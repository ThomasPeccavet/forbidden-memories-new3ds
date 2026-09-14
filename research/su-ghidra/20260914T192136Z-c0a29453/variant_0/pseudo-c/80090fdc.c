/* Analysis pseudo-C, not buildable source. */

uint FUN_80090fdc(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = FUN_800912b4();
  }
  else {
    uVar1 = FUN_800913dc();
    uVar1 = uVar1 >> 0x1d & 1;
  }
  return uVar1;
}

