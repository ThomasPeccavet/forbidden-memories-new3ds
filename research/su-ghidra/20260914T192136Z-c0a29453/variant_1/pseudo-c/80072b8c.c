/* Analysis pseudo-C, not buildable source. */

void FUN_80072b8c(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_80070bb8();
  uVar3 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar2 = FUN_8002c9bc(0,uVar3);
  if (iVar2 == 0) {
    *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  }
  else {
    *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 1;
  }
  return;
}

