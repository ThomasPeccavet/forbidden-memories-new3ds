/* Analysis pseudo-C, not buildable source. */

int FUN_8002cdc8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (param_2 == 0) {
    uVar3 = (&DAT_801d4244)[param_1 + -1];
  }
  else {
    uVar3 = (int)(&DAT_801d4244)[param_1 + -1] >> 9;
  }
  iVar1 = FUN_80024a38((int)(&DAT_801d4244)[param_1 + -1] >> 0x1a & 0x1f);
  iVar1 = (uVar3 & 0x1ff) * 10 + iVar1;
  iVar2 = 0;
  if ((-1 < iVar1) && (iVar2 = iVar1, 9999 < iVar1)) {
    iVar2 = 9999;
  }
  return iVar2;
}

