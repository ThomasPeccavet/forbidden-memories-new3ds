/* Analysis pseudo-C, not buildable source. */

void FUN_8002ceb8(uint param_1)

{
  int iVar1;
  
  iVar1 = (int)(param_1 & 0x7ff) >> 3;
  if ((param_1 & 0x8000) != 0) {
    (&DAT_801d0618)[iVar1] = (&DAT_801d0618)[iVar1] & ~(byte)(0x80 >> (param_1 & 7));
    return;
  }
  (&DAT_801d0618)[iVar1] = (&DAT_801d0618)[iVar1] | (byte)(0x80 >> (param_1 & 7));
  return;
}

