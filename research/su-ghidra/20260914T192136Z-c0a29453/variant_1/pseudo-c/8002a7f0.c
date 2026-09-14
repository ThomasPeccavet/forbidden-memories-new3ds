/* Analysis pseudo-C, not buildable source. */

void FUN_8002a7f0(int param_1)

{
  int iVar1;
  
  DAT_8009c4c0 = 0;
  iVar1 = (int)*(short *)(param_1 + 10) - (int)DAT_8009c4c2;
  if (iVar1 < 0x40) {
    DAT_8009c4c2 = *(short *)(param_1 + 10) + -0x40;
  }
  if (0xbf < iVar1) {
    DAT_8009c4c2 = *(short *)(param_1 + 10) + -0xc0;
  }
  return;
}

