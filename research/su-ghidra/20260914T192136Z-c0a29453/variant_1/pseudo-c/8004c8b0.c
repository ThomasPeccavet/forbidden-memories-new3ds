/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004c8b0(int param_1)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = 0;
  uVar2 = FUN_8004bf74();
  if ((uVar2 & 0x80) == 0) {
    *(undefined1 *)(param_1 + 0x28) = 1;
    uVar3 = (uint)*(byte *)(param_1 + 0x29);
  }
  else {
    if ((uVar2 & 0xff) != 0xff) {
      *(char *)(param_1 + 0x29) = (char)uVar2;
    }
    *(undefined1 *)(param_1 + 0x28) = 0;
    uVar3 = uVar2;
  }
  iVar4 = *(int *)(&DAT_800113b0 + (uVar3 >> 2 & 0x3c));
  if (iVar4 == 0) {
    if ((uVar2 & 0xff) == 0xf0) {
      FUN_8004c53c(param_1);
    }
    else if ((uVar2 & 0xff) == 0xff) {
      uVar1 = FUN_8004bf74(param_1);
      FUN_8004c318(param_1,uVar1);
    }
    else {
      FUN_8004c310();
    }
  }
  else {
    if (*(char *)(param_1 + 0x28) == '\0') {
      uVar2 = FUN_8004bf74(param_1);
    }
    if (iVar4 == 2) {
      uVar1 = FUN_8004bf74(param_1);
    }
    FUN_8004c5a4(param_1,uVar3 & 0xff,uVar2 & 0xff,uVar1);
  }
  return 0;
}

