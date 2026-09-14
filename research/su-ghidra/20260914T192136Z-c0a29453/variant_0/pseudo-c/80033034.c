/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80033034(int param_1)

{
  if ((*(ushort *)(param_1 + 0x633e) & 0x8000) != 0) {
    return 1;
  }
  *(ushort *)(param_1 + 0x633e) = *(ushort *)(param_1 + 0x633e) | 0x8000;
  return 0;
}

