/* Analysis pseudo-C, not buildable source. */

void FUN_800878f8(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar1;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  copFunction(2,0x480012);
  uVar1 = getCopReg(2,0x19);
  *param_2 = uVar1;
  uVar1 = getCopReg(2,0x1a);
  param_2[1] = uVar1;
  uVar1 = getCopReg(2,0x1b);
  param_2[2] = uVar1;
  uVar1 = getCopControlWord(2,0xf800);
  *param_3 = uVar1;
  return;
}

