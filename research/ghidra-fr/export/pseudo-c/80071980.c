/* Analysis pseudo-C, not buildable source. */

void FUN_80071980(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_80070bb8();
  iVar2 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = (int)(short)(&DAT_800eb28c)[(1 - iVar2) * 0x10];
  return;
}

