/* Analysis pseudo-C, not buildable source. */

int FUN_8006c9a8(undefined4 *param_1,int param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int iVar15;
  int iVar16;
  byte *pbVar17;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  undefined4 local_38c;
  undefined1 auStack_388 [20];
  undefined1 auStack_374 [12];
  undefined1 auStack_368 [4];
  undefined1 local_364;
  undefined1 local_363;
  undefined1 local_362;
  undefined2 local_360;
  undefined2 local_35e;
  undefined1 local_35c;
  undefined1 local_35b;
  undefined1 local_35a;
  undefined2 local_358;
  undefined2 local_356;
  undefined1 local_354;
  undefined1 local_353;
  undefined1 local_352;
  undefined2 local_350;
  undefined2 local_34e;
  undefined1 auStack_348 [40];
  undefined2 local_320;
  undefined2 local_31e;
  undefined2 local_31c;
  undefined1 auStack_318 [8];
  int local_310;
  int local_30c;
  int local_308;
  undefined4 local_304;
  short local_300;
  short local_2fe;
  short local_2fc;
  undefined2 local_2e0 [136];
  undefined2 local_1d0 [68];
  undefined1 auStack_148 [136];
  ushort local_c0;
  ushort local_be;
  ushort local_bc;
  uint local_38;
  undefined4 local_34;
  byte local_30;
  
  FUN_8008f548(&local_320,0,8);
  FUN_8008f548(auStack_318,0,8);
  local_310 = DAT_80011830;
  local_30c = DAT_80011834;
  local_308 = DAT_80011838;
  local_304 = DAT_8001183c;
  FUN_8005bed4();
  local_30 = FUN_8005bf24();
  if (-1 < param_2) {
    *param_1 = &DAT_80092a24;
    uVar5 = FUN_8005bed4();
    FUN_8005afa4(uVar5,&local_300);
    sVar4 = local_2fc;
    if (local_2fc <= local_2fe) {
      sVar4 = local_2fe;
    }
    sVar1 = local_2fe;
    if (sVar4 == local_2fc) {
      sVar1 = local_2fc;
      local_2fe = sVar4;
    }
    if (local_2fe < local_300) {
      sVar1 = local_300;
    }
    iVar6 = sVar1 * 5;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 3;
    }
    iVar6 = iVar6 >> 2;
    iVar8 = (int)DAT_80092a28;
    if ((DAT_80092a28 <= iVar6) && (iVar8 = 700, iVar6 < 0x2bd)) {
      iVar8 = iVar6;
    }
    iVar6 = 0;
    puVar13 = param_1 + 4;
    sVar4 = (short)((ulonglong)((longlong)iVar8 * 0x55555556) >> 0x20) - (short)(iVar8 >> 0x1f);
    *(short *)(param_1 + 1) = sVar4;
    *(short *)((int)param_1 + 6) = sVar4;
    *(undefined2 *)(param_1 + 2) = 0;
    puVar9 = param_1 + 3;
    do {
      puVar14 = puVar9;
      iVar11 = iVar6 << 7;
      iVar7 = FUN_800868a8(iVar11);
      iVar7 = iVar8 * iVar7;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0xfff;
      }
      *(short *)puVar14 = (short)(iVar7 >> 0xc);
      iVar7 = FUN_80086b38(iVar11);
      iVar7 = iVar8 * iVar7;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0xfff;
      }
      *(short *)((int)puVar13 + -2) = (short)(iVar7 >> 0xc);
      iVar7 = FUN_80086b38(iVar11);
      iVar7 = iVar8 * iVar7;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0x7fff;
      }
      *(short *)puVar13 = (short)(iVar7 >> 0xf);
      puVar13 = puVar13 + 2;
      iVar6 = iVar6 + 1;
      puVar9 = puVar14 + 2;
    } while (iVar6 < 0x21);
    iVar7 = 0;
    puVar14 = puVar14 + 3;
    iVar6 = (iVar8 << 2) / 5;
    do {
      iVar11 = iVar7 << 7;
      iVar8 = FUN_800868a8(iVar11);
      iVar8 = iVar6 * iVar8;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      *(short *)puVar9 = (short)(iVar8 >> 0xc);
      iVar8 = FUN_80086b38(iVar11);
      iVar8 = iVar6 * iVar8;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0xfff;
      }
      *(short *)((int)puVar14 + -2) = (short)(iVar8 >> 0xc);
      iVar8 = FUN_80086b38(iVar11);
      iVar8 = iVar6 * iVar8;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0x7fff;
      }
      *(short *)puVar14 = (short)(iVar8 >> 0xf);
      puVar14 = puVar14 + 2;
      iVar7 = iVar7 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar7 < 0x21);
    *(char *)((int)param_1 + 0x21e) = ((char)(param_2 % 10) + '\x06') * '\x11';
    *(char *)(param_1 + 0x87) = ((char)((param_2 - param_2 % 100) / 100) + '\x06') * '\x11';
    *(char *)((int)param_1 + 0x21d) =
         ((char)((param_2 % 100 - param_2 % 10) / 10) + '\x06') * '\x11';
    iVar6 = (int)DAT_80092a2a;
    param_1[0x8a] = 0;
    *(undefined1 *)(param_1 + 0x8b) = 0;
    param_1[0x89] = iVar6;
    return 0;
  }
  pbVar17 = (byte *)*param_1;
  local_34 = FUN_8005c018();
  FUN_80082e48(auStack_368);
  FUN_80082ec8(auStack_348);
  FUN_80087158();
  puVar9 = (undefined4 *)FUN_8005c328();
  local_3a8 = *puVar9;
  local_3a4 = puVar9[1];
  local_3a0 = puVar9[2];
  local_39c = puVar9[3];
  local_398 = puVar9[4];
  local_394 = puVar9[5];
  local_390 = puVar9[6];
  local_38c = puVar9[7];
  FUN_80085558(&local_3a8);
  local_320 = 0;
  local_31e = 0;
  local_31c = 0;
  iVar6 = FUN_80086b38((*(byte *)(param_1 + 0x8b) & 3) << 10);
  iVar8 = (int)*(short *)(pbVar17 + 8);
  if (iVar8 == 0) {
    trap(0x1c00);
  }
  if ((iVar8 == -1) && (param_1[0x8a] << 0xc == -0x80000000)) {
    trap(0x1800);
  }
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xf;
  }
  local_310 = (int)(param_1[0x8a] << 0xc) / iVar8 + (iVar6 >> 4);
  local_30c = local_310;
  local_308 = local_310;
  uVar5 = FUN_8005bed4();
  FUN_8005c0b8(uVar5,auStack_318);
  FUN_80085558(&local_3a8);
  FUN_800878f8(auStack_318,auStack_374,&local_38);
  FUN_80087cb8(&local_320,auStack_388);
  FUN_800875f8(auStack_388,&local_310);
  FUN_80085558(auStack_388);
  iVar6 = param_1[0x89];
  iVar8 = (int)*(short *)(pbVar17 + 6);
  if (iVar8 == 0) {
    trap(0x1c00);
  }
  if ((iVar8 == -1) && ((uint)*(byte *)(param_1 + 0x87) * iVar6 == -0x80000000)) {
    trap(0x1800);
  }
  iVar11 = param_1[0x8a];
  iVar7 = ((int)((uint)*(byte *)(param_1 + 0x87) * iVar6) / iVar8) * iVar11;
  iVar10 = (int)*(short *)(pbVar17 + 8);
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar7 == -0x80000000)) {
    trap(0x1800);
  }
  iVar2 = (uint)*(byte *)((int)param_1 + 0x21d) * iVar6;
  if (iVar8 == 0) {
    trap(0x1c00);
  }
  if ((iVar8 == -1) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  iVar6 = (uint)*(byte *)((int)param_1 + 0x21e) * iVar6;
  if (iVar8 == 0) {
    trap(0x1c00);
  }
  if ((iVar8 == -1) && (iVar6 == -0x80000000)) {
    trap(0x1800);
  }
  iVar2 = (iVar2 / iVar8) * iVar11;
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  iVar11 = (iVar6 / iVar8) * iVar11;
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar11 == -0x80000000)) {
    trap(0x1800);
  }
  local_364 = (undefined1)(iVar7 / iVar10);
  local_363 = (undefined1)(iVar2 / iVar10);
  local_362 = (undefined1)(iVar11 / iVar10);
  iVar8 = param_1[0x89];
  iVar6 = (int)*(short *)(pbVar17 + 6);
  if (iVar6 == 0) {
    trap(0x1c00);
  }
  if ((iVar6 == -1) && ((uint)*pbVar17 * iVar8 == -0x80000000)) {
    trap(0x1800);
  }
  iVar11 = param_1[0x8a];
  iVar7 = ((int)((uint)*pbVar17 * iVar8) / iVar6) * iVar11;
  iVar10 = (int)*(short *)(pbVar17 + 8);
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar7 == -0x80000000)) {
    trap(0x1800);
  }
  if (iVar6 == 0) {
    trap(0x1c00);
  }
  if ((iVar6 == -1) && ((uint)pbVar17[1] * iVar8 == -0x80000000)) {
    trap(0x1800);
  }
  if (iVar6 == 0) {
    trap(0x1c00);
  }
  if ((iVar6 == -1) && ((uint)pbVar17[2] * iVar8 == -0x80000000)) {
    trap(0x1800);
  }
  iVar2 = ((int)((uint)pbVar17[1] * iVar8) / iVar6) * iVar11;
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  iVar11 = ((int)((uint)pbVar17[2] * iVar8) / iVar6) * iVar11;
  if (iVar10 == 0) {
    trap(0x1c00);
  }
  if ((iVar10 == -1) && (iVar11 == -0x80000000)) {
    trap(0x1800);
  }
  iVar16 = 0;
  iVar15 = 4;
  iVar12 = 2;
  iVar8 = 8;
  iVar6 = 4;
  local_35c = (undefined1)(iVar7 / iVar10);
  local_35b = (undefined1)(iVar2 / iVar10);
  local_35a = (undefined1)(iVar11 / iVar10);
  local_354 = local_35c;
  local_353 = local_35b;
  local_352 = local_35a;
  FUN_80087c48(param_1 + 1,local_2e0,local_1d0,auStack_148,&local_c0,0x43);
  do {
    local_35e = local_2e0[1];
    local_360 = local_2e0[0];
    local_358 = *(undefined2 *)((int)local_2e0 + iVar6);
    local_356 = *(undefined2 *)((int)local_2e0 + iVar6 + 2);
    local_350 = *(undefined2 *)((int)local_2e0 + iVar8);
    local_34e = *(undefined2 *)((int)local_2e0 + iVar8 + 2);
    iVar7 = FUN_80089bf8(local_1d0[0],*(undefined2 *)((int)local_1d0 + iVar12),
                         *(undefined2 *)((int)local_1d0 + iVar15));
    uVar3 = local_bc | local_c0 | local_be;
    local_38 = uVar3 & 0x20;
    if ((-1 < iVar7 / 2) && ((uVar3 & 0x20) == 0)) {
      FUN_8004d5b8(auStack_368,local_34,iVar7 / 2 & 0xffff,1);
    }
    iVar15 = iVar15 + 2;
    iVar12 = iVar12 + 2;
    iVar8 = iVar8 + 4;
    iVar16 = iVar16 + 1;
    iVar6 = iVar6 + 4;
  } while (iVar16 < 0x20);
  FUN_800871fc();
  *(char *)(param_1 + 0x8b) = *(char *)(param_1 + 0x8b) + '\x01';
  if (param_2 == -2) {
    param_1[0x89] = param_1[0x89] - (uint)local_30;
  }
  else {
    iVar6 = param_1[0x8a] + (uint)local_30;
    param_1[0x8a] = iVar6;
    if (iVar6 < 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = (int)*(short *)(pbVar17 + 8);
      if (iVar6 <= iVar8) goto LAB_8006d364;
    }
    param_1[0x8a] = iVar8;
  }
LAB_8006d364:
  return (uint)((int)param_1[0x89] < 1) << 1;
}

