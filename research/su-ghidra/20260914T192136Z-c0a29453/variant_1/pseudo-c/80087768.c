/* Analysis pseudo-C, not buildable source. */

void FUN_80087768(undefined4 *param_1)

{
  setCopControlWord(2,0x4000,*param_1);
  setCopControlWord(2,0x4800,param_1[1]);
  setCopControlWord(2,0x5000,param_1[2]);
  setCopControlWord(2,0x5800,param_1[3]);
  setCopControlWord(2,0x6000,param_1[4]);
  return;
}

