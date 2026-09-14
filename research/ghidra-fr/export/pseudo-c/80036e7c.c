/* Analysis pseudo-C, not buildable source. */

void FUN_80036e7c(int param_1)

{
  undefined2 uVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  
  bVar2 = DAT_8009c6c8;
  iVar4 = *(int *)(param_1 + 0x30);
  uVar1 = *(undefined2 *)(param_1 + 0x3c);
  *(undefined2 *)(iVar4 + 0x48) = uVar1;
  *(undefined2 *)(iVar4 + 0x38) = uVar1;
  *(undefined2 *)(iVar4 + 0x28) = uVar1;
  sVar3 = *(short *)(param_1 + 0x3c) + *(short *)(param_1 + 0x3e);
  *(short *)(iVar4 + 0x50) = sVar3;
  *(short *)(iVar4 + 0x40) = sVar3;
  *(short *)(iVar4 + 0x30) = sVar3;
  sVar3 = *(short *)(param_1 + 0x40) + (bVar2 & 0x30) +
          (short)((int)((uint)DAT_8009c6d0 << 0x18) >> 0x14);
  *(short *)(iVar4 + 0x2a) = sVar3;
  *(short *)(iVar4 + 0x32) = sVar3;
  *(short *)(iVar4 + 0x42) = sVar3 + 10;
  *(short *)(iVar4 + 0x3a) = sVar3 + 10;
  *(short *)(iVar4 + 0x52) = sVar3 + 0x10;
  *(short *)(iVar4 + 0x4a) = sVar3 + 0x10;
  return;
}

