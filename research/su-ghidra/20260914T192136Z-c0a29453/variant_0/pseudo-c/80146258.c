/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80180000) */

void FUN_80146258(undefined4 param_1,int param_2)

{
  ushort *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  
  trap(0);
  trap(0);
  DAT_801847c0 = (char)param_2 + (char)(param_2 / 0xb) * -0xb;
  uVar2 = FUN_80040350();
  DAT_80184784 = FUN_800403d0(uVar2,2);
  if (DAT_80184784 != 0) {
    FUN_80042bd8(DAT_80184784,0,0,5,0,0,0x1a,1,&DAT_801af800);
    iVar8 = DAT_80184784;
    puVar1 = (ushort *)(DAT_80184784 + 8);
    *(uint *)(DAT_80184784 + 4) = *(uint *)(DAT_80184784 + 4) | 0x1000000;
    *(ushort *)(iVar8 + 8) = *puVar1 | 0x28;
    FUN_80042c1c(iVar8,0);
  }
  uVar2 = FUN_80040350();
  DAT_80184788 = FUN_800403d0(uVar2,2);
  if (DAT_80184788 != 0) {
    FUN_80042bd8(DAT_80184788,0,8,5,0,2,0x1a,1,&DAT_801af800);
    iVar8 = DAT_80184788;
    puVar1 = (ushort *)(DAT_80184788 + 8);
    *(uint *)(DAT_80184788 + 4) = *(uint *)(DAT_80184788 + 4) | 0x1000000;
    *(ushort *)(iVar8 + 8) = *puVar1 | 0x28;
    FUN_80042c1c(iVar8,1);
  }
  uVar2 = FUN_80040350();
  DAT_8018478c = FUN_800403d0(uVar2,2);
  if (DAT_8018478c != 0) {
    FUN_80042bd8(DAT_8018478c,0,8,5,0,1,0x1a,1,&DAT_801af800);
    iVar8 = DAT_8018478c;
    puVar1 = (ushort *)(DAT_8018478c + 8);
    *(uint *)(DAT_8018478c + 4) = *(uint *)(DAT_8018478c + 4) | 0x1000000;
    *(ushort *)(iVar8 + 8) = *puVar1 | 0x28;
    FUN_80042c48();
    iVar8 = DAT_8018478c;
    *(undefined1 *)(DAT_8018478c + 0x6c) = 0x3c;
    iVar3 = DAT_8018478c;
    *(undefined2 *)(iVar8 + 0x60) = 0xfffe;
    *(undefined2 *)(iVar3 + 0x36) = 0;
  }
  uVar6 = 0;
  piVar7 = &DAT_80184794;
  iVar8 = -0xa0;
  do {
    uVar2 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar2,2);
    if ((int)uVar6 < 5) {
      iVar5 = uVar6 * 0x20 + 0x3a;
    }
    else {
      iVar5 = iVar8 + 0x32;
    }
    if (iVar3 == 0) {
      *piVar7 = 0;
    }
    else {
      FUN_80042bd8(iVar3,0xa0,iVar5,0,0,0,0x18,0,&DAT_801af800);
      uVar4 = (uint)DAT_801847c0;
      *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) & 0xffbf | 8;
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x1000000;
      FUN_80040734(iVar3,uVar6 << 1 | (uint)(uVar4 != uVar6));
      FUN_80042c48(iVar3);
      *piVar7 = iVar3;
    }
    piVar7 = piVar7 + 1;
    uVar6 = uVar6 + 1;
    iVar8 = iVar8 + 0x20;
  } while ((int)uVar6 < 0xb);
  DAT_801847c1 = 0;
  DAT_801847c2 = 0;
  DAT_801847c3 = 0;
  if (DAT_801847c0 != 0) {
    DAT_801847c3 = 0x80;
    *(ushort *)(DAT_8018478c + 8) = *(ushort *)(DAT_8018478c + 8) & 0xffbf;
  }
  DAT_801847c4 = 0;
  DAT_801847c5 = 0;
  DAT_801847c6 = 0;
  DAT_801847c7 = 0;
  DAT_801847c8 = 0;
  DAT_801847c9 = 0;
  FUN_80180da4(0);
  DAT_8009c898 = &LAB_80180b4c;
  FUN_800477a4(0x7000);
  return;
}

