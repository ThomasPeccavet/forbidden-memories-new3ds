/* Analysis pseudo-C, not buildable source. */

void FUN_80087798(undefined4 *param_1)

{
  setCopControlWord(2,0x8000,*param_1);
  setCopControlWord(2,0x8800,param_1[1]);
  setCopControlWord(2,0x9000,param_1[2]);
  setCopControlWord(2,0x9800,param_1[3]);
  setCopControlWord(2,0xa000,param_1[4]);
  return;
}

