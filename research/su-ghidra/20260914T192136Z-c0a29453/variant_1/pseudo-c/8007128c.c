/* Analysis pseudo-C, not buildable source. */

void FUN_8007128c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bd8();
  iVar2 = FUN_8008f708();
  if (iVar2 % 100 < iVar3) {
    DAT_800f6f78 = iVar1 + DAT_800f6f74;
  }
  return;
}

