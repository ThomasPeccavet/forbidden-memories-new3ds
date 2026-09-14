/* Analysis pseudo-C, not buildable source. */

int FUN_80086664(int param_1)

{
  int iVar1;
  
  if (param_1 < 0x801) {
    if (param_1 < 0x401) {
      iVar1 = (int)*(short *)(&DAT_80095c38 + param_1 * 2);
    }
    else {
      iVar1 = (int)*(short *)(&DAT_80095c38 + (0x800 - param_1) * 2);
    }
  }
  else if (param_1 < 0xc01) {
    iVar1 = -(int)*(short *)(&DAT_80094c38 + param_1 * 2);
  }
  else {
    iVar1 = -(int)*(short *)(&DAT_80095c38 + (0x1000 - param_1) * 2);
  }
  return iVar1;
}

