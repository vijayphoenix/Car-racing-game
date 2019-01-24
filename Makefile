#==============================================================================
# Build platform
PLATFORM?=linux
# Build description (Primarily uses Debug/Release)
BUILD?=Release
_BUILDL := $(shell echo $(BUILD) | tr A-Z a-z)

# Maximum parallel jobs during build process
MAX_PARALLEL_JOBS?=8

# Dump assembly?
DUMP_ASSEMBLY?=false

# Clean output?
CLEAN_OUTPUT?=true

# Platform specific environment variables
-include env/.all.mk
-include env/.$(_BUILDL).mk
-include env/$(PLATFORM).all.mk
-include env/$(PLATFORM).$(_BUILDL).mk

#==============================================================================
# File/Folder dependencies for the production build recipe (makeproduction)
PRODUCTION_DEPENDENCIES?=
# Extensions to exclude from production builds
PRODUCTION_EXCLUDE?=
# Folder location (relative or absolute) to place the production build into
PRODUCTION_FOLDER?=build
PRODUCTION_FOLDER_RESOURCES := $(PRODUCTION_FOLDER)

#==============================================================================
# Library directories (separated by spaces)
LIB_DIRS?=
INCLUDE_DIRS?=
# Link libraries (separated by spaces)
LINK_LIBRARIES?=

# Precompiled header filename (no extension)
# This file will be excluded from Rebuild, but if the bin/(build) directory is removed, it will be as well.
PRECOMPILED_HEADER?=

# Build-specific preprocessor macros
BUILD_MACROS?=
# Build-specific compiler flags to be appended to the final build step (with prefix)
BUILD_FLAGS?=

# Build dependencies to copy into the bin/(build) folder - example: openal32.dll
BUILD_DEPENDENCIES?=

# NAME should always be passed as an argument from tasks.json as the root folder name, but uses a fallback of "game.exe"
# This is used for the output filename (game.exe)
NAME?=game.exe

#==============================================================================
# The source file directory
SRC_DIR := src


