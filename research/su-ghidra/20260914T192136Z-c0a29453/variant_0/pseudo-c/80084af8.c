/* Analysis pseudo-C, not buildable source. */

void FUN_80084af8(uint *param_1,undefined4 param_2,undefined2 param_3)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  iVar5 = DAT_800ff5c4;
  uVar8 = *param_1;
  if (((-1 < (int)uVar8) && ((short)param_1[2] != 0)) && (*(short *)((int)param_1 + 10) != 0)) {
    uVar12 = ((int)(short)param_1[1] + (int)DAT_800ff444) - (int)(short)param_1[6];
    iVar10 = ((int)*(short *)((int)param_1 + 6) + (int)DAT_800ff446) -
             (int)*(short *)((int)param_1 + 0x1a);
    if ((uVar8 & 0x800000) == 0) {
      uVar9 = (uint)*(byte *)((int)param_1 + 0xe);
      uVar13 = uVar9 + (byte)param_1[2];
    }
    else {
      uVar9 = ((uint)*(byte *)((int)param_1 + 0xe) + (uint)(byte)param_1[2]) - 1;
      uVar13 = *(byte *)((int)param_1 + 0xe) - 1;
    }
    if ((uVar8 & 0x400000) == 0) {
      uVar7 = (uint)*(byte *)((int)param_1 + 0xf);
      uVar11 = uVar7 + *(byte *)((int)param_1 + 10);
    }
    else {
      uVar7 = ((uint)*(byte *)((int)param_1 + 0xf) + (uint)*(byte *)((int)param_1 + 10)) - 1;
      uVar11 = *(byte *)((int)param_1 + 0xf) - 1;
    }
    bVar1 = *(byte *)((int)param_1 + 0x16);
    bVar2 = *(byte *)((int)param_1 + 0x15);
    uVar4 = param_1[5];
    *(uint *)(DAT_800ff5c4 + 8) = uVar12 & 0xffff | iVar10 * 0x10000;
    uVar6 = (uVar7 & 0xff) << 8;
    *(uint *)(iVar5 + 4) =
         uVar8 >> 5 & 0x2000000 | (uVar8 & 0x40) << 0x12 | 0x2c000000 | (uint)bVar1 << 0x10 |
         (uint)bVar2 << 8 | (uint)(byte)uVar4;
    *(uint *)(iVar5 + 0xc) =
         uVar9 & 0xff | uVar6 | (int)*(short *)((int)param_1 + 0x12) << 0x16 |
         ((int)(short)param_1[4] & 0x3f0U) << 0xc;
    uVar7 = (uVar11 & 0xff) << 8;
    *(uint *)(iVar5 + 0x10) = uVar12 + (ushort)param_1[2] & 0xffff | iVar10 * 0x10000;
    *(uint *)(iVar5 + 0x14) =
         uVar13 & 0xff | uVar6 | ((ushort)param_1[3] & 0x1f) << 0x10 | uVar8 >> 1 & 0x1800000 |
         uVar8 >> 7 & 0x600000;
    uVar3 = *(ushort *)((int)param_1 + 10);
    *(uint *)(iVar5 + 0x1c) = uVar9 & 0xff | uVar7;
    *(uint *)(iVar5 + 0x18) = uVar12 & 0xffff | (iVar10 + (uint)uVar3) * 0x10000;
    uVar8 = param_1[2];
    uVar3 = *(ushort *)((int)param_1 + 10);
    *(uint *)(iVar5 + 0x24) = uVar13 & 0xff | uVar7;
    *(uint *)(iVar5 + 0x20) = uVar12 + (ushort)uVar8 & 0xffff | (iVar10 + (uint)uVar3) * 0x10000;
    DAT_800ff5c4 = FUN_80084018(iVar5,param_2,param_3,9);
  }
  return;
}

