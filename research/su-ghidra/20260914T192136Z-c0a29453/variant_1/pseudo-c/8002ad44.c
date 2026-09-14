/* Analysis pseudo-C, not buildable source. */

void FUN_8002ad44(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,6);
  *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(param_1 + 0x48);
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  *(undefined2 *)(iVar2 + 0x60) = 0x100;
  *(undefined4 *)(iVar2 + 0x18) = uVar1;
  *(short *)(iVar2 + 0x3c) = *(short *)(iVar2 + 0x18) << 1;
  *(short *)(iVar2 + 0x3e) = *(short *)(iVar2 + 0x1a) << 1;
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar2 + 0x20) = *(undefined4 *)(param_1 + 0x20);
  uVar1 = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(iVar2 + 0xc) = 0;
  *(undefined4 *)(iVar2 + 0x44) = uVar1;
  FUN_80042c48(iVar2);
  FUN_80042c1c(iVar2,(int)(((uint)*(byte *)(param_1 + 0x16) + param_2) * 0x1000000) >> 0x18);
  *(undefined4 *)(iVar2 + 0x10) = 1;
  *(code **)(iVar2 + 0x4c) = FUN_8002ab50;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0xf7ffffff | 0x50000000;
  return;
}

