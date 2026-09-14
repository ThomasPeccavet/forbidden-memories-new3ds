/* Analysis pseudo-C, not buildable source. */

void FUN_800718e8(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  if (*(short *)(&DAT_801ab000 + iVar3 * 0xc) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
    if ((*(ushort *)(&DAT_801ab006 + iVar3 * 0xc) & 0x1000) != 0) {
      uVar2 = 2;
    }
  }
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = uVar2;
  return;
}

