/* Analysis pseudo-C, not buildable source. */

void FUN_80050f78(void)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  short sVar11;
  byte bVar12;
  short sVar13;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120 [2];
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  int local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  int local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  int local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 local_c8;
  ushort local_c4;
  short local_c2;
  ushort local_c0;
  ushort local_be;
  ushort local_bc;
  byte local_ba;
  byte local_b9;
  undefined2 local_b8;
  undefined2 local_b6;
  undefined1 auStack_b4 [20];
  undefined1 auStack_a0 [3];
  undefined1 local_9d;
  undefined1 auStack_9c [3];
  undefined1 local_99;
  undefined1 auStack_98 [4];
  undefined1 auStack_94 [4];
  undefined1 auStack_90 [4];
  undefined1 auStack_8c [4];
  undefined2 local_88;
  undefined2 local_86;
  undefined1 auStack_84 [4];
  undefined2 local_80;
  undefined2 local_7e;
  undefined1 auStack_7c [3];
  undefined1 local_79;
  undefined1 auStack_78 [3];
  undefined1 local_75;
  undefined2 local_74;
  undefined2 local_72;
  undefined1 auStack_70 [4];
  undefined2 local_6c;
  undefined2 local_6a;
  undefined1 auStack_68 [4];
  undefined2 local_64;
  undefined2 local_62;
  undefined1 auStack_60 [4];
  undefined2 local_5c;
  undefined2 local_5a;
  undefined1 auStack_58 [3];
  undefined1 local_55;
  undefined1 auStack_54 [3];
  undefined1 local_51;
  undefined2 local_50;
  undefined2 local_4e;
  undefined1 auStack_4c [4];
  undefined2 local_48;
  undefined2 local_46;
  undefined1 auStack_44 [4];
  undefined1 auStack_40 [4];
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [8];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [4];
  
  local_130 = DAT_800113f0;
  local_12c = DAT_800113f4;
  local_128 = DAT_800113f8;
  local_124 = DAT_800113fc;
  local_120[0] = DAT_80011400;
  local_118 = DAT_80011404;
  local_114 = DAT_80011408;
  local_110 = DAT_8001140c;
  local_10c = DAT_80011410;
  uVar10 = *(ushort *)(PTR_DAT_8009c318 + 0xaa);
  uVar2 = *(ushort *)(PTR_DAT_8009c318 + 0xa8);
  bVar1 = PTR_DAT_8009c318[0xac];
  sVar13 = (short)*(undefined4 *)(DAT_800f6ad0 + 0x1c) + 300;
  if (DAT_800f6bd7 == '\0') {
    return;
  }
  if (((DAT_800f6b58 == -0x1000) && (DAT_800f6b5c == -0x1000)) && (DAT_800f6b60 == -0x1000)) {
    return;
  }
  FUN_80051904(0);
  local_c8 = 0;
  if ((*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0xe000) != 0) {
    local_c8 = 0x1000000;
  }
  FUN_80085768(0,&DAT_800f6b28);
  FUN_80085768(1,&DAT_800f6b38);
  FUN_80085768(2,&DAT_800f6b48);
  FUN_80085cd8(DAT_800f6b58,DAT_800f6b5c,DAT_800f6b60);
  FUN_80085588(&DAT_800f6bdc);
  FUN_80089ba8(&local_118,&local_130,auStack_b4);
  local_bc = *(ushort *)(PTR_DAT_8009c318 + 0xa8) >> 6 & 0x180 |
             (ushort)((*(ushort *)(PTR_DAT_8009c318 + 0xac) & 0x100) >> 4) |
             (ushort)((*(ushort *)(PTR_DAT_8009c318 + 0xaa) & 0x3ff) >> 6) |
             (ushort)((*(ushort *)(PTR_DAT_8009c318 + 0xac) & 0x200) << 2);
  local_b8 = *(undefined2 *)(PTR_DAT_8009c318 + 0xae);
  local_b6 = *(undefined2 *)(PTR_DAT_8009c318 + 0xb0);
  local_c0 = 0x40;
  local_c2 = DAT_8009c320 + -0x30;
  bVar12 = (byte)((uVar10 & 0x3f) << (2 - (uVar2 >> 0xd & 3) & 0x1f));
  local_be = 0x100;
  local_ba = bVar12;
  local_b9 = bVar1;
  if (((int)DAT_8009c320 < (int)-(*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff)) ||
     ((int)local_c2 < (int)-(*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff))) goto LAB_80051428;
  if (0 < local_c2) {
    local_c2 = 0;
  }
  iVar3 = (int)local_c2;
  if (iVar3 < 0) {
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    local_b9 = (byte)iVar3;
    local_c2 = 0;
    iVar3 = 0;
  }
  iVar7 = (*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff) + (int)DAT_8009c320;
  if (iVar7 < 0x101) {
    if (iVar7 < iVar3 + 0x100) {
LAB_80051244:
      sVar11 = 0x100;
      iVar3 = (local_c2 + 0x100) -
              ((*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff) + (int)DAT_8009c320);
      if (iVar3 < 0x100) {
        sVar11 = (short)iVar3;
      }
      local_be = 0x100 - sVar11;
    }
  }
  else if (0x100 < iVar3 + 0x100) goto LAB_80051244;
  if ((*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff) < 0x101) {
    if ((*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff) < (uint)local_b9 + (uint)local_be) {
LAB_800512c0:
      iVar3 = ((uint)local_b9 + (uint)local_be) - (*(ushort *)(PTR_DAT_8009c318 + 0xa8) & 0x1fff);
      uVar10 = local_be;
      if (iVar3 < (int)(uint)local_be) {
        uVar10 = (ushort)iVar3;
      }
      local_be = local_be - uVar10;
    }
  }
  else if (0x100 < (uint)local_b9 + (uint)local_be) goto LAB_800512c0;
  iVar3 = (int)DAT_8009c31e / 10 + (*(ushort *)(PTR_DAT_8009c318 + 0xa6) / 0x500) * -0xa0;
  local_c4 = (ushort)iVar3;
  while (iVar3 * 0x10000 >> 0x10 < 0x140) {
    if (0 < (int)((int)(short)local_c4 + (uint)local_c0)) {
      FUN_80084978(&local_c8,DAT_8009c864,(1 << (*DAT_8009c864 & 0x1f)) - 1U & 0xffff);
    }
    uVar8 = (uint)local_ba + (uint)local_c0;
    uVar4 = *(ushort *)(PTR_DAT_8009c318 + 0xa6) / 10;
    if (uVar4 == 0) {
      trap(0x1c00);
    }
    if ((uVar4 == 0xffffffff) && (uVar8 == 0x80000000)) {
      trap(0x1800);
    }
    iVar3 = (uint)local_c4 + (uint)local_c0;
    local_c4 = (ushort)iVar3;
    local_ba = (char)(uVar8 % uVar4) + bVar12;
  }
