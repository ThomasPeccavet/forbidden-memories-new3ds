/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80039ba8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_80039a88();
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x13) = 2;
    *(undefined2 *)(param_1 + 6) = 0x8080;
    *(undefined2 *)(param_1 + 8) = 0x8080;
    *(undefined1 *)(param_1 + 0x12) = 0;
  }
  if ((*(byte *)(param_1 + 0x11) & 0x40) == 0) {
    iVar1 = (uint)*(byte *)(param_1 + 6) + _DAT_8009c43c * -0x18;
    if (iVar1 < 1) {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x40;
      iVar1 = 0;
    }
    *(char *)(param_1 + 6) = (char)iVar1;
    *(char *)(param_1 + 7) = (char)iVar1;
  }
  else {
    iVar1 = (uint)*(byte *)(param_1 + 8) + _DAT_8009c43c * -0x18;
    if (iVar1 < 1) {
      FUN_80039ab0(param_1);
      iVar1 = 0;
    }
    *(char *)(param_1 + 8) = (char)iVar1;
    *(char *)(param_1 + 9) = (char)iVar1;
  }
  return;
}

