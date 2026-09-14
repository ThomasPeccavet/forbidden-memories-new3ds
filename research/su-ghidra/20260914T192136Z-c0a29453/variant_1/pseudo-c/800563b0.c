/* Analysis pseudo-C, not buildable source. */

void FUN_800563b0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  if (-1 < param_2) {
    (&DAT_800f4f70)[param_1 * 0x710] = (short)param_2;
    (&DAT_8009c808)[param_1] = (short)param_2;
  }
  if (param_1 < 2) {
    if (-1 < param_3) {
      *(short *)(&DAT_800f4f72 + param_1 * 0xe20) = (short)param_3;
    }
    if (-1 < param_4) {
      *(short *)(&DAT_800f4f74 + param_1 * 0xe20) = (short)param_4;
    }
    if (-1 < param_5) {
      (&DAT_800f4f76)[param_1 * 0xe20] = param_5 != 0;
      (&DAT_8009c80e)[param_1] = param_5 != 0;
    }
    if (-1 < param_6) {
      (&DAT_800f4f77)[param_1 * 0xe20] = param_6 != 0;
      (&DAT_8009c810)[param_1] = param_6 != 0;
    }
  }
  else {
    PTR_DAT_8009c318 = &DAT_800924cc + (uint)DAT_800f6bb0 * 0xb2;
  }
  DAT_8009c324 = 0xf;
  return;
}

