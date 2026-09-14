/* Analysis pseudo-C, not buildable source. */

void FUN_8005c7a4(int param_1,int param_2)

{
  if (0x1c < param_2 - 4U) {
    param_2 = 8;
  }
  *(char *)((int)&DAT_800f4f84 + param_1 * 0xe20 + 1) = (char)param_2;
  if ((&DAT_800f4f8e)[param_1 * 0xe20] == '>') {
    FUN_8005c808(param_1,1);
  }
  return;
}

