/* Analysis pseudo-C, not buildable source. */

void FUN_8007175c(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  iVar4 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  if (((int)(&DAT_801d4244)[iVar4 + -1] >> 0x1a & 0x1fU) < 0x14) {
    iVar2 = FUN_8002cdc8(iVar4,0);
    iVar4 = FUN_8002cdc8(iVar4,1);
    uVar3 = iVar4 < iVar2 ^ 1;
  }
  else {
    uVar3 = 0;
  }
  *(uint *)(&DAT_800f6f20 + iVar1 * 4) = uVar3;
  return;
}

