/* Analysis pseudo-C, not buildable source. */

void FUN_8006b260(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  DAT_801bf98e = 4;
  DAT_801bf98d = 4;
  DAT_801bf98c = 4;
  (&DAT_801bf98c)[param_1] = 0;
  iVar1 = FUN_80036184(3,0x20,0x58,0x40,0xa0,0x80);
  *(undefined1 *)(iVar1 + 0x59) = 0x15;
  FUN_800399f0(iVar1);
  uVar2 = FUN_80040350();
  iVar3 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar3,*(short *)(iVar1 + 0x3c) + 8,(int)*(short *)(iVar1 + 0x40),0,4,0xd,0xc,0x208);
  *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 0x28;
  FUN_80042c48(iVar3);
  FUN_80042c1c(iVar3,0x14);
  *(int *)(iVar1 + 0x2c) = iVar3;
  return;
}

