#pragma once

#include <stddef.h>
#include <stdint.h>

void fm_memory_init(uint8_t *ram, size_t ram_size);

uint32_t fm_memory_read_word(uint32_t addr);
void     fm_memory_write_word(uint32_t addr, uint32_t value);

uint16_t fm_memory_read_half(uint32_t addr);
void     fm_memory_write_half(uint32_t addr, uint16_t value);

uint8_t  fm_memory_read_byte(uint32_t addr);
void     fm_memory_write_byte(uint32_t addr, uint8_t value);

/*
 * 0 = test OK
 * autre = erreur
 */
int fm_memory_self_test(void);

uint32_t fm_memory_last_unmapped(void);
unsigned fm_memory_unmapped_count(void);
void fm_memory_vblank_tick(void);

uint16_t fm_memory_i_stat(void);
uint16_t fm_memory_i_mask(void);