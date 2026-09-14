/* Analysis pseudo-C, not buildable source. */

/* WARNING: Instruction at (ram,0x80086e20) overlaps instruction at (ram,0x80086e1c)
    */

uint FUN_80086dd8(int param_1)

{
  uint uVar1;
  
  setCopReg(2,0xf000,param_1);
  uVar1 = getCopReg(2,0xf800);
  if (uVar1 != 0x20) {
    uVar1 = uVar1 & 0xfffffffe;
    if ((int)(uVar1 - 0x18) < 0) {
      param_1 = param_1 >> (0x18 - uVar1 & 0x1f);
    }
    else {
      param_1 = param_1 << (uVar1 - 0x18 & 0x1f);
    }
    return (uint)((int)*(short *)(&DAT_800964a8 + (param_1 + -0x40) * 2) <<
                 ((int)(0x1f - uVar1) >> 1 & 0x1fU)) >> 0xc;
  }
  return 0;
}

