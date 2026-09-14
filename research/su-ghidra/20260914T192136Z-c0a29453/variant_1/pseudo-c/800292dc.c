/* Analysis pseudo-C, not buildable source. */

void FUN_800292dc(int param_1,int param_2)

{
  int iVar1;
  
  *(short *)(&DAT_800eb4a0 + param_1 * 0x40) = (short)param_2;
  iVar1 = FUN_80014e08(0,0,param_2 * 8 + 0x2ca,8,FUN_80028aa0,0,0);
  *(int *)(iVar1 + 0x38) = param_1;
  DAT_8009c460 = *(uint *)(iVar1 + 0x2c) | 0x10;
  return;
}

