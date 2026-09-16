# New 3DS platform bring-up. Requires devkitARM and libctru.
ifeq ($(strip $(DEVKITARM)),)
$(error Set DEVKITARM to the devkitPro devkitARM directory)
endif
include $(DEVKITARM)/3ds_rules
.DEFAULT_GOAL := all
PSXRECOMP_ROOT ?= ../work/upstream-psxrecomp
RUNTIME := $(PSXRECOMP_ROOT)/runtime
TARGET := fm-new3ds
BUILD := build
ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS := -std=gnu11 -O2 -g -Wall -Wextra -mword-relocations $(ARCH) \
 -ffunction-sections -fdata-sections -MMD -MP \
 -Iinclude -I$(CTRULIB)/include -I$(RUNTIME)/include
LDFLAGS := -specs=3dsx.specs $(ARCH) -Wl,--gc-sections,-Map,$(BUILD)/$(TARGET).map
OBJECTS := $(BUILD)/main.o $(BUILD)/platform.o $(BUILD)/disc.o \
 $(BUILD)/gpu_sw_renderer.o $(BUILD)/gpu_vram_dirty.o
.PHONY: all clean
all: $(TARGET).3dsx
$(BUILD):
	mkdir -p $@
$(BUILD)/%.o: source/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/gpu_sw_renderer.o: $(RUNTIME)/src/gpu_sw_renderer.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/gpu_vram_dirty.o: $(RUNTIME)/src/gpu_vram_dirty.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -L$(CTRULIB)/lib -lctru -lm -o $@
$(TARGET).3dsx: $(TARGET).elf
	3dsxtool $< $@
clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).3dsx
-include $(OBJECTS:.o=.d)
