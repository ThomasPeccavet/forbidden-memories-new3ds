/* Analysis pseudo-C, not buildable source. */

void FUN_80043560(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(short *)(param_1 + 0x36) - param_2;
  iVar4 = *(short *)(param_1 + 0x38) - param_3;
  if (param_4 < 0) {
    iVar2 = FUN_80086628(param_4 + 0x400);
    iVar3 = iVar3 * iVar2;
    iVar4 = iVar4 * iVar2;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xfff;
    }
    *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x36) - (short)(iVar3 >> 0xc);
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    sVar1 = *(short *)(param_1 + 0x38) - (short)(iVar4 >> 0xc);
  }
  else {
    iVar2 = FUN_80086628();
    iVar3 = iVar3 * -iVar2;
    iVar4 = iVar4 * -iVar2;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xfff;
    }
    *(short *)(param_1 + 0x30) = (short)param_2 - (short)(iVar3 >> 0xc);
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    sVar1 = (short)param_3 - (short)(iVar4 >> 0xc);
  }
  *(short *)(param_1 + 0x32) = sVar1;
  return;
}

