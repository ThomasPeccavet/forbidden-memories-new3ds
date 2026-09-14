/* Analysis pseudo-C, not buildable source. */

void FUN_80089c48(undefined4 *param_1,undefined2 *param_2,undefined4 *param_3)

{
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  copFunction(2,0x480012);
  uVar1 = getCopReg(2,0x4800);
  uVar3 = getCopReg(2,0x5000);
  uVar2 = getCopReg(2,0xb);
  *(undefined4 *)(param_2 + 2) = uVar2;
  *param_2 = (short)uVar1;
  param_2[1] = (short)uVar3;
  uVar2 = getCopControlWord(2,0xf800);
  *param_3 = uVar2;
  return;
}

