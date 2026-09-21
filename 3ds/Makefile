# ============================================================
# Forbidden Memories - New Nintendo 3DS
# B111 RELEASE/O3 - generated core rebuilt automatically
# ============================================================

ifeq ($(strip $(DEVKITARM)),)
$(error Set DEVKITARM to the devkitPro devkitARM directory)
endif

include $(DEVKITARM)/3ds_rules

.DEFAULT_GOAL := all


# ============================================================
# Paths
# ============================================================

PSXRECOMP_ROOT ?= ../work/upstream-psxrecomp
RUNTIME := $(PSXRECOMP_ROOT)/runtime

GENERATED_COMBINED := \
	../work/arm-generated-objects/fm-generated-combined.o


# ============================================================
# Target
# ============================================================

TARGET := fm-new3ds
BUILD := build


# ============================================================
# ARM11
# ============================================================

ARCH := \
	-march=armv6k \
	-mtune=mpcore \
	-mfloat-abi=hard \
	-mtp=soft


# ============================================================
# Compiler - B107 release profile
# ============================================================
#
# Previous project profile:
#   -O2 -g
#
# B107:
#   -O3
#   -DNDEBUG
#   -DPSX_NO_DEBUG_TOOLS
#   -fomit-frame-pointer
#
# No -ffast-math: the PS1/GTE arithmetic must remain conservative.
#

CFLAGS := \
	-std=gnu11 \
	-O3 \
	-DNDEBUG \
	-DPSX_NO_DEBUG_TOOLS \
	-fomit-frame-pointer \
	-Wall \
	-Wextra \
	-mword-relocations \
	$(ARCH) \
	-ffunction-sections \
	-fdata-sections \
	-MMD \
	-MP \
	-Iinclude \
	-I$(CTRULIB)/include \
	-I$(RUNTIME)/include


LDFLAGS := \
	-specs=3dsx.specs \
	$(ARCH) \
	-Wl,--gc-sections \
	-Wl,-Map,$(BUILD)/$(TARGET).map


# ============================================================
# Objects
# ============================================================

OBJECTS := \
	$(BUILD)/main.o \
	$(BUILD)/platform.o \
	$(BUILD)/disc.o \
	$(BUILD)/fm_cpu.o \
	$(BUILD)/fm_memory.o \
	$(BUILD)/fm_runtime_shim.o \
	$(BUILD)/fm_interp.o \
	$(BUILD)/fm_gpu.o \
	$(BUILD)/gpu_sw_renderer.o \
	$(BUILD)/gpu_vram_dirty.o


.PHONY: all clean generated-release

all: $(TARGET).3dsx

# B111: the huge PSXRecomp object is prelinked and is NOT rebuilt by
# the normal %.o rule below. A normal 3DS build must therefore refresh
# it explicitly, otherwise an old O2/debug object may be linked.
generated-release:
	cd .. && bash rebuild_generated_release.sh


$(BUILD):
	mkdir -p $@


$(BUILD)/%.o: source/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@


# ============================================================
# 3DS software rasterizer hot path
# ============================================================
#
# B123: keep conservative FP semantics for game/GTE code, but allow
# aggressive FP reassociation/reciprocal optimizations in the software GPU.
# The rasterizer performs float interpolation in the innermost pixel loops.
#
RENDERER_CFLAGS := \
	$(CFLAGS) \
	-Ofast \
	-ffast-math \
	-fno-math-errno \
	-fno-trapping-math \
	-funsafe-math-optimizations \
	-freciprocal-math

$(BUILD)/gpu_sw_renderer.o: $(RUNTIME)/src/gpu_sw_renderer.c | $(BUILD)
	$(CC) $(RENDERER_CFLAGS) -c $< -o $@


$(BUILD)/gpu_vram_dirty.o: $(RUNTIME)/src/gpu_vram_dirty.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET).elf: generated-release $(OBJECTS) $(GENERATED_COMBINED)
	$(CC) \
		$(LDFLAGS) \
		$(OBJECTS) \
		$(GENERATED_COMBINED) \
		-L$(CTRULIB)/lib \
		-lctru \
		-lm \
		-o $@


$(TARGET).3dsx: $(TARGET).elf
	3dsxtool $< $@


clean:
	rm -rf \
		$(BUILD) \
		$(TARGET).elf \
		$(TARGET).3dsx


-include $(OBJECTS:.o=.d)
