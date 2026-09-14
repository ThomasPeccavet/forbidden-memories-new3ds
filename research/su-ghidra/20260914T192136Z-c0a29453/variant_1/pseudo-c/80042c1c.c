/* Analysis pseudo-C, not buildable source. */

void FUN_80042c1c(int param_1,char param_2)

{
  *(char *)(param_1 + 0x16) = param_2;
  *(short *)(param_1 + 0x14) =
       *(short *)(&DAT_8009c2f8 + (uint)*(byte *)(param_1 + 0x17) * 2) - (short)param_2;
  return;
}

