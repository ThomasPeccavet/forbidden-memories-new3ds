/* Analysis pseudo-C, not buildable source. */

uint FUN_8006b5b4(int *param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int *piVar3;
  short sVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  int *piVar14;
  int *piVar15;
  int iVar16;
  byte *pbVar17;
  byte *pbVar18;
  int *piVar19;
  int *piVar20;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined1 auStack_f0 [20];
  undefined1 auStack_dc [12];
  undefined1 auStack_d0 [4];
  byte local_cc;
  byte local_cb;
  byte local_ca;
  undefined2 local_c8;
  undefined2 local_c6;
  byte local_c4;
  byte local_c3;
  byte local_c2;
  undefined2 local_c0;
  undefined2 local_be;
  byte local_bc;
  byte local_bb;
  byte local_ba;
  undefined2 local_b8;
  undefined2 local_b6;
  undefined1 auStack_b0 [40];
  undefined4 local_88;
  undefined2 local_84;
  undefined2 local_82;
  undefined2 local_80;
  undefined2 local_7e;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined1 local_7a;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74;
  undefined1 auStack_70 [8];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 auStack_58 [6];
  ushort local_52;
  int local_50;
  undefined1 auStack_4c [4];
  uint local_48;
  undefined4 local_44;
  undefined2 *local_40;
  undefined1 *local_3c;
  undefined4 *local_38;
  int local_34;
  int local_30;
  
  local_40 = &local_78;
  FUN_8008f548(local_40,0,8);
  local_3c = auStack_70;
  FUN_8008f548(local_3c,0,8);
  local_68 = DAT_80011820;
  local_64 = DAT_80011824;
  local_60 = DAT_80011828;
  local_5c = DAT_8001182c;
  FUN_8005bed4();
  local_34 = FUN_8005bf24();
  local_38 = &local_68;
  if (-1 < param_2) {
    *param_1 = (int)&DAT_80092a08;
    uVar5 = FUN_8005bed4();
    FUN_8005afa4(uVar5,auStack_58);
    iVar13 = ((int)((uint)local_52 << 0x10) >> 0x10) - ((int)((uint)local_52 << 0x10) >> 0x1f) >> 1;
    iVar16 = (int)DAT_80092a1c;
    if ((DAT_80092a1c <= iVar13) && (iVar16 = 700, iVar13 < 0x2bd)) {
      iVar16 = iVar13;
    }
    iVar11 = (int)DAT_80092a1a;
    if ((iVar11 <= iVar13) && (iVar11 = 700, iVar13 < 0x2bd)) {
      iVar11 = iVar13;
    }
    *(undefined2 *)(param_1 + 1) = 0;
    *(short *)((int)param_1 + 6) = -(short)iVar11;
    *(undefined2 *)(param_1 + 2) = 0;
    sVar4 = (short)iVar16;
    *(undefined2 *)(param_1 + 3) = 0;
    *(undefined2 *)((int)param_1 + 0xe) = 0;
    *(short *)(param_1 + 4) = -sVar4;
    *(short *)(param_1 + 5) = -sVar4;
    *(undefined2 *)((int)param_1 + 0x16) = 0;
    *(undefined2 *)(param_1 + 6) = 0;
    *(undefined2 *)(param_1 + 7) = 0;
    *(undefined2 *)((int)param_1 + 0x1e) = 0;
    *(short *)(param_1 + 8) = sVar4;
    *(short *)(param_1 + 9) = sVar4;
    *(undefined2 *)((int)param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 10) = 0;
    iVar16 = 0;
    *(undefined2 *)(param_1 + 0xb) = 0;
    *(short *)((int)param_1 + 0x2e) = (short)iVar11;
    *(undefined2 *)(param_1 + 0xc) = 0;
    piVar10 = param_1 + 0x325;
    do {
      puVar6 = &DAT_80092a08 + iVar16;
      puVar1 = &DAT_80092a0e + iVar16;
      puVar2 = &DAT_80092a14 + iVar16;
      iVar16 = iVar16 + 1;
      FUN_8006c928(piVar10,*puVar6,*puVar1,*puVar2);
      piVar10 = piVar10 + 1;
    } while (iVar16 < 6);
    piVar15 = param_1 + 0xd;
    piVar14 = param_1 + 0x32b;
    iVar16 = 1;
    piVar12 = param_1 + 0x326;
    piVar10 = param_1 + 3;
    do {
      *piVar15 = (int)(param_1 + 1);
      *piVar14 = (int)(param_1 + 0x325);
      piVar15[1] = (int)piVar10;
      piVar14[1] = (int)piVar12;
      iVar13 = iVar16;
      if (iVar16 < 0) {
        iVar13 = iVar16 + 3;
      }
      iVar13 = iVar16 + (iVar13 >> 2) * -4;
      piVar15[2] = (int)(param_1 + iVar13 * 2 + 3);
      piVar15 = piVar15 + 3;
      piVar14[2] = (int)(param_1 + iVar13 + 0x326);
      piVar14 = piVar14 + 3;
      piVar12 = piVar12 + 1;
      iVar16 = iVar16 + 1;
      piVar10 = piVar10 + 2;
    } while (iVar16 < 5);
    iVar16 = 1;
    piVar12 = param_1 + 0x326;
    piVar10 = param_1 + 3;
    do {
      *piVar15 = (int)(param_1 + 0xb);
      *piVar14 = (int)(param_1 + 0x32a);
      iVar13 = iVar16;
      if (iVar16 < 0) {
        iVar13 = iVar16 + 3;
      }
      iVar13 = iVar16 + (iVar13 >> 2) * -4;
      piVar15[1] = (int)(param_1 + iVar13 * 2 + 3);
      piVar14[1] = (int)(param_1 + iVar13 + 0x326);
      piVar15[2] = (int)piVar10;
      piVar15 = piVar15 + 3;
      piVar14[2] = (int)piVar12;
      piVar14 = piVar14 + 3;
      piVar12 = piVar12 + 1;
      iVar16 = iVar16 + 1;
      piVar10 = piVar10 + 2;
    } while (iVar16 < 5);
    piVar15 = param_1 + 0xd;
    piVar14 = param_1 + 0x32b;
    iVar16 = 0;
    piVar20 = param_1 + 0x32d;
    piVar19 = param_1 + 0xf;
    piVar10 = param_1 + 0x343;
    piVar12 = param_1 + 0x25;
    do {
      piVar3 = piVar19 + -1;
      iVar11 = *piVar19;
      piVar19 = piVar19 + 3;
      iVar13 = *piVar15;
      piVar15 = piVar15 + 3;
      iVar16 = iVar16 + 1;
      FUN_8006c2d0(iVar13,*piVar3,iVar11,piVar12,2);
      piVar3 = piVar20 + -1;
      iVar11 = *piVar20;
      piVar20 = piVar20 + 3;
      iVar13 = *piVar14;
      piVar14 = piVar14 + 3;
      FUN_8006c74c(iVar13,*piVar3,iVar11,piVar10,2);
      piVar10 = piVar10 + 0x30;
      piVar12 = piVar12 + 0x60;
    } while (iVar16 < 8);
    param_1[0x4c4] = 0;
    iVar16 = (int)DAT_80092a20;
    *(undefined1 *)(param_1 + 0x4c3) = 0;
    *(undefined1 *)((int)param_1 + 0x130d) = 0;
    param_1[0x4c5] = iVar16;
    return 0;
  }
  iVar11 = *param_1;
  piVar10 = param_1 + 0x25;
  local_44 = FUN_8005c018();
  puVar7 = (undefined4 *)FUN_8005c328();
  local_110 = *puVar7;
  local_10c = puVar7[1];
  local_108 = puVar7[2];
  local_104 = puVar7[3];
  local_100 = puVar7[4];
  local_fc = puVar7[5];
  local_f8 = puVar7[6];
  local_f4 = puVar7[7];
  pbVar18 = (byte *)(param_1 + 0x343);
  FUN_80087158();
  FUN_80082e48(auStack_d0);
  FUN_80082ec8(auStack_b0);
  local_30 = 0;
  local_88 = 0x50000000;
  iVar13 = param_1[0x4c4];
  iVar16 = param_1[0x4c5];
  pbVar17 = (byte *)((int)param_1 + 0xd0e);
  local_78 = 0;
  local_74 = 0;
  local_76 = (undefined2)(iVar13 << 5);
  FUN_80085558(&local_110);
  uVar5 = FUN_8005bed4();
  FUN_8005c0b8(uVar5,local_3c);
  FUN_80085558(&local_110);
  FUN_800878f8(local_3c,auStack_dc,&local_50);
  FUN_80087cb8(local_40,auStack_f0);
  FUN_80087408(&local_110,auStack_f0);
  FUN_800875f8(auStack_f0,local_38);
  FUN_80085558(auStack_f0);
  do {
    iVar8 = FUN_80087ab8(piVar10,piVar10 + 2,piVar10 + 4,&local_c8,&local_c0,&local_b8,auStack_4c,
                         &local_48,&local_50);
    if ((iVar16 < 0) || (iVar9 = (int)*(short *)(iVar11 + 0x18), iVar9 <= iVar16)) {
      if ((iVar13 < 0) || (iVar9 = (int)*(short *)(iVar11 + 0x16), iVar9 <= iVar13)) {
        local_cc = *pbVar18;
        local_cb = pbVar17[-1];
        local_ca = *pbVar17;
        local_c4 = pbVar18[4];
        local_c3 = pbVar17[3];
        local_c2 = pbVar17[4];
        local_bc = pbVar18[8];
        local_bb = pbVar17[7];
        local_ba = pbVar17[8];
      }
      else {
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)*pbVar18 * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)pbVar17[-1] * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)*pbVar17 * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        local_cc = (byte)((int)((uint)*pbVar18 * iVar13) / iVar9);
        local_cb = (byte)((int)((uint)pbVar17[-1] * iVar13) / iVar9);
        local_ca = (byte)((int)((uint)*pbVar17 * iVar13) / iVar9);
        iVar9 = (int)*(short *)(iVar11 + 0x16);
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)pbVar18[4] * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)pbVar17[3] * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar9 == 0) {
          trap(0x1c00);
        }
        if ((iVar9 == -1) && ((uint)pbVar17[4] * iVar13 == -0x80000000)) {
          trap(0x1800);
        }
        local_c4 = (byte)((int)((uint)pbVar18[4] * iVar13) / iVar9);
        local_c3 = (byte)((int)((uint)pbVar17[3] * iVar13) / iVar9);
        local_c2 = (byte)((int)((uint)pbVar17[4] * iVar13) / iVar9);
        local_bc = local_c4;
        local_bb = local_c3;
        local_ba = local_c2;
      }
    }
    else {
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)*pbVar18 * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar17[-1] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)*pbVar17 * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      local_cc = (byte)((int)((uint)*pbVar18 * iVar16) / iVar9);
      local_cb = (byte)((int)((uint)pbVar17[-1] * iVar16) / iVar9);
      local_ca = (byte)((int)((uint)*pbVar17 * iVar16) / iVar9);
      iVar9 = (int)*(short *)(iVar11 + 0x18);
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar18[4] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar17[3] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar17[4] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      local_c4 = (byte)((int)((uint)pbVar18[4] * iVar16) / iVar9);
      local_c3 = (byte)((int)((uint)pbVar17[3] * iVar16) / iVar9);
      local_c2 = (byte)((int)((uint)pbVar17[4] * iVar16) / iVar9);
      iVar9 = (int)*(short *)(iVar11 + 0x18);
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar18[8] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar17[7] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar9 == 0) {
        trap(0x1c00);
      }
      if ((iVar9 == -1) && ((uint)pbVar17[8] * iVar16 == -0x80000000)) {
        trap(0x1800);
      }
      local_bc = (byte)((int)((uint)pbVar18[8] * iVar16) / iVar9);
      local_bb = (byte)((int)((uint)pbVar17[7] * iVar16) / iVar9);
      local_ba = (byte)((int)((uint)pbVar17[8] * iVar16) / iVar9);
    }
    pbVar18 = pbVar18 + 0xc;
    pbVar17 = pbVar17 + 0xc;
    if (((-1 < (int)local_48) && (-1 < local_50)) && (0 < iVar8)) {
      FUN_8004d5b8(auStack_d0,local_44,local_48 & 0xffff,1);
    }
    piVar10 = piVar10 + 6;
    local_30 = local_30 + 1;
  } while (local_30 < 0x80);
  if (iVar16 < 0) {
LAB_8006c088:
    if (-1 < iVar13) {
      iVar16 = (int)*(short *)(iVar11 + 0x16);
      iVar8 = iVar13 << 5;
      if (iVar13 < iVar16) {
        if (iVar16 == 0) {
          trap(0x1c00);
        }
        if ((iVar16 == -1) && (iVar8 == -0x80000000)) {
          trap(0x1800);
        }
        local_7c = (undefined1)(iVar8 / iVar16);
        iVar16 = (int)*(short *)(iVar11 + 0x16);
        if (iVar16 == 0) {
          trap(0x1c00);
        }
        if ((iVar16 == -1) && (iVar8 == -0x80000000)) {
          trap(0x1800);
        }
        local_7b = (undefined1)(iVar8 / iVar16);
        sVar4 = *(short *)(iVar11 + 0x16);
        goto code_r0x8006c11c;
      }
    }
    local_7c = 0x20;
    local_7b = 0x20;
    local_7a = 0x20;
  }
  else {
    iVar9 = (int)*(short *)(iVar11 + 0x18);
    iVar8 = iVar16 << 5;
    if (iVar9 <= iVar16) goto LAB_8006c088;
    if (iVar9 == 0) {
      trap(0x1c00);
    }
    if ((iVar9 == -1) && (iVar8 == -0x80000000)) {
      trap(0x1800);
    }
    local_7c = (undefined1)(iVar8 / iVar9);
    iVar16 = (int)*(short *)(iVar11 + 0x18);
    if (iVar16 == 0) {
      trap(0x1c00);
    }
    if ((iVar16 == -1) && (iVar8 == -0x80000000)) {
      trap(0x1800);
    }
    local_7b = (undefined1)(iVar8 / iVar16);
    sVar4 = *(short *)(iVar11 + 0x18);
code_r0x8006c11c:
    iVar16 = (int)sVar4;
    if (iVar16 == 0) {
      trap(0x1c00);
    }
    if ((iVar16 == -1) && (iVar8 == -0x80000000)) {
      trap(0x1800);
    }
    local_7a = (undefined1)(iVar8 / iVar16);
  }
  piVar12 = param_1 + 0xd;
  iVar16 = 0;
  piVar10 = param_1 + 0xf;
  do {
    iVar13 = FUN_80087ab8(*piVar12,piVar10[-1],*piVar10,&local_c8,&local_c0,&local_b8,auStack_4c,
                          &local_48,&local_50);
    if (((-1 < (int)local_48) && (-1 < local_50)) && (0 < iVar13)) {
      local_84 = local_c8;
      local_82 = local_c6;
      local_80 = local_c0;
      local_7e = local_be;
      FUN_80083f38(&local_88,local_44,local_48 & 0xffff);
      local_84 = local_b8;
      local_82 = local_b6;
      FUN_80083f38(&local_88,local_44,local_48 & 0xffff);
      local_80 = local_c8;
      local_7e = local_c6;
      FUN_80083f38(&local_88,local_44,local_48 & 0xffff);
    }
    piVar10 = piVar10 + 3;
    iVar16 = iVar16 + 1;
    piVar12 = piVar12 + 3;
  } while (iVar16 < 8);
  FUN_800871fc();
  param_1[0x4c4] = param_1[0x4c4] + local_34;
  if (param_2 == -2) {
    param_1[0x4c5] = param_1[0x4c5] - local_34;
  }
  return param_1[0x4c5] >> 0x1f & 2;
}

