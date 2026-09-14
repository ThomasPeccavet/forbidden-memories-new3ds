/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80039a88(int param_1)

{
  if ((*(byte *)(param_1 + 0x11) & 0x80) != 0) {
    return 1;
  }
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x80;
  return 0;
}

