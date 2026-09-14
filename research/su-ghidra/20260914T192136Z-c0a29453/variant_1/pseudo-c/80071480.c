/* Analysis pseudo-C, not buildable source. */

void FUN_80071480(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_80070bb8();
  iVar2 = FUN_80070bb8();
  iVar3 = FUN_80070bb8();
  *(int *)(&DAT_800f6f20 + iVar3 * 4) =
       *(int *)(&DAT_800f6f20 + iVar1 * 4) - *(int *)(&DAT_800f6f20 + iVar2 * 4);
  return;
}

