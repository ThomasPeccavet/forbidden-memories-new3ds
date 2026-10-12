#pragma once
#include "cpu_state.h"
#include <stdio.h>
int fm_vlc_try(CPUState *cpu);
void fm_vlc_reset(void);
void fm_vlc_dump(FILE *file);
