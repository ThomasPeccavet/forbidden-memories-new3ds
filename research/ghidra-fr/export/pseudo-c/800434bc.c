/* Analysis pseudo-C, not buildable source. */

void FUN_800434bc(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(short *)(param_1 + 0x36) + param_2 >> 1;
  iVar4 = *(short *)(param_1 + 0x38) + param_3 >> 1;
  iVar1 = FUN_800866f8(param_4);
  iVar2 = (*(short *)(param_1 + 0x36) - iVar3) * iVar1;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xfff;
  }
  iVar1 = (*(short *)(param_1 + 0x38) - iVar4) * iVar1;
  *(short *)(param_1 + 0x30) = (short)iVar3 + (short)(iVar2 >> 0xc);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xfff;
  }
  *(short *)(param_1 + 0x32) = (short)iVar4 + (short)(iVar1 >> 0xc);
  return;
}

