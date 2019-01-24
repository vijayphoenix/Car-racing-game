CC := g++-8.1.0
CFLAGS := -Wfatal-errors -Wunreachable-code -Wextra -Wall -std=c++17
MAX_PARALLEL_JOBS := 4

CFLAGS := -Os -s $(CFLAGS)

BUILD_MACROS= \
	NDEBUG

LIB_DIRS := \
	/usr/local/gcc-8.1.0/lib \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/gcc-8.1.0/include \
	/usr/local/include

BUILD_DEPENDENCIES :=
