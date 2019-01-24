CFLAGS := -g -Og $(CFLAGS) -pg

BUILD_FLAGS := \
	$(BUILD_FLAGS) \
	-pg

BUILD_MACROS := \
	_DEBUG
