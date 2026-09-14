/* Analysis pseudo-C, not buildable source. */

void FUN_80040748(int param_1,uint param_2)

{
  if (*(byte *)(param_1 + 0x69) != param_2) {
    *(char *)(param_1 + 0x69) = (char)param_2;
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xffef;
  }
  return;
}

