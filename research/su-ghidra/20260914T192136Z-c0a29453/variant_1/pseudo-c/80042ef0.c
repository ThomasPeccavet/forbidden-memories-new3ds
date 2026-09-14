/* Analysis pseudo-C, not buildable source. */

void FUN_80042ef0(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = (uint)*(byte *)(param_1 + 0xc) - (int)*(short *)(param_1 + 0x60);
  if (iVar2 < 1) {
    FUN_80040690();
  }
  else {
    uVar1 = (undefined1)iVar2;
    *(undefined1 *)(param_1 + 0xe) = uVar1;
    *(undefined1 *)(param_1 + 0xd) = uVar1;
    *(undefined1 *)(param_1 + 0xc) = uVar1;
  }
  return;
}