LAB_80051428:
  if ((PTR_DAT_8009c318[0xa1] & 1) != 0) {
    FUN_80089ba8(&local_110,&local_12c,auStack_9c);
    FUN_80089ba8(&local_110,&local_12c,auStack_94);
    FUN_80089ba8(&local_110,&local_128,auStack_8c);
    FUN_80089ba8(&local_110,&local_128,auStack_84);
    FUN_80089ba8(&local_110,&local_128,auStack_78);
    FUN_80089ba8(&local_110,&local_128,auStack_70);
    FUN_80089ba8(&local_110,&local_124,auStack_68);
    FUN_80089ba8(&local_110,&local_124,auStack_60);
    FUN_80089ba8(&local_110,&local_124,auStack_54);
    FUN_80089ba8(&local_110,&local_124,auStack_4c);
    FUN_80089ba8(&local_110,local_120,auStack_44);
    FUN_80089ba8(&local_110,local_120,auStack_3c);
    local_99 = 0x38;
    local_75 = 0x38;
    local_51 = 0x38;
    local_9d = 8;
    local_79 = 8;
    local_55 = 8;
    local_108 = CONCAT22(sVar13,1000);
    local_104 = (uint)local_104._2_2_ << 0x10;
    local_f8 = CONCAT22(sVar13,0x640);
    local_f4 = (uint)local_f4._2_2_ << 0x10;
    local_e8 = CONCAT22(sVar13,0x898);
    local_e4 = (uint)local_e4._2_2_ << 0x10;
    local_d8 = CONCAT22(sVar13,0xaf0);
    local_d4 = (uint)local_d4._2_2_ << 0x10;
    local_100 = CONCAT22(sVar13,(undefined2)local_100);
    local_f0 = CONCAT22(sVar13,(undefined2)local_f0);
    local_e0 = CONCAT22(sVar13,(undefined2)local_e0);
    local_d0 = CONCAT22(sVar13,(undefined2)local_d0);
    uVar5 = FUN_8005c328();
    FUN_80085558(uVar5);
    iVar3 = 0x100;
    do {
      iVar7 = FUN_800866f8(iVar3);
      iVar6 = FUN_80086628(iVar3);
      iVar9 = iVar7 * 1000;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_100 = CONCAT22(local_100._2_2_,(short)(iVar9 >> 0xc));
      iVar9 = iVar6 * 1000;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_fc = CONCAT22(local_fc._2_2_,(short)(iVar9 >> 0xc));
      iVar9 = iVar7 * 0x640;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_f0 = CONCAT22(local_f0._2_2_,(short)(iVar9 >> 0xc));
      iVar9 = iVar6 * 0x640;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_ec = CONCAT22(local_ec._2_2_,(short)(iVar9 >> 0xc));
      iVar9 = iVar7 * 0x898;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_e0 = CONCAT22(local_e0._2_2_,(short)(iVar9 >> 0xc));
      iVar9 = iVar6 * 0x898;
      if (iVar9 < 0) {
        iVar9 = iVar9 + 0xfff;
      }
      local_dc = CONCAT22(local_dc._2_2_,(short)(iVar9 >> 0xc));
      iVar7 = iVar7 * 0xaf0;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0xfff;
      }
      local_d0 = CONCAT22(local_d0._2_2_,(short)(iVar7 >> 0xc));
      iVar6 = iVar6 * 0xaf0;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xfff;
      }
      local_cc = CONCAT22(local_cc._2_2_,(short)(iVar6 >> 0xc));
      iVar7 = FUN_80087a38(&local_108,&local_100,&local_f8,&local_f0,auStack_98,auStack_90,&local_88
                           ,&local_80,auStack_30,auStack_2c);
      iVar6 = FUN_80087a38(&local_e8,&local_e0,&local_d8,&local_d0,&local_50,&local_48,auStack_40,
                           auStack_38,auStack_28,auStack_24);
      local_74 = local_88;
      local_72 = local_86;
      local_6c = local_80;
      local_6a = local_7e;
      local_64 = local_50;
      local_62 = local_4e;
      local_5c = local_48;
      local_5a = local_46;
      if (iVar7 < 0) {
        if (-1 < iVar6) goto LAB_80051808;
      }
      else {
        FUN_800842a8(auStack_a0,DAT_8009c864,(1 << (*DAT_8009c864 & 0x1f)) - 1U & 0xffff);
LAB_80051808:
        FUN_800842a8(auStack_7c,DAT_8009c864,(1 << (*DAT_8009c864 & 0x1f)) - 1U & 0xffff);
        if (-1 < iVar6) {
          FUN_800842a8(auStack_58,DAT_8009c864,(1 << (*DAT_8009c864 & 0x1f)) - 1U & 0xffff);
        }
      }
      iVar3 = iVar3 + 0x100;
      local_108 = local_100;
      local_104 = local_fc;
      local_f8 = local_f0;
      local_f4 = local_ec;
      local_e8 = local_e0;
      local_e4 = local_dc;
      local_d8 = local_d0;
      local_d4 = local_cc;
    } while (iVar3 < 0x1001);
  }
  return;
}

