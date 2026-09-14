/* Analysis pseudo-C, not buildable source. */

void FUN_80087818(int param_1,int param_2,int param_3)

{
  setCopControlWord(2,0xa800,param_1 << 4);
  setCopControlWord(2,0xb000,param_2 << 4);
  setCopControlWord(2,0xb800,param_3 << 4);
  return;
}

