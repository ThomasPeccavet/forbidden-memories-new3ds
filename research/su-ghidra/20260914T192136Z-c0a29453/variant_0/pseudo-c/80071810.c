/* Analysis pseudo-C, not buildable source. */

void FUN_80071810(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_80070bb8();
  iVar2 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  *(uint *)(&DAT_800f6f20 + iVar1 * 4) = (int)(&DAT_801d4244)[iVar2 + -1] >> 0x1a & 0x1f;
  return;
}

