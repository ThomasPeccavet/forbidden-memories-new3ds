/* Analysis pseudo-C, not buildable source. */

void FUN_80089ba8(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 in_at;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  setCopReg(2,param_3,*param_2);
  copFunction(2,0x108041b);
  uVar1 = getCopReg(2,0x16);
  *param_3 = uVar1;
  return;
}

