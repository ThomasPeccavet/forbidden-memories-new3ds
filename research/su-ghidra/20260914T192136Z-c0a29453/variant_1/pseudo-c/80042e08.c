/* Analysis pseudo-C, not buildable source. */

int FUN_80042e08(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  if (param_2 < 0) {
    param_1 = param_1 - param_3;
    bVar1 = param_1 < param_2;
  }
  else {
    param_1 = param_1 + param_3;
    bVar1 = param_2 < param_1;
  }
  if (bVar1) {
    param_1 = param_2;
  }
  return param_1;
}

