/* Analysis pseudo-C, not buildable source. */

void FUN_80033de4(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_80033034();
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x5aa4) - (int)DAT_8009c4c0;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xf;
    }
    *(int *)(param_1 + 0x5aa8) = iVar1 >> 4;
    *(undefined4 *)(param_1 + 0x5aac) = 0x10;
    FUN_80040204(0x1e);
  }
  DAT_8009c4c0 = DAT_8009c4c0 + *(short *)(param_1 + 0x5aa8);
  iVar1 = *(int *)(param_1 + 0x5aac) + -1;
  *(int *)(param_1 + 0x5aac) = iVar1;
  if (iVar1 == 0) {
    DAT_8009c4c0 = *(short *)(param_1 + 0x5aa4);
    *(undefined1 *)(param_1 + 0x6342) = 0;
    if (DAT_8009c4c0 != 0) {
      *(undefined1 *)(param_1 + 0x6342) = 1;
    }
    *(undefined2 *)(param_1 + 0x633e) = *(undefined2 *)(param_1 + 0x6340);
  }
  return;
}

