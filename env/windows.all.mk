CC := i686-w64-mingw32-g++.exe
CFLAGS := -Wfatal-errors -Wunreachable-code -Wextra -Wall -std=c++17
RC := windres.exe

_MINGW := C:/mingw32/bin
_SFML := C:/SFML-2.5.1
_SFML_BIN := $(_SFML)/bin

LIB_DIRS := \
	$(_SFML)/lib

INCLUDE_DIRS := \
	$(_SFML)/include

BUILD_DEPENDENCIES := \
	$(_SFML_BIN)/openal32.dll

PRODUCTION_DEPENDENCIES := \
	$(PRODUCTION_DEPENDENCIES) \
	$(_MINGW)/libgcc_s_dw2-1.dll \
	$(_MINGW)/libstdc++-6.dll \
	$(_MINGW)/libwinpthread-1.dll \
	$(_SFML_BIN)/openal32.dll \
	$(_SFML_BIN)/sfml-audio-2.dll \
	$(_SFML_BIN)/sfml-graphics-2.dll \
	$(_SFML_BIN)/sfml-network-2.dll \
	$(_SFML_BIN)/sfml-system-2.dll \
	$(_SFML_BIN)/sfml-window-2.dll
