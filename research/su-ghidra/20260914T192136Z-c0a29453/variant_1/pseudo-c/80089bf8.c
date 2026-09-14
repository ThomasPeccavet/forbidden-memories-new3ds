/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80089bf8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  setCopReg(2,0x8800,param_1);
  setCopReg(2,0x9000,param_2);
  setCopReg(2,0x9800,param_3);
  copFunction(2,0x158002d);
  uVar1 = getCopReg(2,0x3800);
  return uVar1;
}

