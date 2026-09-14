/* Analysis pseudo-C, not buildable source. */

uint FUN_80080fd0(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((-1 < (short)param_1) &&
     (uVar1 = DAT_80095a9c - 1, (int)(short)param_1 <= (short)DAT_80095a9c + -1)) {
    uVar1 = param_1;
  }
  if ((short)param_2 < 0) {
    param_2 = 0;
  }
  else if ((short)DAT_80095a9e + -1 < (int)(short)param_2) {
    param_2 = DAT_80095a9e - 1;
  }
  return (param_2 & 0x3ff) << 10 | uVar1 & 0x3ff | 0xe4000000;
}

