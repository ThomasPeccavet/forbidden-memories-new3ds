/* Analysis pseudo-C, not buildable source. */

void FUN_8001b720(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  
  iVar2 = (int)*(char *)(param_1 + 0xe);
  piVar4 = &DAT_800eb2b8 + iVar2 * 3;
  *(short *)(*piVar4 + 0x32) = *(short *)(*piVar4 + 0x32) + -4;
  uVar3 = FUN_80040350();
  uVar3 = FUN_800403d0(uVar3,1);
  FUN_80040844(uVar3,(int)*(short *)(*piVar4 + 0x30),(int)*(short *)(*piVar4 + 0x32),0x10,0x10,
               (uint)*(byte *)(param_1 + 0x15) << 4,0xb0,0xb,0x2d0,0xfc);
  FUN_80042c48(uVar3);
  FUN_80042c1c(uVar3,(int)((*(byte *)(*piVar4 + 0x16) + 1) * 0x1000000) >> 0x18);
  (&DAT_800eb2bc)[iVar2 * 3] = uVar3;
  cVar1 = *(char *)(param_1 + 0x15) + '\x01';
  *(char *)(param_1 + 0x15) = cVar1;
  (&DAT_800eb2c1)[iVar2 * 0xc] = cVar1;
  FUN_80040204(0x2f);
  return;
}

