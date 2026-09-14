/* Analysis pseudo-C, not buildable source. */

void FUN_80037f94(int param_1)

{
  *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) | 0x100;
  FUN_80036c64();
  *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) & 0xfeff;
  *(short *)(param_1 + 0x38) = *(short *)(param_1 + 0x38) + 0x10;
  return;
}

