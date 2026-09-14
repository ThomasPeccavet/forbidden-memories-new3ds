/* Analysis pseudo-C, not buildable source. */

int FUN_80087958(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                undefined4 *param_5,undefined4 *param_6,undefined4 *param_7,undefined4 *param_8,
                undefined4 *param_9,uint *param_10)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 in_v0;
  int iVar2;
  undefined4 in_v1;
  uint uVar3;
  uint uVar4;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  setCopReg(2,in_v0,*param_2);
  setCopReg(2,in_v1,param_2[1]);
  setCopReg(2,param_1,*param_3);
  setCopReg(2,param_2,param_3[1]);
  copFunction(2,0x280030);
  uVar1 = getCopReg(2,0xc);
  *param_5 = uVar1;
  uVar1 = getCopReg(2,0xd);
  *param_6 = uVar1;
  uVar1 = getCopReg(2,0xe);
  *param_7 = uVar1;
  uVar3 = getCopControlWord(2,0xf800);
  setCopReg(2,in_zero,*param_4);
  setCopReg(2,in_at,param_4[1]);
  copFunction(2,0x180001);
  uVar1 = getCopReg(2,0xe);
  *param_8 = uVar1;
  uVar1 = getCopReg(2,8);
  *param_9 = uVar1;
  uVar4 = getCopControlWord(2,0xf800);
  iVar2 = getCopReg(2,0x9800);
  *param_10 = uVar4 | uVar3;
  return iVar2 >> 2;
}

