/* Analysis pseudo-C, not buildable source. */

uint FUN_80086d50(void)

{
  undefined4 unaff_retaddr;
  
  DAT_80096498 = unaff_retaddr;
  FUN_80089aa8();
  setCopReg(0,Status,Status | 0x40000000);
  setCopControlWord(2,0xe800,0x155);
  setCopControlWord(2,0xf000,0x100);
  setCopControlWord(2,0xd000,1000);
  setCopControlWord(2,0xd800,0xffffef9e);
  setCopControlWord(2,0xe000,0x1400000);
  setCopControlWord(2,0xc000,0);
  setCopControlWord(2,0xc800,0);
  return Status | 0x40000000;
}

