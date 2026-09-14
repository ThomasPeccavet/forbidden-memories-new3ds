/* Analysis pseudo-C, not buildable source. */

uint FUN_8008cefc(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 == 1) {
    uVar1 = 2;
  }
  else if ((int)param_1 < 2) {
    if (param_1 != 0) {
      uVar1 = param_1 | 0x8000;
    }
  }
  else {
    uVar1 = 1;
    if ((param_1 != 2) && (uVar1 = param_1 | 0x8000, param_1 == 4)) {
      uVar1 = 3;
    }
  }
  return uVar1;
}

