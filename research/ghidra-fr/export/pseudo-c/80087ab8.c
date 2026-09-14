/* Analysis pseudo-C, not buildable source. */

void FUN_80087ab8(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5,undefined4 *param_6,undefined4 *param_7,undefined4 *param_8,
                 undefined4 *param_9)

{
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 in_v0;
  int iVar1;
  undefined4 in_v1;
  undefined4 uVar2;
  
  setCopReg(2,in_zero,*param_1);
  setCopReg(2,in_at,param_1[1]);
  setCopReg(2,in_v0,*param_2);
  setCopReg(2,in_v1,param_2[1]);
  setCopReg(2,param_1,*param_3);
  setCopReg(2,param_2,param_3[1]);
  copFunction(2,0x280030);
  uVar2 = getCopControlWord(2,0xf800);
  *param_9 = uVar2;
  copFunction(2,0x1400006);
  iVar1 = getCopReg(2,0xc000);
  if (0 < iVar1) {
    uVar2 = getCopReg(2,0xc);
    *param_4 = uVar2;
    uVar2 = getCopReg(2,0xd);
    *param_5 = uVar2;
    uVar2 = getCopReg(2,0xe);
    *param_6 = uVar2;
    uVar2 = getCopReg(2,8);
    *param_7 = uVar2;
    copFunction(2,0x158002d);
    uVar2 = getCopReg(2,0x3800);
    *param_8 = uVar2;
  }
  return;
}

