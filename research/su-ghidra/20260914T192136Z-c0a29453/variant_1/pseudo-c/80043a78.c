/* Analysis pseudo-C, not buildable source. */

void FUN_80043a78(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = 0;
  if (param_1 != 0) {
    uVar2 = FUN_80040350();
    iVar7 = FUN_800403d0(uVar2,2);
    FUN_80042bd8(iVar7,0,0,0,0,*(undefined1 *)(param_1 + 0x69),*(undefined1 *)(param_1 + 0x66),0x20d
                 ,&DAT_801af000);
    *(undefined4 *)(iVar7 + 4) = *(undefined4 *)(param_1 + 4);
    FUN_80042c1c(iVar7,0xffffffff);
    *(ushort *)(iVar7 + 8) = *(ushort *)(iVar7 + 8) | 8;
    *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x60000000;
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x50000000;
  }
  *(undefined2 *)(param_2 + 0x48) = 0xa0;
  *(undefined2 *)(param_2 + 0x4a) = 0x80;
  *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) & 0xf7ffffff;
  uVar2 = FUN_80040350();
  iVar3 = FUN_800403d0(uVar2,2);
  FUN_80042bd8(iVar3,0,0,0,0,*(undefined1 *)(param_2 + 0x69),*(undefined1 *)(param_2 + 0x66),0x20d,
               &DAT_801af000);
  *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(param_2 + 4);
  FUN_80042c1c(iVar3,0xffffffff);
  uVar6 = 0;
  *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 8;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x60000000;
  *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(param_2 + 0x48);
  *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) | 0x50000000;
  uVar4 = 0;
  do {
    uVar4 = uVar4 | uVar6 << 8 | uVar6;
    *(uint *)(param_2 + 0xc) = uVar4;
    *(uint *)(iVar3 + 0xc) = uVar4;
    if (param_1 != 0) {
      uVar4 = 0x80 - uVar6;
      uVar5 = uVar4 | uVar4 * 0x10000 | uVar4 * 0x100;
      sVar1 = (short)uVar4 * 0x60 + 0x1000;
      *(short *)(iVar3 + 0x46) = sVar1;
      *(short *)(iVar3 + 0x44) = sVar1;
      *(short *)(param_2 + 0x46) = sVar1;
      *(short *)(param_2 + 0x44) = sVar1;
      *(uint *)(param_1 + 0xc) = uVar5;
      *(uint *)(iVar7 + 0xc) = uVar5;
    }
    uVar6 = uVar6 + 8;
    FUN_80012c50();
    uVar4 = uVar6 * 0x10000;
  } while ((int)uVar6 < 0x81);
  *(undefined4 *)(param_2 + 0x44) = 0x10001000;
  *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) & 0x8fffffff | 0x8000000;
  FUN_80040690(param_1);
  FUN_80040690(iVar7);
  FUN_80040690(iVar3);
  return;
}

