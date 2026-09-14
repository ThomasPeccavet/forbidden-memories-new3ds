/* Analysis pseudo-C, not buildable source. */

int FUN_80042e38(int param_1,int param_2)

{
  if (param_1 < 0) {
    param_1 = param_1 + param_2;
    if (0 < param_1) {
      return 0;
    }
  }
  else {
    param_1 = param_1 - param_2;
    if (param_1 < 0) {
      param_1 = 0;
    }
  }
  return param_1;
}

