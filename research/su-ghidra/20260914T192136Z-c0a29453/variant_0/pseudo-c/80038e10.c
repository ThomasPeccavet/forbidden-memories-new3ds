/* Analysis pseudo-C, not buildable source. */

void FUN_80038e10(int param_1)

{
  int iVar1;
  
  *(undefined2 *)(param_1 + 0x38) = 0x1000;
  *(char *)(param_1 + 0x56) = *(char *)(param_1 + 0x56) + '\x01';
  iVar1 = FUN_80037c0c();
  if ((iVar1 != 0) && (3 < *(byte *)(param_1 + 0x56))) {
    *(undefined1 *)(param_1 + 0x51) = 4;
  }
  DAT_8009c6cc = 1;
  if (DAT_8009c6bc != (code *)0x0) {
    (*DAT_8009c6bc)(param_1);
  }
  return;
}

