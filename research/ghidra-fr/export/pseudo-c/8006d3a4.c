/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8006ed68) */
/* WARNING: Removing unreachable block (ram,0x8006eab8) */
/* WARNING: Removing unreachable block (ram,0x8006f618) */

undefined4 FUN_8006d3a4(int *param_1,int param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  char cVar10;
  ushort uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  undefined4 uVar17;
  ushort *puVar18;
  int *piVar19;
  int *piVar20;
  int iVar21;
  int iVar22;
  int *piVar23;
  short sVar24;
  short sVar25;
  undefined1 uVar26;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined1 auStack_e0 [20];
  undefined1 auStack_cc [12];
  undefined1 auStack_c0 [3];
  undefined1 local_bd;
  byte local_bc;
  byte local_bb;
  byte local_ba;
  undefined1 local_b9;
  undefined1 auStack_b8 [4];
  char local_b4;
  char local_b3;
  undefined2 local_b2;
  undefined1 auStack_b0 [4];
  char local_ac;
  char local_ab;
  undefined2 local_aa;
  undefined1 auStack_a8 [4];
  char local_a4;
  char local_a3;
  undefined1 auStack_a0 [4];
  char local_9c;
  char local_9b;
  undefined2 local_98;
  ushort local_96;
  undefined2 local_94;
  ushort local_90;
  short local_8e;
  ushort local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  short local_78 [8];
  short local_68;
  undefined2 local_66;
  short local_64;
  short local_60;
  undefined2 local_5e;
  short local_5c;
  int local_58;
  undefined1 auStack_54 [4];
  undefined4 local_50;
  undefined4 local_4c;
  ushort local_48;
  int local_40;
  int local_3c;
  int local_38;
  int *local_34;
  int *local_30;
  
  FUN_8008f548(&local_98,0,8);
  FUN_8008f548(&local_90,0,8);
  local_88 = DAT_80011840;
  local_84 = DAT_80011844;
  local_80 = DAT_80011848;
  local_7c = DAT_8001184c;
  local_50 = FUN_8005bed4();
  if (-1 < param_2) {
    iVar21 = 0;
    puVar18 = &DAT_80092a30;
    *param_1 = (int)&DAT_80092af4;
    *(undefined2 *)((int)param_1 + 0xd8a) = 0xae;
    *(undefined2 *)(param_1 + 0x363) = 0x3d28;
    piVar19 = param_1;
    do {
      iVar21 = iVar21 + 1;
      *(ushort *)((int)piVar19 + 0xd8e) =
           (*puVar18 & 3) << 7 | (short)(puVar18[3] & 0x100) >> 4 | 0x20U |
           (ushort)((puVar18[2] & 0x3ff) >> 6) | (puVar18[3] & 0x200) << 2;
      puVar1 = puVar18 + 9;
      puVar2 = puVar18 + 8;
      puVar18 = puVar18 + 0xe;
      *(ushort *)(piVar19 + 0x364) = *puVar1 << 6 | *puVar2 >> 4 & 0x3f;
      piVar19 = piVar19 + 1;
    } while (iVar21 < 1);
    FUN_8005afa4(local_50,&local_90);
    iVar22 = 0;
    iVar21 = 0;
    piVar19 = param_1;
    piVar20 = param_1;
    do {
      iVar12 = FUN_800868a8(iVar21);
      uVar11 = local_8c;
      if ((short)local_8c < (short)local_90) {
        uVar11 = local_90;
      }
      iVar12 = (int)(short)uVar11 * iVar12 * 2;
      if (iVar12 < 0) {
        iVar12 = iVar12 + 0xfff;
      }
      *(short *)(piVar19 + 2) = (short)(iVar12 >> 0xc);
      *(undefined2 *)((int)piVar19 + 10) = 0;
      iVar12 = FUN_80086b38(iVar21);
      uVar11 = local_8c;
      if ((short)local_8c < (short)local_90) {
        uVar11 = local_90;
      }
      iVar12 = (int)(short)uVar11 * iVar12 * 2;
      if (iVar12 < 0) {
        iVar12 = iVar12 + 0xfff;
      }
      *(short *)(piVar19 + 3) = (short)(iVar12 >> 0xc);
      *(short *)(piVar19 + 8) = (short)(-(int)(short)piVar19[2] / 0x30);
      *(undefined2 *)((int)piVar19 + 0x22) = 0;
      *(short *)(piVar19 + 9) = (short)(-(int)(short)piVar19[3] / 0x30);
      *(byte *)((int)piVar20 + 0xd92) = *(byte *)(*param_1 + iVar22) >> 3;
      iVar21 = iVar21 + 0x555;
      *(byte *)((int)piVar20 + 0xd93) = *(byte *)(*param_1 + iVar22 + 3) >> 3;
      iVar12 = *param_1 + iVar22;
      iVar22 = iVar22 + 1;
      *(byte *)(piVar20 + 0x365) = *(byte *)(iVar12 + 6) >> 3;
      piVar20 = piVar20 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar22 < 3);
    if ((short)local_8c < (short)local_90) {
      local_8c = local_90;
    }
    uVar13 = (((int)((uint)local_8c << 0x10) >> 0x10) - ((int)((uint)local_8c << 0x10) >> 0x1f) >> 1
             ) + 200;
    *(short *)(param_1 + 0x360) = (short)uVar13;
    iVar21 = 0;
    if (0x200 < (uVar13 & 0xffff)) {
      *(undefined2 *)(param_1 + 0x360) = 0x200;
    }
    *(undefined1 *)((int)param_1 + 0xd9e) = 0x80;
    *(undefined1 *)((int)param_1 + 0xd9f) = 0x80;
    *(undefined1 *)(param_1 + 0x368) = 0x80;
    piVar19 = param_1;
    piVar20 = param_1;
    do {
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar12 = iVar12 + (iVar22 >> 0xc) * -0x1000;
      iVar14 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar14 = iVar14 - iVar22;
      iVar22 = iVar14;
      if (iVar14 < 0) {
        iVar22 = iVar14 + 0xfff;
      }
      iVar16 = (uint)*(ushort *)(param_1 + 0x360) * iVar12;
      local_38 = iVar14 + (iVar22 >> 0xc) * -0x1000;
      if (iVar16 < 0) {
        iVar16 = iVar16 + 0xfff;
      }
      *(short *)(piVar19 + 0xe) = (short)(iVar16 >> 0xc);
      *(undefined2 *)((int)piVar19 + 0x3a) = 0;
      iVar22 = (uint)*(ushort *)(param_1 + 0x360) * local_38;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0xf) = (short)(iVar22 >> 0xc);
      iVar12 = iVar12 * 0x18;
      if (iVar12 < 0) {
        iVar12 = iVar12 + 0xfff;
      }
      *(short *)(piVar19 + 0x8e) = (short)(iVar12 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * -0x18;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)((int)piVar19 + 0x23a) = (short)(iVar22 >> 0xc);
      iVar22 = local_38 * 0x18;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x8f) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 3;
      }
      *(short *)(piVar20 + 0x310) = (short)iVar12 + (short)(iVar22 >> 2) * -4;
      piVar20 = (int *)((int)piVar20 + 2);
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 0x40);
    iVar21 = 0;
    piVar19 = param_1;
    piVar20 = param_1;
    piVar23 = param_1;
    do {
      iVar12 = iVar21 << 7;
      iVar22 = FUN_800868a8(iVar12);
      iVar22 = (uint)*(ushort *)(param_1 + 0x360) * iVar22;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x10e) = (short)(iVar22 >> 0xc);
      *(undefined2 *)((int)piVar19 + 0x43a) = 0;
      iVar22 = FUN_80086b38(iVar12);
      iVar22 = (uint)*(ushort *)(param_1 + 0x360) * iVar22;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x10f) = (short)(iVar22 >> 0xc);
      iVar22 = -(int)(short)piVar19[0x10e];
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0x7f;
      }
      *(short *)(piVar19 + 0x14e) = (short)(iVar22 >> 7);
      *(undefined2 *)((int)piVar19 + 0x53a) = 0xfff0;
      iVar22 = -(int)(short)piVar19[0x10f];
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0x7f;
      }
      *(short *)(piVar19 + 0x14f) = (short)(iVar22 >> 7);
      iVar22 = FUN_800868a8(iVar12);
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0x7f;
      }
      *(short *)(piVar19 + 0x18e) = (short)(iVar22 >> 7);
      *(undefined2 *)((int)piVar19 + 0x63a) = 0;
      iVar22 = FUN_80086b38(iVar12);
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0x7f;
      }
      *(short *)(piVar19 + 399) = (short)(iVar22 >> 7);
      iVar12 = FUN_8008f708();
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 7;
      }
      *(short *)(piVar23 + 0x330) = (short)iVar12 + (short)(iVar22 >> 3) * -8;
      *(undefined1 *)((int)piVar20 + 0xda2) = 1;
      *(undefined1 *)((int)piVar20 + 0xda3) = 1;
      *(undefined1 *)(piVar20 + 0x369) = 1;
      piVar20 = piVar20 + 1;
      piVar23 = (int *)((int)piVar23 + 2);
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 0x20);
    iVar21 = 0;
    piVar19 = param_1;
    do {
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0xa0;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x1ce) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0xa0;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)((int)piVar19 + 0x73a) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0xa0;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x1cf) = (short)(iVar22 >> 0xc);
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 0x20);
    iVar21 = 0;
    piVar19 = param_1;
    piVar20 = param_1;
    do {
      *(undefined2 *)(piVar19 + 0x20e) = 0;
      *(undefined2 *)((int)piVar19 + 0x83a) = 0;
      *(undefined2 *)(piVar19 + 0x20f) = 0;
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0x60;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x28e) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0x18;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)((int)piVar19 + 0xa3a) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = FUN_8008f708();
      iVar12 = iVar12 - iVar22;
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 0xfff;
      }
      iVar22 = (iVar12 + (iVar22 >> 0xc) * -0x1000) * 0x60;
      if (iVar22 < 0) {
        iVar22 = iVar22 + 0xfff;
      }
      *(short *)(piVar19 + 0x28f) = (short)(iVar22 >> 0xc);
      iVar12 = FUN_8008f708();
      iVar22 = iVar12;
      if (iVar12 < 0) {
        iVar22 = iVar12 + 3;
      }
      *(short *)(piVar20 + 0x340) = (short)iVar12 + (short)(iVar22 >> 2) * -4;
      piVar20 = (int *)((int)piVar20 + 2);
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 0x40);
    *(undefined1 *)((int)param_1 + 0xe22) = 0x80;
    *(undefined1 *)((int)param_1 + 0xe23) = 0x40;
    *(undefined1 *)(param_1 + 0x389) = 0x79;
    FUN_8005c0b8(local_50,&local_98);
    local_96 = 0;
    *(undefined2 *)(param_1 + 0x30e) = local_98;
    *(undefined2 *)((int)param_1 + 0xc3a) = 0;
    *(undefined2 *)((int)param_1 + 0xd82) = 0;
    *(undefined2 *)(param_1 + 0x361) = 0;
    param_1[1] = 0;
    *(undefined2 *)((int)param_1 + 0xd86) = 1;
    *(undefined1 *)(param_1 + 0x362) = 0;
    *(undefined2 *)(param_1 + 0x30f) = local_94;
    FUN_80048ae8(0,0xff,0);
    return 0;
  }
  local_4c = FUN_8005c018();
  FUN_8005bf24();
  FUN_8005cbf4(1);
  FUN_80087158();
  puVar15 = (undefined4 *)FUN_8005c328();
  local_100 = *puVar15;
  local_fc = puVar15[1];
  local_f8 = puVar15[2];
  local_f4 = puVar15[3];
  local_f0 = puVar15[4];
  local_ec = puVar15[5];
  local_e8 = puVar15[6];
  local_e4 = puVar15[7];
  FUN_8005c0b8(local_50,&local_90);
  local_8e = 0;
  *(ushort *)(param_1 + 0x30e) = local_90;
  *(undefined2 *)((int)param_1 + 0xc3a) = 0;
  *(ushort *)(param_1 + 0x30f) = local_8c;
  if (*(short *)((int)param_1 + 0xd82) == 0) {
    local_98 = 0;
    local_94 = 0;
    local_96 = (short)param_1[1] * 0xa0 & 0xfff;
  }
  FUN_80085558(&local_100);
  FUN_800878f8(param_1 + 0x30e,auStack_cc,&local_58);
  FUN_80087cb8(&local_98,auStack_e0);
  FUN_80087408(&local_100,auStack_e0);
  FUN_800875f8(auStack_e0,&local_88);
  FUN_80085558(auStack_e0);
  local_bd = 9;
  local_b9 = 0x2c;
  local_aa = *(undefined2 *)((int)param_1 + 0xd8a);
  local_b2 = (undefined2)param_1[0x363];
  local_b4 = '\0';
  local_b3 = '\0';
  local_ac = '?';
  local_ab = '\0';
  local_a4 = '\0';
  local_a3 = '?';
  local_9c = '?';
  local_9b = '?';
  if (*(short *)((int)param_1 + 0xd82) == 0) {
    iVar21 = 0;
    piVar19 = param_1;
    piVar20 = param_1;
    do {
      if (((*(char *)((int)piVar20 + 0xd92) != '\0') || (*(char *)((int)piVar20 + 0xd93) != '\0'))
         || ((char)piVar20[0x365] != '\0')) {
        local_48 = 1;
        local_bc = *(undefined1 *)((int)piVar20 + 0xd92);
        iVar22 = 0;
        local_bb = *(undefined1 *)((int)piVar20 + 0xd93);
        local_ba = (byte)piVar20[0x365];
        local_34 = piVar19;
        local_30 = piVar19;
        do {
          iVar12 = 0;
          local_40 = iVar22 + -2;
          local_48 = -local_48;
          local_3c = (int)(short)local_48;
          local_38 = iVar22;
          do {
            iVar22 = 0;
            sVar25 = -1;
            sVar24 = 1;
            do {
              sVar4 = (short)local_3c;
              sVar5 = (short)iVar12;
              sVar7 = sVar24;
              if (local_40 < 0) {
                sVar7 = sVar25;
              }
              sVar8 = sVar24;
              if (local_40 < 0) {
                sVar8 = sVar25;
              }
              sVar6 = (short)iVar22;
              sVar9 = sVar6;
              if (local_40 < 0) {
                sVar9 = -sVar6;
              }
              if (local_40 < 0) {
                sVar6 = -sVar6;
              }
              local_78[0] = sVar4 * -(*(ushort *)(param_1 + 0x360) >> 2) * (sVar5 + 1) +
                            (short)local_34[2];
              local_78[1] = *(undefined2 *)((int)piVar19 + 10);
              local_78[2] = -(*(ushort *)(param_1 + 0x360) >> 2) * sVar7 + (short)piVar19[3];
              local_78[4] = sVar4 * -(*(ushort *)(param_1 + 0x360) >> 2) * sVar5 +
                            (short)local_34[2];
              local_78[5] = *(undefined2 *)((int)piVar19 + 10);
              local_78[6] = -(*(ushort *)(param_1 + 0x360) >> 2) * sVar8 + (short)piVar19[3];
              local_68 = sVar4 * -(*(ushort *)(param_1 + 0x360) >> 2) * (sVar5 + 1) +
                         (short)local_34[2];
              local_66 = *(undefined2 *)((int)piVar19 + 10);
              local_64 = -(*(ushort *)(param_1 + 0x360) >> 2) * sVar9 + (short)piVar19[3];
              local_60 = sVar4 * -(*(ushort *)(param_1 + 0x360) >> 2) * sVar5 + (short)local_34[2];
              local_5e = *(undefined2 *)((int)piVar19 + 10);
              local_5c = -(*(ushort *)(param_1 + 0x360) >> 2) * sVar6 + (short)piVar19[3];
              local_b4 = ('\x03' - (char)iVar12) * '\x10';
              local_b3 = ('\x03' - (char)iVar22) * '\x10';
              local_ac = local_b4 + '\x0f';
              local_a3 = local_b3 + '\x0f';
              local_ab = local_b3;
              local_a4 = local_b4;
              local_9c = local_ac;
              local_9b = local_a3;
              uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                                    auStack_a8,auStack_a0,auStack_54,&local_58);
              if ((-1 < (int)uVar13) && (-1 < local_58)) {
                FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
              }
              sVar25 = sVar25 + -1;
              iVar22 = iVar22 + 1;
              sVar24 = sVar24 + 1;
            } while (iVar22 < 4);
            iVar12 = iVar12 + 1;
          } while (iVar12 < 4);
          iVar22 = local_38 + 1;
        } while (iVar22 < 4);
        iVar22 = (int)(short)local_30[2];
        if (iVar22 < 0) {
          iVar22 = -iVar22;
        }
        if (iVar22 < 0x21) {
          iVar22 = (int)*(short *)((int)local_30 + 10);
          if (iVar22 < 0) {
            iVar22 = -iVar22;
          }
          if (0x20 < iVar22) goto LAB_8006e1c0;
          iVar22 = (int)(short)local_30[3];
          if (iVar22 < 0) {
            iVar22 = -iVar22;
          }
          if (0x20 < iVar22) goto LAB_8006e1c0;
          if (*(short *)((int)param_1 + 0xd82) == 0) {
            *(undefined2 *)((int)param_1 + 0xd82) = 1;
          }
          *(undefined2 *)(local_30 + 2) = 0;
          *(undefined2 *)((int)local_30 + 10) = 0;
          *(undefined2 *)(local_30 + 3) = 0;
        }
        else {
LAB_8006e1c0:
          *(short *)(local_30 + 2) = (short)local_30[2] + (short)local_30[8];
          *(short *)((int)local_30 + 10) =
               *(short *)((int)local_30 + 10) + *(short *)((int)local_30 + 0x22);
          *(short *)(local_30 + 3) = (short)local_30[3] + (short)local_30[9];
        }
        piVar19 = local_30;
        if (*(short *)((int)param_1 + 0xd82) == 0) {
          bVar3 = *(byte *)(*param_1 + iVar21) >> 1;
          if ((int)(uint)*(byte *)((int)piVar20 + 0xd92) < (int)(bVar3 - 9)) {
            *(byte *)((int)piVar20 + 0xd92) = *(byte *)((int)piVar20 + 0xd92) + 8;
          }
          else {
            *(byte *)((int)piVar20 + 0xd92) = bVar3;
          }
          bVar3 = *(byte *)(*param_1 + iVar21 + 3) >> 1;
          if ((int)(uint)*(byte *)((int)piVar20 + 0xd93) < (int)(bVar3 - 9)) {
            *(byte *)((int)piVar20 + 0xd93) = *(byte *)((int)piVar20 + 0xd93) + 8;
          }
          else {
            *(byte *)((int)piVar20 + 0xd93) = bVar3;
          }
          bVar3 = *(byte *)(*param_1 + iVar21 + 6) >> 1;
          if ((int)(uint)*(byte *)(piVar20 + 0x365) < (int)(bVar3 - 9)) {
            *(byte *)(piVar20 + 0x365) = *(byte *)(piVar20 + 0x365) + 8;
          }
          else {
            *(byte *)(piVar20 + 0x365) = bVar3;
          }
        }
        else {
          *(undefined1 *)((int)param_1 + 0xd92) = 0x80;
          *(undefined1 *)((int)param_1 + 0xd93) = 0x20;
          *(undefined1 *)(param_1 + 0x365) = 0x20;
          *(undefined1 *)((int)param_1 + 0xd96) = 0x20;
          *(undefined1 *)((int)param_1 + 0xd97) = 0x80;
          *(undefined1 *)(param_1 + 0x366) = 0x20;
          *(undefined1 *)((int)param_1 + 0xd9a) = 0x20;
          *(undefined1 *)((int)param_1 + 0xd9b) = 0x20;
          *(undefined1 *)(param_1 + 0x367) = 0x80;
        }
      }
      piVar20 = piVar20 + 1;
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 3);
    if (*(short *)((int)param_1 + 0xd82) != 0) goto LAB_8006e324;
  }
  else {
LAB_8006e324:
    if (((param_1[0x367] & 0xffff0000U) != 0) || ((char)param_1[0x368] != '\0')) {
      local_bc = *(undefined1 *)((int)param_1 + 0xd9e);
      local_bb = *(undefined1 *)((int)param_1 + 0xd9f);
      local_48 = 1;
      local_ba = (byte)param_1[0x368];
      iVar21 = 0;
      do {
        iVar22 = 0;
        iVar12 = iVar21 + -2;
        uVar11 = -local_48;
        local_38 = iVar21;
        local_48 = uVar11;
        do {
          iVar21 = 0;
          sVar25 = -1;
          sVar24 = 1;
          do {
            local_60 = (short)iVar22;
            local_78[0] = uVar11 * -(*(ushort *)(param_1 + 0x360) >> 2) * (local_60 + 1);
            local_78[1] = 0;
            local_78[2] = sVar24;
            if (iVar12 < 0) {
              local_78[2] = sVar25;
            }
            local_78[2] = -(*(ushort *)(param_1 + 0x360) >> 2) * local_78[2];
            local_78[4] = uVar11 * -(*(ushort *)(param_1 + 0x360) >> 2) * local_60;
            local_78[5] = 0;
            local_78[6] = sVar24;
            if (iVar12 < 0) {
              local_78[6] = sVar25;
            }
            local_78[6] = -(*(ushort *)(param_1 + 0x360) >> 2) * local_78[6];
            local_68 = uVar11 * -(*(ushort *)(param_1 + 0x360) >> 2) * (local_60 + 1);
            local_66 = 0;
            local_5c = (short)iVar21;
            local_64 = local_5c;
            if (iVar12 < 0) {
              local_64 = -local_5c;
            }
            local_64 = -(*(ushort *)(param_1 + 0x360) >> 2) * local_64;
            local_60 = uVar11 * -(*(ushort *)(param_1 + 0x360) >> 2) * local_60;
            local_5e = 0;
            if (iVar12 < 0) {
              local_5c = -local_5c;
            }
            local_5c = -(*(ushort *)(param_1 + 0x360) >> 2) * local_5c;
            local_b4 = ('\x03' - (char)iVar22) * '\x10';
            local_b3 = ('\x03' - (char)iVar21) * '\x10';
            local_ac = local_b4 + '\x0f';
            local_a3 = local_b3 + '\x0f';
            local_ab = local_b3;
            local_a4 = local_b4;
            local_9c = local_ac;
            local_9b = local_a3;
            uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                                  auStack_a8,auStack_a0,auStack_54,&local_58);
            if ((-1 < (int)uVar13) && (-1 < local_58)) {
              FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
            }
            sVar25 = sVar25 + -1;
            iVar21 = iVar21 + 1;
            sVar24 = sVar24 + 1;
          } while (iVar21 < 4);
          iVar22 = iVar22 + 1;
        } while (iVar22 < 4);
        iVar21 = local_38 + 1;
      } while (iVar21 < 4);
      if (*(ushort *)(param_1 + 0x361) < 2) {
        if (*(short *)((int)param_1 + 0xd82) == 1) {
          cVar10 = *(byte *)((int)param_1 + 0xd9e) + 8;
          if (0xf5 < *(byte *)((int)param_1 + 0xd9e)) {
            cVar10 = -1;
          }
          *(char *)((int)param_1 + 0xd9e) = cVar10;
          cVar10 = *(byte *)((int)param_1 + 0xd9f) + 8;
          if (0xf5 < *(byte *)((int)param_1 + 0xd9f)) {
            cVar10 = -1;
          }
          *(char *)((int)param_1 + 0xd9f) = cVar10;
          cVar10 = *(byte *)(param_1 + 0x368) + 8;
          if (0xf5 < *(byte *)(param_1 + 0x368)) {
            cVar10 = -1;
          }
          *(char *)(param_1 + 0x368) = cVar10;
          *(short *)(param_1 + 0x360) = (short)param_1[0x360] + 4;
          if (((param_1[0x367] & 0xffff0000U) == 0xffff0000) && ((char)param_1[0x368] == -1)) {
            *(undefined2 *)((int)param_1 + 0xd82) = 2;
          }
        }
        else if (*(short *)((int)param_1 + 0xd82) == 2) {
          cVar10 = -0x80;
          if (0x88 < *(byte *)((int)param_1 + 0xd9e)) {
            cVar10 = *(byte *)((int)param_1 + 0xd9e) - 8;
          }
          *(char *)((int)param_1 + 0xd9e) = cVar10;
          cVar10 = -0x80;
          if (0x88 < *(byte *)((int)param_1 + 0xd9f)) {
            cVar10 = *(byte *)((int)param_1 + 0xd9f) - 8;
          }
          *(char *)((int)param_1 + 0xd9f) = cVar10;
          cVar10 = -0x80;
          if (0x88 < *(byte *)(param_1 + 0x368)) {
            cVar10 = *(byte *)(param_1 + 0x368) - 8;
          }
          *(char *)(param_1 + 0x368) = cVar10;
          *(short *)(param_1 + 0x360) = (short)param_1[0x360] + -2;
          if (((param_1[0x367] & 0xffff0000U) == 0x80800000) && ((char)param_1[0x368] == -0x80)) {
            *(undefined2 *)((int)param_1 + 0xd82) = 1;
          }
        }
      }
      else {
        if (*(byte *)((int)param_1 + 0xd9e) < 9) {
          *(undefined1 *)((int)param_1 + 0xd9e) = 0;
        }
        else {
          *(byte *)((int)param_1 + 0xd9e) = *(byte *)((int)param_1 + 0xd9e) - 8;
        }
        if (*(byte *)((int)param_1 + 0xd9f) < 9) {
          *(undefined1 *)((int)param_1 + 0xd9f) = 0;
        }
        else {
          *(byte *)((int)param_1 + 0xd9f) = *(byte *)((int)param_1 + 0xd9f) - 8;
        }
        if (*(byte *)(param_1 + 0x368) < 9) {
          *(undefined1 *)(param_1 + 0x368) = 0;
        }
        else {
          *(byte *)(param_1 + 0x368) = *(byte *)(param_1 + 0x368) - 8;
        }
        *(short *)(param_1 + 0x360) = (short)param_1[0x360] + 2;
      }
    }
    if (((((param_1[0x364] & 0xffff0000U) != 0) || ((char)param_1[0x365] != '\0')) &&
        (((param_1[0x365] & 0xffff0000U) != 0 || ((char)param_1[0x366] != '\0')))) &&
       (((param_1[0x366] & 0xffff0000U) != 0 || ((char)param_1[0x367] != '\0')))) {
      FUN_80085558(&local_100);
      FUN_800878f8(param_1 + 0x30e,auStack_cc,&local_58);
      FUN_80087cb8(&local_98,auStack_e0);
      FUN_800875f8(auStack_e0,&local_88);
      FUN_80085558(auStack_e0);
      iVar21 = 0;
      piVar19 = param_1;
      piVar20 = param_1;
      do {
        iVar22 = iVar21 % 3;
        local_bc = *(undefined1 *)((int)param_1 + iVar22 * 4 + 0xd92);
        local_bb = *(undefined1 *)((int)param_1 + iVar22 * 4 + 0xd93);
        local_ba = (byte)param_1[iVar22 + 0x365];
        local_b4 = (char)((*(ushort *)(piVar19 + 0x310) & 1) << 5);
        local_b3 = (char)(*(ushort *)(piVar19 + 0x310) >> 1) * ' ' + '@';
        local_ac = ((byte)(short)piVar19[0x310] & 1) * ' ' + '\x1f';
        local_ab = (char)(*(ushort *)(piVar19 + 0x310) >> 1) * ' ' + '@';
        local_a4 = (char)((*(ushort *)(piVar19 + 0x310) & 1) << 5);
        iVar22 = 0;
        local_a3 = (char)(*(ushort *)(piVar19 + 0x310) >> 1) * ' ' + '_';
        local_9c = ((byte)(short)piVar19[0x310] & 1) * ' ' + '\x1f';
        local_9b = (char)(*(ushort *)(piVar19 + 0x310) >> 1) * ' ' + '_';
        local_78[0] = -0x20;
        local_78[1] = 0xffe0;
        local_78[2] = 0;
        local_78[4] = 0x20;
        local_78[5] = 0xffe0;
        local_78[6] = 0;
        local_68 = -0x20;
        local_66 = 0x20;
        local_64 = 0;
        local_60 = 0x20;
        local_5e = 0x20;
        local_5c = 0;
        puVar15 = &local_100;
        do {
          *(short *)(puVar15 + 0x22) = *(short *)(puVar15 + 0x22) + (short)piVar20[0xe];
          iVar22 = iVar22 + 1;
          *(short *)((int)puVar15 + 0x8a) =
               *(short *)((int)puVar15 + 0x8a) + *(short *)((int)piVar20 + 0x3a);
          *(short *)(puVar15 + 0x23) = *(short *)(puVar15 + 0x23) + (short)piVar20[0xf];
          puVar15 = puVar15 + 2;
        } while (iVar22 < 4);
        uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                              auStack_a8,auStack_a0,auStack_54,&local_58);
        if ((-1 < (int)uVar13) && (-1 < local_58)) {
          FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
        }
        *(short *)(piVar20 + 0xe) = (short)piVar20[0xe] + (short)piVar20[0x8e];
        *(short *)((int)piVar20 + 0x3a) =
             *(short *)((int)piVar20 + 0x3a) + *(short *)((int)piVar20 + 0x23a);
        *(short *)(piVar20 + 0xf) = (short)piVar20[0xf] + (short)piVar20[0x8f];
        *(short *)(piVar19 + 0x310) =
             (short)(*(ushort *)(piVar19 + 0x310) + 1) +
             (short)((int)(*(ushort *)(piVar19 + 0x310) + 1) >> 2) * -4;
        piVar19 = (int *)((int)piVar19 + 2);
        iVar21 = iVar21 + 1;
        piVar20 = piVar20 + 2;
      } while (iVar21 < 0x40);
      piVar19 = param_1;
      do {
        if (*(byte *)((int)piVar19 + 0xd92) < 0x10) {
          *(undefined1 *)((int)piVar19 + 0xd92) = 0;
        }
        else {
          *(byte *)((int)piVar19 + 0xd92) = *(byte *)((int)piVar19 + 0xd92) - 0xf;
        }
        if (*(byte *)((int)piVar19 + 0xd93) < 0x10) {
          *(undefined1 *)((int)piVar19 + 0xd93) = 0;
        }
        else {
          *(byte *)((int)piVar19 + 0xd93) = *(byte *)((int)piVar19 + 0xd93) - 0xf;
        }
        if (*(byte *)(piVar19 + 0x365) < 0x10) {
          *(undefined1 *)(piVar19 + 0x365) = 0;
        }
        else {
          *(byte *)(piVar19 + 0x365) = *(byte *)(piVar19 + 0x365) - 0xf;
        }
        piVar19 = piVar19 + 1;
      } while ((int)piVar19 < (int)(param_1 + 3));
    }
    local_aa = *(undefined2 *)((int)param_1 + 0xd8e);
    local_b2 = (undefined2)param_1[0x364];
    local_78[0] = -0x40;
    local_78[1] = 0xff00;
    local_78[2] = 0;
    local_78[4] = 0x40;
    local_78[5] = 0xff00;
    local_78[6] = 0;
    local_68 = -0x40;
    local_66 = 0;
    local_64 = 0;
    local_60 = 0x40;
    local_5e = 0;
    local_5c = 0;
    iVar21 = 0;
    uVar13 = 0;
    if (*(short *)((int)param_1 + 0xd86) != 0) {
      piVar19 = param_1;
      piVar20 = param_1;
      piVar23 = param_1;
      do {
        if (((*(char *)((int)piVar19 + 0xda2) != '\0') || (*(char *)((int)piVar19 + 0xda3) != '\0'))
           || ((char)piVar19[0x369] != '\0')) {
          local_90 = (short)param_1[0x30e] + (short)piVar20[0x10e];
          local_8e = *(short *)((int)param_1 + 0xc3a) + *(short *)((int)piVar20 + 0x43a);
          local_8c = (short)param_1[0x30f] + (short)piVar20[0x10f];
          FUN_80085558(&local_100);
          FUN_800878f8(&local_90,auStack_cc,&local_58);
          FUN_80087cb8(&local_98,auStack_e0);
          FUN_800875f8(auStack_e0,&local_88);
          FUN_80085558(auStack_e0);
          local_b3 = '\0';
          local_b4 = (char)(short)piVar23[0x330] << 5;
          local_ab = '\0';
          local_ac = (char)(short)piVar23[0x330] * ' ' + '\x1f';
          local_a3 = '?';
          local_a4 = (char)(short)piVar23[0x330] << 5;
          local_9b = '?';
          local_9c = (char)(short)piVar23[0x330] * ' ' + '\x1f';
          local_bc = *(undefined1 *)((int)piVar19 + 0xda2);
          local_bb = *(undefined1 *)((int)piVar19 + 0xda3);
          local_ba = (byte)piVar19[0x369];
          uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                                auStack_a8,auStack_a0,auStack_54,&local_58);
          if ((-1 < (int)uVar13) && (-1 < local_58)) {
            FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
          }
          *(short *)(piVar23 + 0x330) =
               (short)(*(ushort *)(piVar23 + 0x330) + 1) +
               (short)((int)(*(ushort *)(piVar23 + 0x330) + 1) >> 3) * -8;
          if (*(ushort *)(param_1 + 0x361) < 2) {
            cVar10 = *(byte *)((int)piVar19 + 0xda2) + 0x1f;
            if (0x60 < *(byte *)((int)piVar19 + 0xda2)) {
              cVar10 = -0x80;
            }
            *(char *)((int)piVar19 + 0xda2) = cVar10;
            cVar10 = *(byte *)((int)piVar19 + 0xda3) + 0x1f;
            if (0x60 < *(byte *)((int)piVar19 + 0xda3)) {
              cVar10 = -0x80;
            }
            *(char *)((int)piVar19 + 0xda3) = cVar10;
            cVar10 = *(byte *)(piVar19 + 0x369) + 0x1f;
            if (0x60 < *(byte *)(piVar19 + 0x369)) {
              cVar10 = -0x80;
            }
            *(char *)(piVar19 + 0x369) = cVar10;
          }
          sVar24 = (short)param_1[0x361];
          if (sVar24 == 1) {
            *(short *)(piVar20 + 0x10e) = (short)piVar20[0x10e] + (short)piVar20[0x14e];
            *(short *)((int)piVar20 + 0x43a) =
                 *(short *)((int)piVar20 + 0x43a) + *(short *)((int)piVar20 + 0x53a);
            *(short *)(piVar20 + 0x10f) = (short)piVar20[0x10f] + (short)piVar20[0x14f];
            sVar24 = (short)param_1[0x361];
          }
          if (sVar24 == 2) {
            *(short *)(piVar20 + 0x10e) = (short)piVar20[0x10e] + (short)piVar20[0x18e];
            *(short *)((int)piVar20 + 0x43a) =
                 *(short *)((int)piVar20 + 0x43a) + *(short *)((int)piVar20 + 0x63a);
            *(short *)(piVar20 + 0x10f) = (short)piVar20[0x10f] + (short)piVar20[399];
            *(short *)((int)piVar20 + 0x63a) = *(short *)((int)piVar20 + 0x63a) + 2;
            if (*(byte *)((int)piVar19 + 0xda2) < 9) {
              *(undefined1 *)((int)piVar19 + 0xda2) = 0;
            }
            else {
              *(byte *)((int)piVar19 + 0xda2) = *(byte *)((int)piVar19 + 0xda2) - 8;
            }
            if (*(byte *)((int)piVar19 + 0xda3) < 9) {
              *(undefined1 *)((int)piVar19 + 0xda3) = 0;
            }
            else {
              *(byte *)((int)piVar19 + 0xda3) = *(byte *)((int)piVar19 + 0xda3) - 8;
            }
            if (*(byte *)(piVar19 + 0x369) < 9) {
              *(undefined1 *)(piVar19 + 0x369) = 0;
            }
            else {
              *(byte *)(piVar19 + 0x369) = *(byte *)(piVar19 + 0x369) - 8;
            }
          }
        }
        piVar19 = piVar19 + 1;
        piVar20 = piVar20 + 2;
        iVar21 = iVar21 + 1;
        piVar23 = (int *)((int)piVar23 + 2);
      } while (iVar21 < (int)(uint)*(ushort *)((int)param_1 + 0xd86));
      uVar13 = (uint)*(ushort *)((int)param_1 + 0xd86);
    }
    if (((0x40 < *(byte *)((int)param_1 + (uVar13 - 1) * 4 + 0xda2)) ||
        (0x40 < *(byte *)((int)param_1 + (uVar13 - 1) * 4 + 0xda3))) ||
       (0x40 < *(byte *)(param_1 + uVar13 + 0x368))) {
      uVar11 = *(ushort *)(param_1 + 0x361);
      if (uVar11 != 0) goto LAB_8006efe0;
      if ((uint)*(ushort *)((int)param_1 + 0xd86) % 3 == 0) {
        FUN_80048ae8(1,0xff,0);
      }
      uVar11 = *(short *)((int)param_1 + 0xd86) + 1;
      *(ushort *)((int)param_1 + 0xd86) = uVar11;
      if (0x20 < uVar11) {
        *(undefined2 *)((int)param_1 + 0xd86) = 0x20;
        *(undefined2 *)(param_1 + 0x361) = 1;
      }
    }
  }
  uVar11 = *(ushort *)(param_1 + 0x361);
