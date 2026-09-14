/* Analysis pseudo-C, not buildable source. */

void FUN_800714e8(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar4 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  uVar2 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar1 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  DAT_800ec21a = (undefined1)iVar3;
  DAT_800ec219 = DAT_800ec21a;
  DAT_800ec21b = (char)uVar2;
  if (iVar1 == 0) {
    if ((iVar3 < 6) || (iVar4 != 1)) {
      DAT_800ec21a = 0;
    }
  }
  else if (iVar1 < 0xff) {
    DAT_800ec21a = (undefined1)iVar1;
  }
  else {
    DAT_800ec21a = 0x3a;
  }
  return;
}

