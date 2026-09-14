/* Analysis pseudo-C, not buildable source. */

void FUN_800877f8(int param_1,int param_2,int param_3)

{
  setCopControlWord(2,0x6800,param_1 << 4);
  setCopControlWord(2,0x7000,param_2 << 4);
  setCopControlWord(2,0x7800,param_3 << 4);
  return;
}

