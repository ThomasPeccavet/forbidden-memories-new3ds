/* Analysis pseudo-C, not buildable source. */

void FUN_80087c48(undefined4 *param_1,undefined4 *param_2,undefined2 *param_3,undefined2 *param_4,
                 undefined2 *param_5,int param_6)

{
  undefined4 in_zero;
  undefined4 in_at;
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  do {
    setCopReg(2,in_zero,*param_1);
    setCopReg(2,in_at,param_1[1]);
    copFunction(2,0x180001);
    param_1 = param_1 + 2;
    param_6 = param_6 + -1;
    uVar2 = getCopReg(2,0xe);
    *param_2 = uVar2;
    uVar2 = getCopReg(2,0x9800);
    uVar3 = getCopReg(2,0x4000);
    uVar1 = getCopControlWord(2,0xf800);
    *param_3 = (short)uVar2;
    *param_4 = (short)uVar3;
    *param_5 = (short)(uVar1 >> 0xc);
    param_2 = param_2 + 1;
    param_3 = param_3 + 1;
    param_4 = param_4 + 1;
    param_5 = param_5 + 1;
  } while (0 < param_6);
  return;
}

