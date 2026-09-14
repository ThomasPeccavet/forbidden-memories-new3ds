/* Analysis pseudo-C, not buildable source. */

uint FUN_80075ea8(int param_1,uint param_2)

{
  uint uVar1;
  
  if (DAT_80093fdc != 0) {
    if (DAT_80093fe4 == 0) {
      trap(0x1c00);
    }
    if (param_2 % DAT_80093fe4 != 0) {
      param_2 = param_2 + DAT_80093fe4 & ~DAT_80093fe8;
    }
  }
  uVar1 = param_2 >> (DAT_80093fe0 & 0x1f);
  if (param_1 != -2) {
    if (param_1 == -1) {
      param_2 = uVar1 & 0xffff;
    }
    else {
      *(short *)(param_1 * 2 + DAT_80093fb8) = (short)uVar1;
    }
  }
  return param_2;
}

