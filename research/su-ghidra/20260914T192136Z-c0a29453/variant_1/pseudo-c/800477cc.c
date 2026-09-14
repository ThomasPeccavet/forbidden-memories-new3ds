/* Analysis pseudo-C, not buildable source. */

void FUN_800477cc(ushort param_1,short param_2)

{
  if ((*(byte *)(DAT_8009c7e0 + 0x4a) & 2) != 0) {
    if ((param_1 & 0x8000) == 0) {
      if (0x6fff < param_1) {
        param_1 = param_1 + 0x9000;
      }
      FUN_800496c0((int)(short)param_1,(int)param_2);
    }
    else {
      FUN_8004785c(0x7000);
      FUN_800456c4(param_1,(int)param_2);
    }
  }
  return;
}

