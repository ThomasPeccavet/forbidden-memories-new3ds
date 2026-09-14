/* Analysis pseudo-C, not buildable source. */

void FUN_80073a44(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_80070bb8();
  iVar2 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  if (iVar3 == 0) {
    iVar2 = (char)(&DAT_80092c11)[iVar2 * 9] * 100;
  }
  else {
    iVar2 = (int)(char)(&DAT_80092c11)[iVar3 + iVar2 * 9];
  }
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = iVar2;
  return;
}

