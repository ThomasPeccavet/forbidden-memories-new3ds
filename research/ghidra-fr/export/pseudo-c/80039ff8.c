/* Analysis pseudo-C, not buildable source. */

void FUN_80039ff8(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80039a88();
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x13) = 3;
    *(undefined1 *)(param_1 + 0x15) = 0;
    if (*(char *)(param_1 + 0x12) != '\0') {
      *(undefined1 *)(param_1 + 0x15) = 0x80;
    }
  }
  if (*(char *)(param_1 + 0x12) == '\0') {
    uVar2 = *(byte *)(param_1 + 0x15) + 5;
    if (0x7f < uVar2) {
      *(undefined1 *)(param_1 + 0x13) = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
      return;
    }
  }
  else {
    uVar2 = *(byte *)(param_1 + 0x15) - 5;
    if ((int)uVar2 < 1) {
      FUN_80039ab0(param_1);
      return;
    }
  }
  *(char *)(param_1 + 0x15) = (char)uVar2;
  return;
}

