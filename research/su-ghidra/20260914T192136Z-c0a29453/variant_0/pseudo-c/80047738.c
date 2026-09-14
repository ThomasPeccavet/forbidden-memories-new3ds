/* Analysis pseudo-C, not buildable source. */

void FUN_80047738(ushort param_1)

{
  if ((*(byte *)(DAT_8009c7e0 + 0x4a) & 2) != 0) {
    if ((param_1 & 0x8000) == 0) {
      if (0x6fff < param_1) {
        param_1 = param_1 + 0x9000;
      }
      FUN_800495c8((int)(short)param_1,1);
    }
    else {
      FUN_800457f0(param_1);
    }
  }
  return;
}

