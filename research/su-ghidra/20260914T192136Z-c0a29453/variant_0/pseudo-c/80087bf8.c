/* Analysis pseudo-C, not buildable source. */

int FUN_80087bf8(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                undefined4 *param_5,undefined4 *param_6)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar2;
  int iVar3;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  copFunction(2,0x180001);
  uVar2 = getCopControlWord(2,0xf800);
  uVar1 = getCopReg(2,0xe);
  *param_4 = uVar1;
  *param_6 = uVar2;
  setCopReg(2,in_zero,*param_2);
  setCopReg(2,in_at,param_2[1]);
  setCopReg(2,param_3,*param_3);
  copFunction(2,0xe80413);
  iVar3 = getCopReg(2,0x9800);
  uVar1 = getCopReg(2,0x16);
  *param_5 = uVar1;
  return iVar3 >> 2;
}

