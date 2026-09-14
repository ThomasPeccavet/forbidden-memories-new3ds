/* Analysis pseudo-C, not buildable source. */

void FUN_80037814(int param_1)

{
  int unaff_gp;
  
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
  }
  if (*(char *)(*(int *)(unaff_gp + 0x414) + 0x33) == '\0') {
    FUN_8003a364();
    *(undefined1 *)(param_1 + 0x51) = 0;
  }
  return;
}

