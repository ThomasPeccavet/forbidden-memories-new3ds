/* Analysis pseudo-C, not buildable source. */

void FUN_8007187c(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_80070bb8();
  iVar2 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = (int)*(short *)(&DAT_801ab000 + iVar2 * 0xc);
  return;
}