LAB_8006efe0:
  if ((1 < uVar11) && (((param_1[0x388] & 0xffff0000U) != 0 || ((char)param_1[0x389] != '\0')))) {
    local_aa = *(undefined2 *)((int)param_1 + 0xd8a);
    local_b2 = (undefined2)param_1[0x363];
    local_48 = 1;
    local_90 = *(ushort *)(param_1 + 0x30e);
    iVar21 = 0;
    local_8e = *(short *)((int)param_1 + 0xc3a) + -0x220;
    local_8c = *(ushort *)(param_1 + 0x30f);
    FUN_80085558(&local_100);
    FUN_800878f8(&local_90,auStack_cc,&local_58);
    FUN_80087cb8(&local_98,auStack_e0);
    FUN_800875f8(auStack_e0,&local_88);
    FUN_80085558(auStack_e0);
    do {
      iVar22 = (int)(short)local_48;
      local_48 = -local_48;
      local_78[0] = -(short)(iVar22 * -0x10000 >> 9);
      local_78[1] = 0xff80;
      if (iVar21 + -2 < 0) {
        local_78[1] = 0x80;
      }
      local_78[2] = 0;
      local_78[4] = 0;
      if (iVar21 + -2 < 0) {
        local_78[5] = 0x80;
      }
      else {
        local_78[5] = 0xff80;
      }
      local_78[6] = 0;
      local_66 = 0;
      local_64 = 0;
      local_60 = 0;
      local_5e = 0;
      local_5c = 0;
      local_68 = -(short)((int)((uint)local_48 << 0x10) >> 9);
      local_bc = *(undefined1 *)((int)param_1 + 0xe22);
      local_bb = *(undefined1 *)((int)param_1 + 0xe23);
      local_ba = (byte)param_1[0x389];
      local_a3 = 0x3f;
      local_9b = 0x3f;
      local_b4 = 0x40;
      local_b3 = 0;
      local_ac = 0x7f;
      local_ab = 0;
      local_a4 = 0x40;
      local_9c = 0x7f;
      uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                            auStack_a8,auStack_a0,auStack_54,&local_58);
      if ((-1 < (int)uVar13) && (-1 < local_58)) {
        FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
      }
      local_bc = *(byte *)((int)param_1 + 0xe22) >> 1;
      local_bb = *(byte *)((int)param_1 + 0xe23) >> 1;
      local_b4 = 0x40;
      local_b3 = 0x40;
      local_ac = 0x7f;
      local_ab = 0x40;
      local_a4 = 0x40;
      local_a3 = 0x7f;
      local_9c = 0x7f;
      local_9b = 0x7f;
      local_ba = *(byte *)(param_1 + 0x389) >> 1;
      uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                            auStack_a8,auStack_a0,auStack_54,&local_58);
      if ((-1 < (int)uVar13) && (-1 < local_58)) {
        FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
      }
      iVar21 = iVar21 + 1;
    } while (iVar21 < 4);
    local_b3 = 0x80;
    local_ab = 0x80;
    local_a3 = 0xff;
    local_9b = 0xff;
    local_b4 = 0;
    local_ac = 0x1f;
    local_a4 = 0;
    local_9c = 0x1f;
    local_78[0] = -4;
    local_78[1] = 0;
    local_78[2] = 0;
    local_78[4] = 4;
    local_78[5] = 0;
    local_78[6] = 0;
    local_bc = *(byte *)((int)param_1 + 0xe22) >> 2;
    iVar21 = 0;
    local_bb = *(byte *)((int)param_1 + 0xe23) >> 2;
    local_ba = *(byte *)(param_1 + 0x389) >> 2;
    piVar19 = param_1;
    do {
      local_68 = (short)piVar19[0x1ce] + -2;
      local_66 = *(undefined2 *)((int)piVar19 + 0x73a);
      local_64 = (short)piVar19[0x1cf];
      local_60 = (short)piVar19[0x1ce] + 2;
      local_5e = *(undefined2 *)((int)piVar19 + 0x73a);
      local_5c = (short)piVar19[0x1cf];
      uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                            auStack_a8,auStack_a0,auStack_54,&local_58);
      if ((-1 < (int)uVar13) && (-1 < local_58)) {
        FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
      }
      iVar21 = iVar21 + 1;
      piVar19 = piVar19 + 2;
    } while (iVar21 < 0x20);
    iVar21 = 0;
    piVar19 = param_1;
    piVar20 = param_1;
    do {
      local_bc = *(undefined1 *)((int)param_1 + 0xe22);
      local_bb = *(undefined1 *)((int)param_1 + 0xe23);
      local_ba = (byte)param_1[0x389];
      local_b4 = (char)((*(ushort *)(piVar19 + 0x340) & 1) << 5);
      local_b3 = (char)(*(ushort *)(piVar19 + 0x340) >> 1) * ' ' + '@';
      local_ac = ((byte)(short)piVar19[0x340] & 1) * ' ' + '\x1f';
      local_ab = (char)(*(ushort *)(piVar19 + 0x340) >> 1) * ' ' + '@';
      local_a4 = (char)((*(ushort *)(piVar19 + 0x340) & 1) << 5);
      iVar22 = 0;
      local_a3 = (char)(*(ushort *)(piVar19 + 0x340) >> 1) * ' ' + '_';
      local_9c = ((byte)(short)piVar19[0x340] & 1) * ' ' + '\x1f';
      local_9b = (char)(*(ushort *)(piVar19 + 0x340) >> 1) * ' ' + '_';
      local_78[0] = -0x20;
      local_78[1] = 0xffe0;
      local_78[2] = 0;
      local_78[4] = 0x20;
      local_78[5] = 0xffe0;
      local_78[6] = 0;
      local_68 = -0x20;
      local_66 = 0x20;
      local_64 = 0;
      local_60 = 0x20;
      local_5e = 0x20;
      local_5c = 0;
      puVar15 = &local_100;
      do {
        *(short *)(puVar15 + 0x22) = *(short *)(puVar15 + 0x22) + (short)piVar20[0x20e];
        iVar22 = iVar22 + 1;
        *(short *)((int)puVar15 + 0x8a) =
             *(short *)((int)puVar15 + 0x8a) + *(short *)((int)piVar20 + 0x83a);
        *(short *)(puVar15 + 0x23) = *(short *)(puVar15 + 0x23) + (short)piVar20[0x20f];
        puVar15 = puVar15 + 2;
      } while (iVar22 < 4);
      uVar13 = FUN_80087a38(local_78,local_78 + 4,&local_68,&local_60,auStack_b8,auStack_b0,
                            auStack_a8,auStack_a0,auStack_54,&local_58);
      if ((-1 < (int)uVar13) && (-1 < local_58)) {
        FUN_8004d5b8(auStack_c0,local_4c,uVar13 & 0xffff,1);
      }
      *(short *)(piVar20 + 0x20e) = (short)piVar20[0x20e] + (short)piVar20[0x28e];
      *(short *)((int)piVar20 + 0x83a) =
           *(short *)((int)piVar20 + 0x83a) + *(short *)((int)piVar20 + 0xa3a);
      *(short *)(piVar20 + 0x20f) = (short)piVar20[0x20f] + (short)piVar20[0x28f];
      *(short *)(piVar19 + 0x340) =
           (short)(*(ushort *)(piVar19 + 0x340) + 1) +
           (short)((int)(*(ushort *)(piVar19 + 0x340) + 1) >> 2) * -4;
      piVar19 = (int *)((int)piVar19 + 2);
      iVar21 = iVar21 + 1;
      *(short *)((int)piVar20 + 0xa3a) = *(short *)((int)piVar20 + 0xa3a) + 2;
      piVar20 = piVar20 + 2;
    } while (iVar21 < 0x40);
    if (*(byte *)((int)param_1 + 0xe22) < 0x10) {
      *(undefined1 *)((int)param_1 + 0xe22) = 0;
    }
    else {
      *(byte *)((int)param_1 + 0xe22) = *(byte *)((int)param_1 + 0xe22) - 0xf;
    }
    if (*(byte *)((int)param_1 + 0xe23) < 0x10) {
      *(undefined1 *)((int)param_1 + 0xe23) = 0;
    }
    else {
      *(byte *)((int)param_1 + 0xe23) = *(byte *)((int)param_1 + 0xe23) - 0xf;
    }
    if (*(byte *)(param_1 + 0x389) < 0x10) {
      *(undefined1 *)(param_1 + 0x389) = 0;
    }
    else {
      *(byte *)(param_1 + 0x389) = *(byte *)(param_1 + 0x389) - 0xf;
    }
  }
  uVar17 = 5;
  if ((char)param_1[0x362] < '\0') {
    uVar17 = 0;
    uVar26 = 0x80;
  }
  else {
    uVar26 = (undefined1)param_1[0x362];
  }
  FUN_8005c698(local_50,uVar17,uVar26,uVar26,uVar26);
  if ((short)param_1[0x361] != 0) {
    if (*(byte *)(param_1 + 0x362) < 0x7c) {
      *(byte *)(param_1 + 0x362) = *(byte *)(param_1 + 0x362) + 4;
    }
    else {
      *(undefined1 *)(param_1 + 0x362) = 0x80;
      *(undefined2 *)(param_1 + 0x361) = 2;
    }
  }
  param_1[1] = param_1[1] + 1;
  FUN_800871fc();
  uVar17 = 0;
  if ((((((param_1[0x388] & 0xffff0000U) == 0) && (uVar17 = 0, (char)param_1[0x389] == '\0')) &&
       (uVar17 = 0, (param_1[0x368] & 0xffff0000U) == 0)) &&
      ((uVar17 = 0, (char)param_1[0x369] == '\0' &&
       (uVar17 = 0, (param_1[0x367] & 0xffff0000U) == 0)))) &&
     (uVar17 = 2, (char)param_1[0x368] != '\0')) {
    uVar17 = 0;
  }
  return uVar17;
}

