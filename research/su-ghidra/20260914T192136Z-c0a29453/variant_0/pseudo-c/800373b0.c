/* Analysis pseudo-C, not buildable source. */

void FUN_800373b0(int param_1)

{
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    FUN_80037354(param_1,2,0);
  }
  else if (((&DAT_800ec39f)[(uint)*(ushort *)(param_1 + 0x5c) * 0x16] & 0x80) == 0) {
    *(undefined1 *)(param_1 + 0x56) = 0;
    *(undefined2 *)(param_1 + 0x38) = 0;
    *(undefined2 *)(param_1 + 0x3a) = 0;
    *(undefined1 *)(param_1 + 0x51) = 0;
  }
  return;
}

