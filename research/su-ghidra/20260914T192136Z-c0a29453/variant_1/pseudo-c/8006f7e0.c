/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80070aa8) */

undefined4 FUN_8006f7e0(short *param_1,int param_2)

{
  undefined1 uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  short *psVar14;
  int iVar15;
  short *psVar16;
  int iVar17;
  short sVar18;
  int iVar19;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined1 auStack_100 [20];
  undefined1 auStack_ec [12];
  undefined1 auStack_e0 [3];
  undefined1 local_dd;
  undefined1 local_dc;
  undefined1 local_db;
  undefined1 local_da;
  undefined1 local_d9;
  undefined1 auStack_d8 [4];
  undefined1 local_d4;
  char local_d3;
  short local_d2;
  undefined1 auStack_d0 [4];
  char local_cc;
  char local_cb;
  short local_ca;
  undefined1 auStack_c8 [4];
  undefined1 local_c4;
  char local_c3;
  undefined1 auStack_c0 [4];
  char local_bc;
  char local_bb;
  undefined1 auStack_b8 [3];
  undefined1 local_b5;
  undefined1 local_b4;
  undefined1 local_b3;
  undefined1 local_b2;
  undefined1 local_b1;
  undefined1 auStack_b0 [4];
  undefined1 local_ac;
  undefined1 local_ab;
  undefined1 local_aa;
  undefined1 auStack_a8 [4];
  byte local_a4;
  byte local_a3;
  byte local_a2;
  undefined1 auStack_a0 [4];
  byte local_9c;
  byte local_9b;
  byte local_9a;
  undefined1 auStack_98 [8];
  undefined1 auStack_90 [8];
  undefined1 auStack_88 [2];
  undefined2 local_86;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  short local_70 [8];
  short local_60 [4];
  short local_58 [4];
  int local_50;
  undefined1 auStack_4c [4];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  int local_38;
  short *local_34;
  int local_30;
  
  FUN_8008f548(auStack_90,0,8);
  FUN_8008f548(auStack_88,0,8);
  local_80 = DAT_80011850;
  local_7c = DAT_80011854;
  local_78 = DAT_80011858;
  local_74 = DAT_8001185c;
  local_48 = FUN_8005bed4();
  if (param_2 < 0) {
    local_44 = FUN_8005c018();
    FUN_8005bf24();
    FUN_8005cbf4(1);
    FUN_80087158();
    puVar10 = (undefined4 *)FUN_8005c328();
    local_120 = *puVar10;
    local_11c = puVar10[1];
    local_118 = puVar10[2];
    local_114 = puVar10[3];
    local_110 = puVar10[4];
    local_10c = puVar10[5];
    local_108 = puVar10[6];
    local_104 = puVar10[7];
    FUN_8005c0b8(local_48,auStack_88);
    local_86 = 0;
    FUN_80085558(&local_120);
    FUN_800878f8(auStack_88,auStack_ec,&local_50);
    FUN_80087cb8(auStack_90,auStack_100);
    FUN_800875f8(auStack_100,&local_80);
    FUN_80085558(auStack_100);
    local_dd = 9;
    local_d9 = 0x2c;
    local_ca = param_1[0x385];
    local_d2 = param_1[0x386];
    local_d4 = 0x40;
    local_c4 = 0x40;
    local_c3 = 0x3f;
    local_bb = 0x3f;
    local_d3 = 0;
    local_cc = 0x7f;
    local_cb = 0;
    local_bc = 0x7f;
    local_b5 = 8;
    local_b1 = 0x38;
    iVar19 = 0;
    if (param_1[0x380] != 0) {
      local_30 = 0;
      psVar16 = param_1;
      local_40 = &local_120;
      local_34 = param_1;
      do {
        iVar8 = local_30;
        if ((((char)psVar16[0x387] != '\0') || (*(char *)((int)psVar16 + 0x70f) != '\0')) ||
           ((char)psVar16[0x388] != '\0')) {
          local_dc = (undefined1)psVar16[0x387];
          local_db = *(undefined1 *)((int)psVar16 + 0x70f);
          local_da = (undefined1)psVar16[0x388];
          local_b4 = 0;
          local_b3 = 0;
          local_b2 = 0;
          local_ac = 0;
          local_ab = 0;
          local_aa = 0;
          if ((ushort)param_1[0x380] < 0x20) {
            local_a4 = *(byte *)(psVar16 + 0x387) >> 1;
            local_a3 = *(byte *)((int)psVar16 + 0x70f) >> 1;
            local_a2 = *(byte *)(psVar16 + 0x388) >> 1;
            local_9c = *(byte *)(psVar16 + 0x387) >> 1;
            local_9b = *(byte *)((int)psVar16 + 0x70f) >> 1;
            local_9a = *(byte *)(psVar16 + 0x388) >> 1;
          }
          else {
            local_a4 = *(byte *)(psVar16 + 0x387);
            local_a3 = *(byte *)((int)psVar16 + 0x70f);
            local_a2 = *(byte *)(psVar16 + 0x388);
            local_9c = *(byte *)(psVar16 + 0x387);
            local_9b = *(byte *)((int)psVar16 + 0x70f);
            local_9a = *(byte *)(psVar16 + 0x388);
          }
          iVar7 = 1;
          iVar17 = 0;
          iVar15 = -2;
          do {
            iVar11 = (int)(short)iVar7;
            iVar7 = -iVar11;
            if (iVar15 < 0) {
              local_70[1] = 0x80;
            }
            else {
              local_70[1] = 0xff80;
            }
            local_70[2] = 0;
            local_70[4] = 0;
            if (iVar15 < 0) {
              local_70[5] = 0x80;
            }
            else {
              local_70[5] = 0xff80;
            }
            iVar13 = 0;
            psVar14 = (short *)(iVar8 + (int)param_1);
            local_70[6] = 0;
            local_60[1] = 0;
            local_60[2] = 0;
            local_58[0] = 0;
            local_58[1] = 0;
            local_58[2] = 0;
            puVar10 = local_40;
            do {
              *(short *)(puVar10 + 0x2c) = *(short *)(puVar10 + 0x2c) + *psVar14;
              iVar13 = iVar13 + 1;
              *(short *)((int)puVar10 + 0xb2) = *(short *)((int)puVar10 + 0xb2) + psVar14[1];
              *(short *)(puVar10 + 0x2d) = *(short *)(puVar10 + 0x2d) + psVar14[2];
              puVar10 = puVar10 + 2;
            } while (iVar13 < 4);
            local_70[0] = -(short)(iVar11 * -0x10000 >> 9);
            local_60[0] = -(short)(iVar11 * -0x10000 >> 9);
            uVar12 = FUN_80087a38(local_70,local_70 + 4,local_60,local_58,auStack_d8,auStack_d0,
                                  auStack_c8,auStack_c0,auStack_4c,&local_50);
            if ((-1 < (int)uVar12) && (-1 < local_50)) {
              FUN_8004d5b8(auStack_e0,local_44,uVar12 & 0xffff,1);
            }
            iVar17 = iVar17 + 1;
            iVar15 = iVar15 + 1;
          } while (iVar17 < 4);
          sVar18 = psVar16[0x80];
          sVar2 = psVar16[0x81];
          local_70[2] = 0;
          sVar3 = psVar16[0x80];
          sVar4 = psVar16[0x81];
          local_70[6] = 0;
          sVar5 = psVar16[0x80];
          local_60[1] = 0;
          local_60[2] = 0;
          sVar6 = psVar16[0x80];
          iVar8 = 0;
          local_58[1] = 0;
          local_58[2] = 0;
          puVar10 = local_40;
          do {
            *(short *)(puVar10 + 0x2c) = *(short *)(puVar10 + 0x2c) + *local_34;
            iVar8 = iVar8 + 1;
            *(short *)((int)puVar10 + 0xb2) = *(short *)((int)puVar10 + 0xb2) + local_34[1];
            *(short *)(puVar10 + 0x2d) = *(short *)(puVar10 + 0x2d) + local_34[2];
            puVar10 = puVar10 + 2;
          } while (iVar8 < 4);
          local_70[0] = -sVar18;
          local_70[1] = -sVar2;
          local_70[4] = sVar3;
          local_70[5] = -sVar4;
          local_60[0] = -sVar5;
          local_58[0] = sVar6;
          uVar12 = FUN_80087a38(local_70,local_70 + 4,local_60,local_58,auStack_b0,auStack_a8,
                                auStack_a0,auStack_98,auStack_4c,&local_50);
          if ((-1 < (int)uVar12) && (-1 < local_50)) {
            FUN_8004d5b8(auStack_b8,local_44,uVar12 & 0xffff,1);
          }
          if (param_1[899] == 0) {
            psVar16[0x80] = psVar16[0x80] + 2;
            psVar16[0x81] = psVar16[0x81] + 0x80;
          }
          if (0x20 < psVar16[0x80]) {
            psVar16[0x80] = 0x20;
          }
          if (0x600 < psVar16[0x81]) {
            psVar16[0x81] = 0x600;
          }
          if (((ushort)param_1[0x380] < 0x20) || (param_1[899] == 1)) {
            if (*(byte *)(psVar16 + 0x387) < 0x10) {
              *(undefined1 *)(psVar16 + 0x387) = 0;
            }
            else {
              *(byte *)(psVar16 + 0x387) = *(byte *)(psVar16 + 0x387) - 0xf;
            }
            if (*(byte *)((int)psVar16 + 0x70f) < 0x10) {
              *(undefined1 *)((int)psVar16 + 0x70f) = 0;
            }
            else {
              *(byte *)((int)psVar16 + 0x70f) = *(byte *)((int)psVar16 + 0x70f) - 0xf;
            }
            if (*(byte *)(psVar16 + 0x388) < 0x10) goto LAB_80070240;
            *(byte *)(psVar16 + 0x388) = *(byte *)(psVar16 + 0x388) - 0xf;
          }
          else {
            if (*(byte *)(psVar16 + 0x387) < 7) {
              *(undefined1 *)(psVar16 + 0x387) = 0;
            }
            else {
              *(byte *)(psVar16 + 0x387) = *(byte *)(psVar16 + 0x387) - 4;
            }
            if (*(byte *)((int)psVar16 + 0x70f) < 7) {
              *(undefined1 *)((int)psVar16 + 0x70f) = 0;
            }
            else {
              *(byte *)((int)psVar16 + 0x70f) = *(byte *)((int)psVar16 + 0x70f) - 4;
            }
            if (*(byte *)(psVar16 + 0x388) < 7) {
LAB_80070240:
              *(undefined1 *)(psVar16 + 0x388) = 0;
            }
            else {
              *(byte *)(psVar16 + 0x388) = *(byte *)(psVar16 + 0x388) - 4;
            }
          }
          if (((((char)psVar16[0x387] == '\0') && (*(char *)((int)psVar16 + 0x70f) == '\0')) &&
              ((char)psVar16[0x388] == '\0')) && (param_1[899] == 0)) {
            iVar7 = FUN_8008f708();
            iVar8 = FUN_8008f708();
            iVar7 = iVar7 - iVar8;
            iVar8 = iVar7;
            if (iVar7 < 0) {
              iVar8 = iVar7 + 0xfff;
            }
            iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
            if (iVar8 < 0) {
              iVar8 = iVar8 + 0xfff;
            }
            *local_34 = (short)(iVar8 >> 0xc);
            local_34[1] = 0;
            iVar7 = FUN_8008f708();
            iVar8 = FUN_8008f708();
            iVar7 = iVar7 - iVar8;
            iVar8 = iVar7;
            if (iVar7 < 0) {
              iVar8 = iVar7 + 0xfff;
            }
            iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
            if (iVar8 < 0) {
              iVar8 = iVar8 + 0xfff;
            }
            local_34[2] = (short)(iVar8 >> 0xc);
            *(undefined1 *)(psVar16 + 0x387) = 0xc0;
            *(undefined1 *)((int)psVar16 + 0x70f) = 0xc0;
            *(undefined1 *)(psVar16 + 0x388) = 0xff;
            psVar16[0x80] = 8;
            psVar16[0x81] = 0x100;
          }
        }
        local_34 = local_34 + 4;
        local_30 = local_30 + 8;
        iVar19 = iVar19 + 1;
        psVar16 = psVar16 + 2;
      } while (iVar19 < (int)(uint)(ushort)param_1[0x380]);
    }
    local_d4 = 0x40;
    local_d3 = '@';
    local_cc = '\x7f';
    local_cb = '@';
    local_c4 = 0x40;
    local_c3 = '\x7f';
    local_bc = '\x7f';
    local_bb = '\x7f';
    iVar19 = 0;
    if (param_1[0x381] != 0) {
      local_3c = &local_120;
      local_38 = 0;
      psVar16 = param_1;
      psVar14 = param_1;
      do {
        iVar8 = local_38;
        if ((((char)psVar16[0x3c7] != '\0') || (*(char *)((int)psVar16 + 0x78f) != '\0')) ||
           ((char)psVar16[0x3c8] != '\0')) {
          local_dc = (undefined1)psVar16[0x3c7];
          local_db = *(undefined1 *)((int)psVar16 + 0x78f);
          iVar15 = 0;
          local_da = (undefined1)psVar16[0x3c8];
          iVar7 = -2;
          sVar18 = 1;
          do {
            if (iVar7 < 0) {
              local_70[1] = 0x50;
            }
            else {
              local_70[1] = -0x50;
            }
            local_70[2] = 0;
            local_70[4] = 0;
            if (iVar7 < 0) {
              local_70[5] = 0x50;
            }
            else {
              local_70[5] = -0x50;
            }
            iVar17 = 0;
            local_70[6] = 0;
            local_60[1] = 0;
            local_60[2] = 0;
            local_58[0] = 0;
            local_58[1] = 0;
            local_58[2] = 0;
            puVar10 = local_3c;
            do {
              *(short *)(puVar10 + 0x2c) =
                   *(short *)(puVar10 + 0x2c) + *(short *)((int)param_1 + iVar8 + 0x180);
              iVar17 = iVar17 + 1;
              *(short *)((int)puVar10 + 0xb2) =
                   *(short *)((int)puVar10 + 0xb2) + *(short *)((int)param_1 + iVar8 + 0x182);
              *(short *)(puVar10 + 0x2d) =
                   *(short *)(puVar10 + 0x2d) + *(short *)((int)param_1 + iVar8 + 0x184);
              puVar10 = puVar10 + 2;
            } while (iVar17 < 4);
            local_70[0] = sVar18 * 0x50;
            local_60[0] = sVar18 * 0x50;
            uVar12 = FUN_80087a38(local_70,local_70 + 4,local_60,local_58,auStack_d8,auStack_d0,
                                  auStack_c8,auStack_c0,auStack_4c,&local_50);
            if ((-1 < (int)uVar12) && (-1 < local_50)) {
              FUN_8004d5b8(auStack_e0,local_44,uVar12 & 0xffff,1);
            }
            iVar15 = iVar15 + 1;
            iVar7 = iVar7 + 1;
            sVar18 = -sVar18;
          } while (iVar15 < 4);
          if (*(byte *)(psVar16 + 0x3c7) < 0x20) {
            *(undefined1 *)(psVar16 + 0x3c7) = 0;
          }
          else {
            *(byte *)(psVar16 + 0x3c7) = *(byte *)(psVar16 + 0x3c7) - 0x1f;
          }
          if (*(byte *)((int)psVar16 + 0x78f) < 0x20) {
            *(undefined1 *)((int)psVar16 + 0x78f) = 0;
          }
          else {
            *(byte *)((int)psVar16 + 0x78f) = *(byte *)((int)psVar16 + 0x78f) - 0x1f;
          }
          if (*(byte *)(psVar16 + 0x3c8) < 0x20) {
            *(undefined1 *)(psVar16 + 0x3c8) = 0;
          }
          else {
            *(byte *)(psVar16 + 0x3c8) = *(byte *)(psVar16 + 0x3c8) - 0x1f;
          }
          if ((((char)psVar16[0x3c7] == '\0') && (*(char *)((int)psVar16 + 0x78f) == '\0')) &&
             ((char)psVar16[0x3c8] == '\0')) {
            iVar7 = FUN_8008f708();
            iVar8 = FUN_8008f708();
            iVar7 = iVar7 - iVar8;
            iVar8 = iVar7;
            if (iVar7 < 0) {
              iVar8 = iVar7 + 0xfff;
            }
            iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
            if (iVar8 < 0) {
              iVar8 = iVar8 + 0xfff;
            }
            psVar14[0xc0] = (short)(iVar8 >> 0xc);
            iVar7 = FUN_8008f708();
            iVar8 = iVar7;
            if (iVar7 < 0) {
              iVar8 = iVar7 + 0xfff;
            }
            iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * -0x80;
            if (iVar8 < 0) {
              iVar8 = iVar8 + 0xfff;
            }
            psVar14[0xc1] = (short)(iVar8 >> 0xc);
            iVar7 = FUN_8008f708();
            iVar8 = FUN_8008f708();
            iVar7 = iVar7 - iVar8;
            iVar8 = iVar7;
            if (iVar7 < 0) {
              iVar8 = iVar7 + 0xfff;
            }
            iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
            if (iVar8 < 0) {
              iVar8 = iVar8 + 0xfff;
            }
            psVar14[0xc2] = (short)(iVar8 >> 0xc);
            *(undefined1 *)(psVar16 + 0x3c7) = 0x40;
            *(undefined1 *)((int)psVar16 + 0x78f) = 0x40;
            *(undefined1 *)(psVar16 + 0x3c8) = 0x55;
          }
        }
        psVar14 = psVar14 + 4;
        local_38 = local_38 + 8;
        iVar19 = iVar19 + 1;
        psVar16 = psVar16 + 2;
      } while (iVar19 < (int)(uint)(ushort)param_1[0x381]);
    }
    if ((param_1[899] == 0) && ((param_1[0x382] & 1U) == 0)) {
      FUN_80048ae8(2,0xff,0);
      sVar18 = param_1[0x380];
      param_1[0x380] = sVar18 + 1U;
      if (0x20 < (ushort)(sVar18 + 1U)) {
        param_1[0x380] = 0x20;
      }
      if (((param_1[0x382] & 1U) == 0) &&
         (sVar18 = param_1[0x381], param_1[0x381] = sVar18 + 1U, 0x20 < (ushort)(sVar18 + 1U))) {
        param_1[0x381] = 0x20;
      }
    }
    uVar1 = (undefined1)param_1[900];
    FUN_8005c698(local_48,5,uVar1,uVar1,uVar1);
    if (*(byte *)(param_1 + 900) < 4) {
      *(undefined1 *)(param_1 + 900) = 0;
    }
    else {
      *(byte *)(param_1 + 900) = *(byte *)(param_1 + 900) - 2;
    }
    if (((param_1[0x380] == 0x20) && (param_1[0x381] == 0x20)) && ((char)param_1[900] == '\0')) {
      *(undefined1 *)(param_1 + 0x407) = 0xc0;
      *(undefined1 *)((int)param_1 + 0x80f) = 0xc0;
      *(undefined1 *)(param_1 + 0x408) = 0xff;
      *(undefined1 *)(param_1 + 0x3c7) = 0;
      *(undefined1 *)((int)param_1 + 0x78f) = 0;
      *(undefined1 *)(param_1 + 0x3c8) = 0;
      param_1[0x381] = 0;
      param_1[899] = 1;
      FUN_8005c698(local_48,5,0,0,0);
    }
    if (((param_1[0x407] != 0) || ((char)param_1[0x408] != '\0')) && (iVar19 = 0, param_1[899] == 1)
       ) {
      local_dc = (undefined1)param_1[0x407];
      local_db = *(undefined1 *)((int)param_1 + 0x80f);
      local_da = (undefined1)param_1[0x408];
      psVar16 = param_1;
      psVar14 = param_1;
      do {
        local_d4 = (undefined1)(((ushort)psVar16[0x340] & 1) << 5);
        local_d3 = (char)((ushort)psVar16[0x340] >> 1) * ' ' + '@';
        local_cc = ((byte)psVar16[0x340] & 1) * ' ' + '\x1f';
        local_cb = (char)((ushort)psVar16[0x340] >> 1) * ' ' + '@';
        local_c4 = (undefined1)(((ushort)psVar16[0x340] & 1) << 5);
        iVar8 = 0;
        local_c3 = (char)((ushort)psVar16[0x340] >> 1) * ' ' + '_';
        local_bc = ((byte)psVar16[0x340] & 1) * ' ' + '\x1f';
        local_bb = (char)((ushort)psVar16[0x340] >> 1) * ' ' + '_';
        local_70[0] = -0x10;
        local_70[1] = -0x10;
        local_70[2] = 0;
        local_70[4] = 0x10;
        local_70[5] = -0x10;
        local_70[6] = 0;
        local_60[0] = -0x10;
        local_60[1] = 0x10;
        local_60[2] = 0;
        local_58[0] = 0x10;
        local_58[1] = 0x10;
        local_58[2] = 0;
        puVar10 = &local_120;
        do {
          *(short *)(puVar10 + 0x2c) = *(short *)(puVar10 + 0x2c) + psVar14[0x140];
          iVar8 = iVar8 + 1;
          *(short *)((int)puVar10 + 0xb2) = *(short *)((int)puVar10 + 0xb2) + psVar14[0x141];
          *(short *)(puVar10 + 0x2d) = *(short *)(puVar10 + 0x2d) + psVar14[0x142];
          puVar10 = puVar10 + 2;
        } while (iVar8 < 4);
        uVar12 = FUN_80087a38(local_70,local_70 + 4,local_60,local_58,auStack_d8,auStack_d0,
                              auStack_c8,auStack_c0,auStack_4c,&local_50);
        if ((-1 < (int)uVar12) && (-1 < local_50)) {
          FUN_8004d5b8(auStack_e0,local_44,uVar12 & 0xffff,1);
        }
        psVar14[0x140] = psVar14[0x140] + psVar14[0x240];
        psVar14[0x141] = psVar14[0x141] + psVar14[0x241];
        psVar14[0x142] = psVar14[0x142] + psVar14[0x242];
        psVar16[0x340] =
             (short)((ushort)psVar16[0x340] + 1) +
             (short)((int)((ushort)psVar16[0x340] + 1) >> 2) * -4;
        psVar16 = psVar16 + 1;
        iVar19 = iVar19 + 1;
        psVar14 = psVar14 + 4;
      } while (iVar19 < 0x40);
      if (*(byte *)(param_1 + 0x407) < 10) {
        *(undefined1 *)(param_1 + 0x407) = 0;
      }
      else {
        *(byte *)(param_1 + 0x407) = *(byte *)(param_1 + 0x407) - 8;
      }
      if (*(byte *)((int)param_1 + 0x80f) < 10) {
        *(undefined1 *)((int)param_1 + 0x80f) = 0;
      }
      else {
        *(byte *)((int)param_1 + 0x80f) = *(byte *)((int)param_1 + 0x80f) - 8;
      }
      if (*(byte *)(param_1 + 0x408) < 10) {
        *(undefined1 *)(param_1 + 0x408) = 0;
      }
      else {
        *(byte *)(param_1 + 0x408) = *(byte *)(param_1 + 0x408) - 8;
      }
    }
    param_1[0x382] = param_1[0x382] + 1;
    FUN_800871fc();
    uVar9 = 0;
    if ((((param_1[0x3c7] == 0) && (uVar9 = 0, (char)param_1[0x3c8] == '\0')) &&
        (uVar9 = 0, param_1[0x407] == 0)) && (uVar9 = 2, (char)param_1[0x408] != '\0')) {
      uVar9 = 0;
    }
  }
  else {
    iVar19 = 0;
    param_1[0x385] = 0xae;
    param_1[0x386] = 0x3d28;
    psVar16 = param_1;
    psVar14 = param_1;
    do {
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      *psVar14 = (short)(iVar8 >> 0xc);
      psVar14[1] = 0;
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar14[2] = (short)(iVar8 >> 0xc);
      *(undefined1 *)(psVar16 + 0x387) = 0x60;
      *(undefined1 *)((int)psVar16 + 0x70f) = 0x60;
      *(undefined1 *)(psVar16 + 0x388) = 0x7f;
      psVar16[0x80] = 8;
      psVar16[0x81] = 0x100;
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar14[0xc0] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * -0x80;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar14[0xc1] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x140;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar14[0xc2] = (short)(iVar8 >> 0xc);
      *(undefined1 *)(psVar16 + 0x3c7) = 0x40;
      *(undefined1 *)((int)psVar16 + 0x78f) = 0x40;
      *(undefined1 *)(psVar16 + 0x3c8) = 0x55;
      psVar16 = psVar16 + 2;
      iVar19 = iVar19 + 1;
      psVar14 = psVar14 + 4;
    } while (iVar19 < 0x20);
    iVar19 = 0;
    psVar16 = param_1;
    psVar14 = param_1;
    do {
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0xa0;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar16[0x140] = (short)(iVar8 >> 0xc);
      psVar16[0x141] = 0;
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0xa0;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar16[0x142] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x18;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar16[0x240] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * -0x18;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar16[0x241] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = FUN_8008f708();
      iVar7 = iVar7 - iVar8;
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 0xfff;
      }
      iVar8 = (iVar7 + (iVar8 >> 0xc) * -0x1000) * 0x18;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      psVar16[0x242] = (short)(iVar8 >> 0xc);
      iVar7 = FUN_8008f708();
      iVar8 = iVar7;
      if (iVar7 < 0) {
        iVar8 = iVar7 + 3;
      }
      psVar14[0x340] = (short)iVar7 + (short)(iVar8 >> 2) * -4;
      psVar14 = psVar14 + 1;
      iVar19 = iVar19 + 1;
      psVar16 = psVar16 + 4;
    } while (iVar19 < 0x40);
    uVar9 = 0;
    *(undefined1 *)(param_1 + 0x407) = 0;
    *(undefined1 *)((int)param_1 + 0x80f) = 0;
    *(undefined1 *)(param_1 + 0x408) = 0;
    param_1[0x380] = 0;
    param_1[0x381] = 0;
    param_1[899] = 0;
    param_1[0x382] = 0;
    *(undefined1 *)(param_1 + 900) = 0x80;
  }
  return uVar9;
}

