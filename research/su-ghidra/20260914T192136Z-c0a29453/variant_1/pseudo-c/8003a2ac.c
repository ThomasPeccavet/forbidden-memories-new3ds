/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003a2ac(int param_1)

{
  if ((*(byte *)(param_1 + 0x33) & 0x80) != 0) {
    return 1;
  }
  *(byte *)(param_1 + 0x33) = *(byte *)(param_1 + 0x33) | 0x80;
  return 0;
}

