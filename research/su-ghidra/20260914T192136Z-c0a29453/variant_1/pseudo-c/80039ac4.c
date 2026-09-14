/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80039ac4(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_80039a88();
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x13) = 2;
    *(undefined2 *)(param_1 + 6) = 0;
    *(undefined2 *)(param_1 + 8) = 0;
    *(undefined1 *)(param_1 + 0x12) = 0x10;
  }
  *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) - (char)DAT_8009c43c;
  if ((*(byte *)(param_1 + 0x11) & 0x40) == 0) {
    iVar1 = (uint)*(byte *)(param_1 + 6) + _DAT_8009c43c * 0x10;
    *(char *)(param_1 + 6) = (char)iVar1;
    if (iVar1 * 0x1000000 < 0) {
      *(undefined1 *)(param_1 + 6) = 0x80;
      *(undefined1 *)(param_1 + 0x12) = 8;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x40;
    }
    *(undefined1 *)(param_1 + 8) = *(undefined1 *)(param_1 + 6);
  }
  else {
    iVar1 = (uint)*(byte *)(param_1 + 7) + _DAT_8009c43c * 0x10;
    *(char *)(param_1 + 7) = (char)iVar1;
    if (iVar1 * 0x1000000 < 0) {
      *(undefined1 *)(param_1 + 0x12) = 0;
      *(undefined1 *)(param_1 + 0x13) = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    *(undefined1 *)(param_1 + 9) = *(undefined1 *)(param_1 + 7);
  }
  return;
}