# Project .cpp or .rc files (relative to $(SRC_DIR) directory)
SOURCE_FILES := $(patsubst $(SRC_DIR)/%,%,$(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.c' -o -name '*.cc' -o -name '*.rc'))
# Project subdirectories within $(SRC_DIR)/ that contain source files
PROJECT_DIRS := $(patsubst $(SRC_DIR)/%,%,$(shell find $(SRC_DIR) -mindepth 1 -maxdepth 99 -type d))

# Add prefixes to the above variables
_LIB_DIRS := $(LIB_DIRS:%=-L%)
_INCLUDE_DIRS := $(patsubst %,-I%,$(SRC_DIR)/ $(INCLUDE_DIRS))

_BUILD_MACROS := $(BUILD_MACROS:%=-D%)
_LINK_LIBRARIES := $(LINK_LIBRARIES:%=-l%)

#==============================================================================
# MacOS Specific
MACOS_ICON?=icon
PRODUCTION_MACOS_BUNDLE_COMPANY?=developer
PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME?=App
PRODUCTION_MACOS_BUNDLE_NAME?=App
PRODUCTION_MACOS_MAKE_DMG?=true

ifeq ($(PLATFORM),osx)
	PRODUCTION_MACOS_BUNDLE_COMPANY := '$(PRODUCTION_MACOS_BUNDLE_COMPANY)'
	PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME := '$(PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME)'
	PRODUCTION_MACOS_BUNDLE_NAME := '$(PRODUCTION_MACOS_BUNDLE_NAME)'
	PRODUCTION_FOLDER_MACOS := $(PRODUCTION_FOLDER)
	PRODUCTION_FOLDER := $(PRODUCTION_FOLDER)/$(PRODUCTION_MACOS_BUNDLE_NAME).app/Contents
	PRODUCTION_FOLDER_RESOURCES := $(PRODUCTION_FOLDER)/Resources
	PRODUCTION_DEPENDENCIES := $(PRODUCTION_DEPENDENCIES)
	PRODUCTION_MACOS_FRAMEWORKS := $(PRODUCTION_MACOS_FRAMEWORKS:%=%.framework)
	PRODUCTION_MACOS_BACKGROUND := env/osx/dmg-background
endif

#==============================================================================
# Directories & Dependencies
BLD_DIR := bin/$(BUILD)
BLD_DIR := $(BLD_DIR:%/=%)
_EXE := $(BLD_DIR)/$(NAME)
_NAMENOEXT := $(NAME:.exe=)
_NAMENOEXT := $(_NAMENOEXT:.dll=)

_SOURCES_IF_RC := $(if $(filter windows,$(PLATFORM)),$(SOURCE_FILES:.rc=.res),$(SOURCE_FILES:%.rc=))

OBJ_DIR := $(BLD_DIR)/obj
_OBJS := $(_SOURCES_IF_RC)
_OBJS := $(_OBJS:.c=.o)
_OBJS := $(_OBJS:.cpp=.o)
_OBJS := $(_OBJS:.cc=.o)
OBJS := $(_OBJS:%=$(OBJ_DIR)/%)
OBJ_SUBDIRS := $(PROJECT_DIRS:%=$(OBJ_DIR)/%)

DEP_DIR := $(BLD_DIR)/dep
_DEPS := $(_SOURCES_IF_RC)
_DEPS := $(_DEPS:.c=.d)
_DEPS := $(_DEPS:.cpp=.d)
_DEPS := $(_DEPS:.cc=.d)
DEPS := $(_DEPS:%=$(DEP_DIR)/%)
DEP_SUBDIRS := $(PROJECT_DIRS:%=$(DEP_DIR)/%)

_PCH_HFILE := $(shell find $(SRC_DIR) -name '$(PRECOMPILED_HEADER).hpp' -o -name '$(PRECOMPILED_HEADER).h' -o -name '$(PRECOMPILED_HEADER).hh')
_PCH_EXT := $(_PCH_HFILE:$(SRC_DIR)/$(PRECOMPILED_HEADER).%=%)
_PCH_COMPILER_EXT := $(if $(filter osx,$(PLATFORM)),p,g)ch


_PCH := $(_PCH_HFILE:$(SRC_DIR)/%=$(OBJ_DIR)/%)
ifneq ($(_PCH),)
	_PCH_GCH := $(_PCH).$(_PCH_COMPILER_EXT)
endif

ifeq ($(DUMP_ASSEMBLY),true)
	ASM_DIR := $(BLD_DIR)/asm
	_ASMS := $(_OBJS:%.res=)
	_ASMS := $(_ASMS:.o=.o.asm)
	ASMS := $(_ASMS:%=$(ASM_DIR)/%)
	ASM_SUBDIRS := $(PROJECT_DIRS:%=$(ASM_DIR)/%)
endif

_DIRECTORIES := $(sort bin $(BLD_DIR) $(OBJ_DIR) $(OBJ_SUBDIRS) $(DEP_DIR) $(DEP_SUBDIRS) $(ASM_DIR) $(ASM_SUBDIRS))
_BUILD_DEPENDENCIES := $(patsubst %,$(BLD_DIR)/%,$(notdir $(filter %.dll,$(BUILD_DEPENDENCIES))))

_CLEAN := $(filter true,$(CLEAN_OUTPUT))

# Quiet flag
_Q := $(if $(_CLEAN),@)

#==============================================================================
# Compiler & flags
CC?=g++
RC?=windres.exe
CFLAGS_ALL?=-Wfatal-errors -Wextra -Wall
CFLAGS?=-g $(CFLAGS_ALL)

CFLAGS_DEPS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
PCH_COMPILE = $(CC) $(CFLAGS_DEPS) $(_BUILD_MACROS) $(CFLAGS) -fdiagnostics-color=always $(_INCLUDE_DIRS) -o $@ -c $<
ifneq ($(_PCH),)
	_INCLUDE_PCH := -include $(_PCH)
endif
OBJ_COMPILE = $(CC) $(CFLAGS_DEPS) $(_BUILD_MACROS) $(_INCLUDE_DIRS) $(_INCLUDE_PCH) $(CFLAGS) -fdiagnostics-color=always -o $@ -c $<
RC_COMPILE = -$(RC) -J rc -O coff -i $< -o $@
ifeq ($(PLATFORM),osx)
	ASM_COMPILE = otool -tvV $< | c++filt > $@
else
	ASM_COMPILE = objdump -d -C -Mintel $< > $@
endif
POST_COMPILE = @mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

export GCC_COLORS := error=01;31:warning=01;33:note=01;36:locus=00;34

#==============================================================================
# Build Scripts
all:
	@$(MAKE) -k --no-print-directory makepch
	@$(MAKE) -j$(MAX_PARALLEL_JOBS) -k --no-print-directory makebuild

.PHONY: rebuild
rebuild: clean all

.PHONY: buildprod
buildprod: all makeproduction

#==============================================================================
# Functions
define color_reset
	@tput setaf 4
endef

define comple_with
	$(color_reset)
	$(if $(_CLEAN),@echo $($(1):$(OBJ_DIR)/%=%))
	$(_Q)$(2)
	$(POST_COMPILE)
endef

MKDIR := $(_Q)mkdir -p
WITH_DEPS = $(_PCH_GCH) $(DEP_DIR)/%.d | $(_DIRECTORIES)

#==============================================================================
# Build Recipes
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(WITH_DEPS)
	$(call comple_with,<,$(OBJ_COMPILE))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(WITH_DEPS)
	$(call comple_with,<,$(OBJ_COMPILE))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(WITH_DEPS)
	$(call comple_with,<,$(OBJ_COMPILE))

$(OBJ_DIR)/%.$(_PCH_EXT).$(_PCH_COMPILER_EXT) : $(SRC_DIR)/%.$(_PCH_EXT)
$(OBJ_DIR)/%.$(_PCH_EXT).$(_PCH_COMPILER_EXT) : $(SRC_DIR)/%.$(_PCH_EXT) $(DEP_DIR)/%.d | $(_DIRECTORIES)
	$(call comple_with,<,$(PCH_COMPILE))

$(OBJ_DIR)/%.res: $(SRC_DIR)/%.rc
$(OBJ_DIR)/%.res: $(SRC_DIR)/%.rc $(SRC_DIR)/%.h | $(_DIRECTORIES)
	$(color_reset)
	$(if $(_CLEAN),@echo $(<:$(OBJ_DIR)/%=%))
	$(_Q)$(RC_COMPILE)

$(ASM_DIR)/%.o.asm: $(OBJ_DIR)/%.o
	$(if $(_CLEAN),,$(color_reset))
	$(_Q)$(ASM_COMPILE)

# TODO: Redo the .dll stuff at some point
$(_EXE): $(_PCH_GCH) $(OBJS) $(ASMS) $(BLD_DIR) $(_BUILD_DEPENDENCIES)
	$(color_reset)
	$(if $(_CLEAN),@echo; echo 'Linking: $(_EXE)')
ifeq ($(suffix $(_EXE)),.dll)
	-rm -f $(BLD_DIR)/lib$(_NAMENOEXT).def $(BLD_DIR)/lib$(_NAMENOEXT).a
	$(_Q)$(CC) -shared -Wl,--output-def="$(BLD_DIR)/lib$(_NAMENOEXT).def" -Wl,--out-implib="$(BLD_DIR)/lib$(_NAMENOEXT).a" -Wl,--dll $(_LIB_DIRS) $(OBJS) -o $@ -s $(_LINK_LIBRARIES) $(BUILD_FLAGS)
else
	$(_Q)$(CC) $(_LIB_DIRS) -o $@ $(OBJS) $(_LINK_LIBRARIES) $(BUILD_FLAGS)
endif


.PHONY: makepch
makepch: $(_PCH_GCH)
	@echo > /dev/null

.PHONY: makebuild
makebuild: $(_EXE)
	$(color_reset)
	@echo '$(BUILD) build target is up to date.'

$(_DIRECTORIES) :
	$(if $(_CLEAN),,$(color_reset))
	$(MKDIR) $@

.PHONY: clean
clean:
	$(color_reset)
	$(if $(_CLEAN),@echo 'Cleaning old build files & folders...'; echo)
	$(_Q)$(RM) $(_EXE) $(DEPS) $(OBJS)

#==============================================================================
# Production recipes

$(BLD_DIR)/%.dll:
	$(color_reset)
	$(foreach dep,$(BUILD_DEPENDENCIES),$(shell cp -r $(dep) $(BLD_DIR)))

$(BLD_DIR)/%.so:
	$(color_reset)
	$(foreach dep,$(BUILD_DEPENDENCIES),$(shell cp -r $(dep) $(BLD_DIR)))

.PHONY: rmprod
rmprod:
	$(color_reset)
	-$(_Q)rm -f -r $(if $(filter osx,$(PLATFORM)),$(PRODUCTION_FOLDER_MACOS),$(PRODUCTION_FOLDER))

.PHONY: mkdirprod
mkdirprod:
	$(color_reset)
	$(MKDIR) $(PRODUCTION_FOLDER)

.PHONY: releasetoprod
releasetoprod: $(_EXE)
	$(color_reset)
ifeq ($(PLATFORM),osx)
	@echo 'Creating the MacOS application bundle...'
	$(MKDIR) $(PRODUCTION_FOLDER)/Resources $(PRODUCTION_FOLDER)/Frameworks $(PRODUCTION_FOLDER)/MacOS
ifeq ($(shell brew ls --versions makeicns),)
	brew install makeicns
	$(color_reset)
endif
	$(_Q)makeicns -in env/osx/$(MACOS_ICON).png -out $(PRODUCTION_FOLDER)/Resources/$(MACOS_ICON).icns
	$(_Q)plutil -convert binary1 env/osx/Info.plist.json -o $(PRODUCTION_FOLDER)/Info.plist
	$(_Q)plutil -replace CFBundleExecutable -string $(NAME) $(PRODUCTION_FOLDER)/Info.plist
	$(_Q)plutil -replace CFBundleName -string $(PRODUCTION_MACOS_BUNDLE_NAME) $(PRODUCTION_FOLDER)/Info.plist
	$(_Q)plutil -replace CFBundleDisplayName -string "$(PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME)" $(PRODUCTION_FOLDER)/Info.plist
	$(_Q)plutil -replace CFBundleIdentifier -string com.$(PRODUCTION_MACOS_BUNDLE_DEVELOPER).$(PRODUCTION_MACOS_BUNDLE_NAME) $(PRODUCTION_FOLDER)/Info.plist
	$(_Q)cp $(_EXE) $(PRODUCTION_FOLDER)/MacOS
	$(_Q)chmod +x $(PRODUCTION_FOLDER)/MacOS/$(NAME)
else
	$(_Q)cp $(_EXE) $(PRODUCTION_FOLDER)
endif

.PHONY: makeproduction
makeproduction: rmprod mkdirprod releasetoprod
	$(color_reset)
	@echo -n 'Adding dynamic libraries & project dependencies...'
	$(foreach dep,$(PRODUCTION_DEPENDENCIES),$(shell cp -r $(dep) $(PRODUCTION_FOLDER_RESOURCES)))
	$(foreach excl,$(PRODUCTION_EXCLUDE),$(shell find $(PRODUCTION_FOLDER_RESOURCES) -name '$(excl)' -delete))
	@echo ' Done'
ifeq ($(PLATFORM),osx)
	$(foreach framework,$(PRODUCTION_MACOS_FRAMEWORKS),$(shell cp -r /Library/Frameworks/$(framework) $(PRODUCTION_FOLDER)/Frameworks))
ifeq ($(PRODUCTION_MACOS_MAKE_DMG),true)
	$(shell hdiutil detach /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/ &> /dev/null)
	@echo 'Creating the dmg image for the application...'
	$(_Q)hdiutil create -megabytes 54 -fs HFS+ -volname $(PRODUCTION_MACOS_BUNDLE_NAME) $(PRODUCTION_FOLDER_MACOS)/.tmp.dmg > /dev/null
	$(_Q)hdiutil attach $(PRODUCTION_FOLDER_MACOS)/.tmp.dmg > /dev/null
	$(_Q)cp -r $(PRODUCTION_FOLDER_MACOS)/$(PRODUCTION_MACOS_BUNDLE_NAME).app /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/
	-$(_Q)rm -rf /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/.fseventsd
	$(MKDIR) /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/.background
	$(_Q)tiffutil -cathidpicheck $(PRODUCTION_MACOS_BACKGROUND).png $(PRODUCTION_MACOS_BACKGROUND)@2x.png -out /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/.background/background.tiff
	$(_Q)ln -s /Applications /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/Applications
	$(_Q)appName=$(PRODUCTION_MACOS_BUNDLE_NAME) osascript env/osx/dmg.applescript
	$(_Q)hdiutil detach /Volumes/$(PRODUCTION_MACOS_BUNDLE_NAME)/ > /dev/null
	$(_Q)hdiutil convert $(PRODUCTION_FOLDER_MACOS)/.tmp.dmg -format UDZO -o $(PRODUCTION_FOLDER_MACOS)/$(PRODUCTION_MACOS_BUNDLE_NAME).dmg > /dev/null
	$(_Q)rm -f $(PRODUCTION_FOLDER_MACOS)/.tmp.dmg
	@echo 'Created $(PRODUCTION_FOLDER_MACOS)/$(PRODUCTION_MACOS_BUNDLE_NAME).dmg'
endif
endif

#==============================================================================
# Dependency recipes
$(DEP_DIR)/%.d: ;
.PRECIOUS: $(DEP_DIR)/%.d

include $(wildcard $(DEPS))