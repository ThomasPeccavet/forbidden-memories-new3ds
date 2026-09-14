/* Analysis pseudo-C, not buildable source. */

int FUN_80049bec(undefined4 param_1,short param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = DAT_8009c7d8;
  sVar1 = *(short *)(DAT_8009c7d8 + 0x4a4);
  if ((int)sVar1 == (int)param_2) {
    FUN_80077748(*(undefined4 *)(DAT_8009c7d8 + 0x4b8));
    iVar3 = FUN_800776e8(param_1,*(undefined4 *)(iVar2 + 0x4b4));
    iVar4 = -1;
    if (iVar3 == *(int *)(iVar2 + 0x4b4)) {
      *(undefined4 *)(iVar2 + 0x4b0) = param_1;
      iVar4 = (int)sVar1;
    }
  }
  else {
    iVar4 = -1;
  }
  return iVar4;
}

