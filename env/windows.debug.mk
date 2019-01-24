CFLAGS := -g -Og $(CFLAGS) -pg

BUILD_FLAGS := \
	-pg

BUILD_MACROS := \
	_DEBUG

LINK_LIBRARIES := \
	sfml-graphics-d \
	sfml-audio-d \
	sfml-network-d \
	sfml-window-d \
	sfml-system-d