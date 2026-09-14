/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80087928(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  setCopReg(2,0x6000,param_1);
  setCopReg(2,0x7000,param_3);
  setCopReg(2,0x6800,param_2);
  copFunction(2,0x1400006);
  uVar1 = getCopReg(2,0xc000);
  return uVar1;
}

