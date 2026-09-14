/* Analysis pseudo-C, not buildable source. */

int FUN_8003748c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040390();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,(int)*(short *)(param_1 + 0x3c) + (int)*(short *)(param_1 + 0x3e) + -0x10,
               (int)*(short *)(param_1 + 0x40) + (int)*(short *)(param_1 + 0x42) + -0x10,3,0,0,0xb,
               0x20c);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
  FUN_80042c48(iVar2);
  FUN_80042c1c(iVar2,(int)((*(byte *)(param_1 + 0x59) + 1) * 0x1000000) >> 0x18);
  return iVar2;
}

