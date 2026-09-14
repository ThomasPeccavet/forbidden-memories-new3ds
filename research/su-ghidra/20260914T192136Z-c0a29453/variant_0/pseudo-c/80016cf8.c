/* Analysis pseudo-C, not buildable source. */

void FUN_80016cf8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = (int)*(short *)(param_1 + 0x12) - (int)*(short *)(param_1 + 0x14);
  if (iVar1 != 0) {
    iVar2 = iVar1;
    if (iVar1 < 0) {
      iVar2 = -iVar1;
    }
    iVar3 = 9;
    if (299 < iVar2) {
      iVar3 = 0x13;
    }
    if (999 < iVar2) {
      iVar3 = 0x2f;
    }
    if (2999 < iVar2) {
      iVar3 = 0x61;
    }
    if (iVar1 < 1) {
      iVar1 = iVar1 + iVar3;
      if (0 < iVar1) {
        iVar1 = 0;
      }
    }
    else {
      iVar1 = iVar1 - iVar3;
      if (iVar1 < 0) {
        iVar1 = 0;
      }
    }
    *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x14) + (short)iVar1;
  }
  return;
}

