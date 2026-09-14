/* Analysis pseudo-C, not buildable source. */

void FUN_80084478(uint *param_1,undefined4 param_2,undefined2 param_3)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined2 local_68;
  undefined2 local_66;
  short local_64;
  int local_60;
  int local_5c;
  undefined4 local_58;
  short local_50;
  short local_4e;
  undefined2 local_4c;
  short local_48;
  short local_46;
  undefined2 local_44;
  short local_40;
  short local_3e;
  undefined2 local_3c;
  short local_38;
  short local_36;
  undefined2 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 auStack_20 [4];
  undefined1 auStack_1c [4];
  
  iVar4 = DAT_800ff5c4;
  uVar13 = *param_1;
  if ((int)uVar13 < 0) {
    return;
  }
  if ((short)param_1[2] == 0) {
    return;
  }
  uVar8 = 0;
  if (*(short *)((int)param_1 + 10) == 0) {
    return;
  }
  uVar6 = uVar13 >> 0x1b & 1;
  if (param_1[7] == 0x10001000) {
    if (param_1[8] != 0) goto LAB_8008450c;
    uVar8 = (uint)((uVar13 & 0xc00000) == 0);
  }
  uVar6 = uVar6 | uVar8;
LAB_8008450c:
  if (uVar6 == 0) {
    if (param_1[8] == 0) {
      local_88 = DAT_800ff4f0;
      local_84 = DAT_800ff4f4;
      local_80 = DAT_800ff4f8;
      local_7c = DAT_800ff4fc;
      local_78 = DAT_800ff500;
      local_74 = DAT_800ff504;
      local_70 = DAT_800ff508;
      local_6c = DAT_800ff50c;
    }
    else {
      local_68 = 0;
      local_66 = 0;
      local_64 = (short)((ulonglong)((longlong)(int)param_1[8] * 0xb60b60b7) >> 0x28) -
                 (short)((int)param_1[8] >> 0x1f);
      FUN_80087cb8(&local_68,&local_88);
    }
    if (param_1[7] != 0x10001000) {
      local_60 = (int)(short)param_1[7];
      local_5c = (int)*(short *)((int)param_1 + 0x1e);
      local_58 = 0;
      FUN_800875f8(&local_88,&local_60);
    }
    local_60 = (int)(short)param_1[1];
    local_5c = (int)*(short *)((int)param_1 + 6);
    local_58 = FUN_800877e8();
    FUN_800875c8(&local_88,&local_60);
    FUN_80087738(&local_88);
    FUN_800877c8(&local_88);
    local_4c = 0;
    local_50 = -(short)param_1[6];
    local_4e = -*(short *)((int)param_1 + 0x1a);
    local_44 = 0;
    local_48 = (short)param_1[2] + local_50;
    local_3c = 0;
    local_3e = *(short *)((int)param_1 + 10) + local_4e;
    local_38 = (short)param_1[2] + local_50;
    local_34 = 0;
    local_36 = *(short *)((int)param_1 + 10) + local_4e;
    local_46 = local_4e;
    local_40 = local_50;
    FUN_80087958(&local_50,&local_48,&local_40,&local_38,&local_30,&local_2c,&local_28,&local_24,
                 auStack_20,auStack_1c);
    if ((uVar13 & 0x800000) == 0) {
      uVar6 = (uint)*(byte *)((int)param_1 + 0xe);
      uVar8 = (uVar6 + (byte)param_1[2]) - 1;
    }
    else {
      uVar8 = (uint)*(byte *)((int)param_1 + 0xe);
      uVar6 = (uVar8 + (byte)param_1[2]) - 1;
    }
    if ((uVar13 & 0x400000) == 0) {
      uVar11 = (uint)*(byte *)((int)param_1 + 0xf);
      uVar7 = (uVar11 + *(byte *)((int)param_1 + 10)) - 1;
    }
    else {
      uVar7 = (uint)*(byte *)((int)param_1 + 0xf);
      uVar11 = (uVar7 + *(byte *)((int)param_1 + 10)) - 1;
    }
    uVar12 = (uVar11 & 0xff) << 8;
    bVar1 = *(byte *)((int)param_1 + 0x16);
    bVar2 = *(byte *)((int)param_1 + 0x15);
    uVar11 = param_1[5];
    *(undefined4 *)(iVar4 + 8) = local_30;
    *(uint *)(iVar4 + 4) =
         uVar13 >> 5 & 0x2000000 | (uVar13 & 0x40) << 0x12 | 0x2c000000 | (uint)bVar1 << 0x10 |
         (uint)bVar2 << 8 | (uint)(byte)uVar11;
    sVar3 = *(short *)((int)param_1 + 0x12);
    uVar11 = param_1[4];
    *(undefined4 *)(iVar4 + 0x10) = local_2c;
    *(uint *)(iVar4 + 0xc) =
         uVar6 & 0xff | uVar12 | (int)sVar3 << 0x16 | ((int)(short)uVar11 & 0x3f0U) << 0xc;
    uVar11 = param_1[3];
    uVar10 = 9;
    *(undefined4 *)(iVar4 + 0x18) = local_28;
    uVar7 = (uVar7 & 0xff) << 8;
    *(uint *)(iVar4 + 0x1c) = uVar6 & 0xff | uVar7;
    *(undefined4 *)(iVar4 + 0x20) = local_24;
    *(uint *)(iVar4 + 0x24) = uVar8 & 0xff | uVar7;
    uVar8 = uVar8 & 0xff | uVar12 | ((ushort)uVar11 & 0x1f) << 0x10 | uVar13 >> 1 & 0x1800000;
    uVar13 = uVar13 >> 7 & 0x600000;
  }
  else {
    uVar8 = param_1[1];
    sVar3 = *(short *)((int)param_1 + 6);
    *(uint *)(DAT_800ff5c4 + 4) =
         (ushort)param_1[3] & 0x1f | uVar13 >> 0x11 & 0x180 | 0xe1000200 | uVar13 >> 0x17 & 0x60;
    iVar9 = (int)DAT_800ff444;
    iVar5 = (int)DAT_800ff446;
    uVar10 = 5;
    *(uint *)(iVar4 + 8) =
         uVar13 >> 5 & 0x2000000 | (uVar13 & 0x40) << 0x12 | 0x64000000 |
         (uint)*(byte *)((int)param_1 + 0x16) << 0x10 | (uint)*(byte *)((int)param_1 + 0x15) << 8 |
         (uint)(byte)param_1[5];
    *(uint *)(iVar4 + 0xc) =
         ((short)uVar8 + iVar9) - (int)(short)param_1[6] & 0xffffU |
         ((sVar3 + iVar5) - (int)*(short *)((int)param_1 + 0x1a)) * 0x10000;
    *(uint *)(iVar4 + 0x10) =
         (uint)*(ushort *)((int)param_1 + 0xe) | (int)*(short *)((int)param_1 + 0x12) << 0x16 |
         ((int)(short)param_1[4] & 0x3f0U) << 0xc;
    uVar8 = (uint)(ushort)param_1[2];
    uVar13 = (uint)*(ushort *)((int)param_1 + 10) << 0x10;
  }
  *(uint *)(iVar4 + 0x14) = uVar8 | uVar13;
  DAT_800ff5c4 = FUN_80084018(iVar4,param_2,param_3,uVar10);
  return;
}

