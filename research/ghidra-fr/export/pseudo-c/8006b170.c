/* Analysis pseudo-C, not buildable source. */

void FUN_8006b170(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  DAT_8009c6d1 = (undefined1)param_1;
  iVar1 = FUN_80036184(3,10,0x30,0x78,0x120,0x10);
  *(undefined1 *)(iVar1 + 0x59) = 0x12;
  FUN_800399f0(iVar1);
  uVar2 = FUN_80040350();
  iVar3 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar3,(int)*(short *)(iVar1 + 0x3c) + param_1 * 0xa0,(int)*(short *)(iVar1 + 0x40),0,
               4,0xe,0xc,0x208);
  *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 0x28;
  FUN_80042c48(iVar3);
  FUN_80042c1c(iVar3,0x11);
  *(int *)(iVar1 + 0x2c) = iVar3;
  return;
}

