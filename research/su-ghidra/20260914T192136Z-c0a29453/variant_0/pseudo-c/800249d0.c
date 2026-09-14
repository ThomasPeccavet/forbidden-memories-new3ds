/* Analysis pseudo-C, not buildable source. */

void FUN_800249d0(int *param_1)

{
  *(ushort *)((int)param_1 + 0x16) = *(ushort *)((int)param_1 + 0x16) & 0x7fff;
  if (*param_1 != 0) {
    FUN_80040690();
    *param_1 = 0;
  }
  return;
}

