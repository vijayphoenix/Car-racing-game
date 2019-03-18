cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Project name
project(POPL2_project)

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

# General compiler options
if (SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
endif()

# Specific compiler options - set C++11 flag for g++ and clang
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -w")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

	# Mac OS X: clang uses libc++ standard library
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
endif()

#####################################################################################################################################


# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

# Find SFML
# Note: SFML_STATIC_LIBRARIES determines which libraries are found by find_package()
find_package(SFML 2 COMPONENTS audio graphics window system network)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()
######################################################################################################################################


##
message("Vijay-->\n1.PROJECT_NAME::${PROJECT_NAME}\n2.SFML_LIBRARIES::${SFML_LIBRARIES}\n")
message("3.SFML_DEPENDENCIES::${SFML_DEPENDENCIES}\n\n")
######################################################################################################################################
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(libs)
add_executable(main src/Main.cpp)
target_link_libraries(main extLibs)

######################################################################################################################################
# Build static or shared libraries? Set chapter-specific DLL import macro
if(SFML_STATIC_LIBRARIES)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
endif()

# Link SFML. For versions < 2.2, SFML_DEPENDENCIES is not defined, and we do not need to link dependencies
if(SFML_VERSION_MINOR LESS 2)
set(SFML_DEPENDENCIES "")
endif()
target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


