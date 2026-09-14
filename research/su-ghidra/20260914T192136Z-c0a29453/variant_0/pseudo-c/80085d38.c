/* Analysis pseudo-C, not buildable source. */

void FUN_80085d38(uint param_1,uint param_2,uint *param_3)

{
  param_3[2] = param_1 & 0xffff;
  param_3[3] = param_2 & 0xffff;
  param_3[4] = (param_3[1] + (4 << (*param_3 & 0x1f))) - 4;
  FUN_80080150(param_3[1],1 << (*param_3 & 0x1f));
  return;
}

