/* Analysis pseudo-C, not buildable source. */

void FUN_80075e64(int param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    *(short *)(param_1 * 2 + DAT_80093fb8) = (short)param_2;
  }
  else {
    *(short *)(param_1 * 2 + DAT_80093fb8) = (short)(param_2 >> (DAT_80093fe0 & 0x1f));
  }
  return;
}

