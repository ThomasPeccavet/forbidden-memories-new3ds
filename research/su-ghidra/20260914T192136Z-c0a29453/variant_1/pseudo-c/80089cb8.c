/* Analysis pseudo-C, not buildable source. */

uint FUN_80089cb8(uint param_1,uint *param_2)

{
  uint uVar1;
  
  if (param_1 == 0) {
    param_1 = 0;
    if (DAT_800ff5f0 != 0) {
      param_2[1] = (uint)DAT_800ff5f8;
      param_1 = param_2[1];
      uVar1 = *DAT_800ff5f8;
      DAT_800ff5f8 = DAT_800ff5f8 + 1;
      DAT_800ff5f0 = DAT_800ff5f0 - 1;
      *param_2 = uVar1;
    }
  }
  else {
    DAT_800ff5f4 = *(uint **)(*(int *)(param_1 - 8) + 8);
    DAT_800ff5f0 = *DAT_800ff5f4 & 0x7fffffff;
    *DAT_800ff5f4 = DAT_800ff5f0;
    DAT_800ff5f8 = DAT_800ff5f4 + 1;
  }
  return param_1;
}

