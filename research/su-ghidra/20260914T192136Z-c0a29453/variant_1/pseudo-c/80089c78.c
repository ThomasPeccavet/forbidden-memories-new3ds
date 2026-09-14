/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80089c78(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 in_v0;
  undefined4 uVar1;
  undefined4 in_v1;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  setCopReg(2,in_v0,*param_2);
  setCopReg(2,in_v1,param_2[1]);
  setCopReg(2,param_1,*param_3);
  setCopReg(2,param_2,param_3[1]);
  copFunction(2,0x280030);
  uVar1 = getCopControlWord(2,0xf800);
  copFunction(2,0x158002d);
  copFunction(2,0x1400006);
  return uVar1;
}

