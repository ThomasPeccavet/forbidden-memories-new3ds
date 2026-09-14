/* Analysis pseudo-C, not buildable source. */

void FUN_80039148(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x28);
  iVar2 = *(int *)(param_1 + 0x2c);
  *(undefined2 *)(iVar2 + 0x18) = *(undefined2 *)(iVar3 + 0x18);
  *(undefined2 *)(iVar2 + 0x1a) = *(undefined2 *)(iVar3 + 0x1a);
  sVar1 = *(short *)(iVar3 + 0x30);
  *(short *)(iVar2 + 0x48) = sVar1;
  *(short *)(iVar2 + 0x28) = sVar1;
  *(short *)(iVar2 + 0x38) = sVar1 + -8;
  sVar1 = *(short *)(iVar3 + 0x30) + *(short *)(iVar3 + 0x3c);
  *(short *)(iVar2 + 0x50) = sVar1;
  *(short *)(iVar2 + 0x30) = sVar1;
  *(short *)(iVar2 + 0x40) = sVar1 + 8;
  sVar1 = *(short *)(iVar3 + 0x32) + -8;
  *(short *)(iVar2 + 0x32) = sVar1;
  *(short *)(iVar2 + 0x2a) = sVar1;
  sVar1 = *(short *)(iVar3 + 0x32) + *(short *)(iVar3 + 0x4a);
  *(short *)(iVar2 + 0x42) = sVar1;
  *(short *)(iVar2 + 0x3a) = sVar1;
  sVar1 = *(short *)(iVar3 + 0x32) + *(short *)(iVar3 + 0x3e) + 8;
  *(short *)(iVar2 + 0x52) = sVar1;
  *(short *)(iVar2 + 0x4a) = sVar1;
  return;
}

