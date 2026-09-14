/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80037c0c(int param_1)

{
  if (*(short *)(param_1 + 0x3e) <= *(short *)(param_1 + 0x38)) {
    *(undefined2 *)(param_1 + 0x38) = 0;
    *(ushort *)(param_1 + 0x3a) = *(short *)(param_1 + 0x3a) + (ushort)*(byte *)(param_1 + 0x5b);
  }
  if ((int)((int)*(short *)(param_1 + 0x3a) + (uint)*(byte *)(param_1 + 0x5b)) <=
      (int)*(short *)(param_1 + 0x42)) {
    return 0;
  }
  *(ushort *)(param_1 + 0x3a) = *(short *)(param_1 + 0x3a) - (ushort)*(byte *)(param_1 + 0x5b);
  return 1;
}

