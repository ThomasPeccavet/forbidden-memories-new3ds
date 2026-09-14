/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80042ec8(int param_1)

{
  if ((*(byte *)(param_1 + 0x6c) & 0x80) != 0) {
    return 1;
  }
  *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x80;
  return 0;
}

