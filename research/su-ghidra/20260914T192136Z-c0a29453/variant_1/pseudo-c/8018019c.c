/* Analysis pseudo-C, not buildable source. */

void FUN_8018019c(void)

{
  undefined4 uVar1;
  undefined4 in_v1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int unaff_s0;
  uint uVar6;
  int *piVar7;
  undefined4 uStack00000010;
  undefined4 uStack00000014;
  undefined4 uStack00000018;
  undefined4 uStack0000001c;
  undefined *puStack00000020;
  
  uStack00000018 = 0x1a;
  uStack00000010 = 0;
  puStack00000020 = &DAT_801af800;
  uStack00000014 = in_v1;
  uStack0000001c = in_v1;
  FUN_80042bd8();
  iVar2 = *(int *)(unaff_s0 + 0x478c);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x1000000;
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
  FUN_80042c48();
  iVar3 = *(int *)(unaff_s0 + 0x478c);
  *(undefined1 *)(iVar3 + 0x6c) = 0x3c;
  iVar2 = *(int *)(unaff_s0 + 0x478c);
  *(undefined2 *)(iVar3 + 0x60) = 0xfffe;
  *(undefined2 *)(iVar2 + 0x36) = 0;
  uVar6 = 0;
  piVar7 = &DAT_80184794;
  iVar2 = -0xa0;
  do {
    uVar1 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar1,2);
    if ((int)uVar6 < 5) {
      iVar5 = uVar6 * 0x20 + 0x3a;
    }
    else {
      iVar5 = iVar2 + 0x32;
    }
    if (iVar3 == 0) {
      *piVar7 = 0;
    }
    else {
      uStack00000010 = 0;
      uStack00000014 = 0;
      uStack00000018 = 0x18;
      uStack0000001c = 0;
      puStack00000020 = &DAT_801af800;
      FUN_80042bd8(iVar3,0xa0,iVar5,0);
      uVar4 = (uint)DAT_801847c0;
      *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) & 0xffbf | 8;
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x1000000;
      FUN_80040734(iVar3,uVar6 << 1 | (uint)(uVar4 != uVar6));
      FUN_80042c48(iVar3);
      *piVar7 = iVar3;
    }
    piVar7 = piVar7 + 1;
    uVar6 = uVar6 + 1;
    iVar2 = iVar2 + 0x20;
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

