/* Analysis pseudo-C, not buildable source. */

int FUN_80021614(int param_1,int param_2)

{
  short *psVar1;
  
  for (psVar1 = (short *)(&DAT_801798a8 + param_1 * 0x14); *psVar1 <= param_2; psVar1 = psVar1 + 2)
  {
  }
  return (int)psVar1[1];
}

