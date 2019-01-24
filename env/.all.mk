MAX_PARALLEL_JOBS := 8
CLEAN_OUTPUT := true
DUMP_ASSEMBLY := false

LINK_LIBRARIES := \
	sfml-graphics \
	sfml-audio \
	sfml-network \
	sfml-window \
	sfml-system

PRECOMPILED_HEADER := PCH

PRODUCTION_FOLDER := build

PRODUCTION_EXCLUDE := \
	*.psd \
	*.rar \
	*.7z \
	Thumbs.db \
	.DS_Store

PRODUCTION_DEPENDENCIES := \
	content

