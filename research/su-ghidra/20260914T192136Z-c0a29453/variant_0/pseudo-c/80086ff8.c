/* Analysis pseudo-C, not buildable source. */

int * FUN_80086ff8(undefined4 *param_1,uint *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  setCopControlWord(2,0,*param_1);
  setCopControlWord(2,0x800,param_1[1]);
  setCopControlWord(2,0x1000,param_1[2]);
  setCopControlWord(2,0x1800,param_1[3]);
  setCopControlWord(2,0x2000,param_1[4]);
  uVar1 = *param_2;
  uVar3 = param_2[1];
  uVar5 = param_2[2];
  if ((int)uVar1 < 0) {
    iVar7 = -((int)-uVar1 >> 0xf);
    uVar1 = -(-uVar1 & 0x7fff);
  }
  else {
    iVar7 = (int)uVar1 >> 0xf;
    uVar1 = uVar1 & 0x7fff;
  }
  if ((int)uVar3 < 0) {
    iVar8 = -((int)-uVar3 >> 0xf);
    uVar3 = -(-uVar3 & 0x7fff);
  }
  else {
    iVar8 = (int)uVar3 >> 0xf;
    uVar3 = uVar3 & 0x7fff;
  }
  if ((int)uVar5 < 0) {
    iVar9 = -((int)-uVar5 >> 0xf);
    uVar5 = -(-uVar5 & 0x7fff);
  }
  else {
    iVar9 = (int)uVar5 >> 0xf;
    uVar5 = uVar5 & 0x7fff;
  }
  setCopReg(2,0x4800,iVar7);
  setCopReg(2,0x5000,iVar8);
  setCopReg(2,0x5800,iVar9);
  copFunction(2,0x41e012);
  iVar7 = getCopReg(2,0xc800);
  iVar8 = getCopReg(2,0xd000);
  iVar9 = getCopReg(2,0xd800);
  setCopReg(2,0x4800,uVar1);
  setCopReg(2,0x5000,uVar3);
  setCopReg(2,0x5800,uVar5);
  copFunction(2,0x49e012);
  if (iVar7 < 0) {
    iVar7 = iVar7 * 8;
  }
  else {
    iVar7 = iVar7 << 3;
  }
  if (iVar8 < 0) {
    iVar8 = iVar8 * 8;
  }
  else {
    iVar8 = iVar8 << 3;
  }
  if (iVar9 < 0) {
    iVar9 = iVar9 * 8;
  }
  else {
    iVar9 = iVar9 << 3;
  }
  iVar2 = getCopReg(2,0xc800);
  iVar4 = getCopReg(2,0xd000);
  iVar6 = getCopReg(2,0xd800);
  *param_3 = iVar2 + iVar7;
  param_3[1] = iVar4 + iVar8;
  param_3[2] = iVar6 + iVar9;
  return param_3;
}

