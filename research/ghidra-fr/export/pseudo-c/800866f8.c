/* Analysis pseudo-C, not buildable source. */

int FUN_800866f8(uint param_1)

{
  int iVar1;
  
  if ((int)param_1 < 0) {
    param_1 = -param_1;
  }
  param_1 = param_1 & 0xfff;
  if (param_1 < 0x801) {
    if (param_1 < 0x401) {
      iVar1 = (int)*(short *)(&DAT_80095c38 + (0x400 - param_1) * 2);
    }
    else {
      iVar1 = -(int)*(short *)(&DAT_80095438 + param_1 * 2);
    }
  }
  else if (param_1 < 0xc01) {
    iVar1 = -(int)*(short *)(&DAT_80095c38 + (0xc00 - param_1) * 2);
  }
  else {
    iVar1 = (int)*(short *)(&DAT_80094438 + param_1 * 2);
  }
  return iVar1;
}

