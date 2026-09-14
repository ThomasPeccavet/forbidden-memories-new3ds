/* Analysis pseudo-C, not buildable source. */

uint FUN_8002ce7c(uint param_1)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)(&DAT_801d0618)[(int)(param_1 & 0x7ff) >> 3] & 0x80 >> (param_1 & 7);
  if ((param_1 & 0x8000) != 0) {
    uVar1 = (uint)(uVar1 == 0);
  }
  return uVar1;
}

