/* Analysis pseudo-C, not buildable source. */

void FUN_80026c2c(int param_1,int param_2)

{
  if (((param_1 - 0x12dU < 0x32) || (param_1 - 0x28bU < 0x32)) || (param_1 == 0x2d1)) {
    DAT_8009c5c4 = (short)param_1;
    DAT_8009c5a4 = DAT_8009c5c4 + -0x12d;
    if ((0x28a < param_1) && (DAT_8009c5a4 = DAT_8009c5c4 + -0x259, param_1 == 0x2d1)) {
      DAT_8009c5a4 = 100;
    }
    DAT_8009c550 = 0x8000;
    if (param_2 != 0) {
      DAT_8009c550 = 0xc000;
    }
  }
  return;
}

