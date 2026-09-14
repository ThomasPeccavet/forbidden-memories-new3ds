/* Analysis pseudo-C, not buildable source. */

void FUN_801820c0(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined2 *puVar5;
  int iVar6;
  undefined2 *puVar7;
  
  uVar1 = FUN_80040350();
  DAT_80184808 = FUN_800403d0(uVar1,2);
  if (DAT_80184808 != 0) {
    FUN_80040800(DAT_80184808,0,0,0,4,0xb,0xc,0x208);
    iVar2 = DAT_80184808;
    *(ushort *)(DAT_80184808 + 8) = *(ushort *)(DAT_80184808 + 8) | 0x28;
    FUN_80042c1c(iVar2,0xfffffffd);
  }
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,4);
  FUN_80042b0c(iVar2,0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x60000000;
  FUN_80042c1c(iVar2,0xfffffffe);
  *(undefined4 *)(iVar2 + 0x28) = 0xf80000;
  *(undefined4 *)(iVar2 + 0x30) = 0xf80140;
  *(undefined4 *)(iVar2 + 0x38) = 0x1000000;
  *(undefined4 *)(iVar2 + 0x40) = 0x1000140;
  *(undefined4 *)(iVar2 + 0x3c) = 0x808080;
  *(undefined4 *)(iVar2 + 0x44) = 0x808080;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,4);
  FUN_80042b0c(iVar2,0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x60000000;
  FUN_80042c1c(iVar2,0xfffffffe);
  *(undefined4 *)(iVar2 + 0x30) = 0x140;
  *(undefined4 *)(iVar2 + 0x28) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0x80000;
  *(undefined4 *)(iVar2 + 0x40) = 0x80140;
  *(undefined4 *)(iVar2 + 0x2c) = 0x808080;
  *(undefined4 *)(iVar2 + 0x34) = 0x808080;
  uVar1 = FUN_80040350();
  DAT_8018480c = FUN_800403d0(uVar1,2);
  if (DAT_8018480c != 0) {
    FUN_80040800(DAT_8018480c,0,0xfffffffd,0,4,4,0xc,0x208);
    iVar2 = DAT_8018480c;
    *(ushort *)(DAT_8018480c + 8) = *(ushort *)(DAT_8018480c + 8) | 0x28;
    FUN_80042c1c(iVar2,0xffffffff);
  }
  FUN_8006b080(0,0x25,0xa0,0x25);
  iVar2 = 0;
  puVar7 = &DAT_80185ec8;
  puVar5 = &DAT_80185eb8;
  piVar4 = &DAT_80184818;
  iVar6 = 0x1e;
  do {
    uVar1 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar1,2);
    if (iVar3 == 0) {
      *piVar4 = 0;
    }
    else {
      FUN_80040800(iVar3,iVar6,0x24,0,4,8,0xc,0x208);
      *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 0x28;
      FUN_80042c1c(iVar3,0);
      *(undefined2 *)(iVar3 + 0x60) = 0xfffe;
      *piVar4 = iVar3;
    }
    piVar4[1] = 0;
    puVar5[1] = 0;
    *puVar5 = 0;
    *puVar7 = 0;
    (&DAT_80185ef4)[iVar2] = 0;
    (&DAT_80185ef6)[iVar2] = 0;
    (&DAT_80185ef8)[iVar2] = 0;
    FUN_801835b8(iVar2,1);
    FUN_80184704(iVar2);
    puVar7 = puVar7 + 0xb;
    puVar5 = puVar5 + 2;
    piVar4 = piVar4 + 2;
    iVar2 = iVar2 + 1;
    iVar6 = iVar6 + 0xa0;
  } while (iVar2 < 2);
  DAT_80185efa = 0;
  DAT_80185efb = 0;
  DAT_80185efc = 0;
  DAT_80185efd = 0;
  DAT_8009c89c = FUN_80183d58;
  DAT_8009c424 = 1;
  return;
}

