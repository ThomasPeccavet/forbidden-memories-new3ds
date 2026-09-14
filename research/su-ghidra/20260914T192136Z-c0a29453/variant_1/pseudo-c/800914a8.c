/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800914a8(uint *param_1,uint *param_2,int param_3)

{
  bool bVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  ushort *puVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  undefined2 *puVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  
  if (param_1 != (uint *)0x0) {
    iVar18 = 0;
    iVar19 = 0;
    iVar20 = 0;
    puVar17 = (undefined2 *)((int)param_2 + DAT_8009b458 * 2);
    uVar4 = *param_1;
    iVar15 = (uint)(ushort)param_1[1] << 10;
    uVar16 = (uint)(-1 < (int)(*(ushort *)((int)param_1 + 6) - 3));
    puVar7 = param_1 + 3;
    uVar5 = CONCAT22((short)param_1[2],*(undefined2 *)((int)param_1 + 10));
    uVar6 = 0;
    *param_2 = uVar4;
    DAT_8009b480 = param_2 + (uVar4 & 0xffff) + 1;
    puVar8 = (undefined2 *)((int)param_2 + 2);
    goto LAB_8009156c;
  }
  puVar17 = DAT_8009b460 + DAT_8009b458;
  uVar4 = DAT_8009b464;
  uVar6 = DAT_8009b468;
  puVar7 = DAT_8009b45c;
  puVar2 = DAT_8009b460;
  iVar15 = DAT_8009b46c;
  uVar16 = DAT_8009b470;
  iVar18 = DAT_8009b474;
  iVar19 = DAT_8009b478;
  iVar20 = DAT_8009b47c;
LAB_80091688:
  do {
    while( true ) {
      puVar9 = puVar2;
      puVar11 = (uint *)((uVar4 >> 0x13) * 8 + param_3 + 0x800);
      uVar12 = *puVar11;
      if (uVar12 == 0) {
        uVar4 = uVar4 << 8;
        uVar5 = uVar6 + 8;
        uVar6 = uVar5 & 0xf;
        if ((uVar5 & 0x10) != 0) {
          uVar5 = *puVar7;
          puVar7 = (uint *)((int)puVar7 + 2);
          uVar4 = uVar4 | (uint)(ushort)uVar5 << uVar6;
        }
        uVar12 = *(uint *)((uVar4 >> 0x17) * 4 + param_3 + 0x10800);
        uVar14 = 0;
      }
      else {
        uVar14 = puVar11[1];
      }
      uVar4 = uVar4 << (uVar12 & 0x1f);
      uVar5 = uVar6 + (uVar12 & 0xff);
      uVar6 = uVar5 & 0xf;
      if ((uVar5 & 0x10) != 0) {
        uVar5 = *puVar7;
        puVar7 = (uint *)((int)puVar7 + 2);
        uVar4 = uVar4 | (uint)(ushort)uVar5 << uVar6;
      }
      puVar8 = puVar9;
      if (uVar12 >> 0x10 != 0x7c1f) break;
LAB_8009176c:
      *puVar8 = (short)(uVar4 >> 0x10);
      uVar5 = *puVar7;
      puVar7 = (uint *)((int)puVar7 + 2);
      uVar4 = uVar4 << 0x10 | (uint)(ushort)uVar5 << uVar6;
      puVar2 = puVar8 + 1;
    }
    *puVar9 = (short)(uVar12 >> 0x10);
    uVar5 = uVar4;
    if (uVar12 >> 0x10 != 0xfe00) {
      puVar8 = puVar9 + 1;
      puVar2 = puVar8;
      if (uVar14 == 0) goto LAB_80091688;
      if ((uVar14 & 0xffff) == 0x7c1f) goto LAB_8009176c;
      *puVar8 = (short)uVar14;
      if ((uVar14 & 0xffff) != 0xfe00) {
        uVar12 = uVar14 >> 0x10;
        puVar8 = puVar9 + 2;
        puVar2 = puVar8;
        if (uVar12 == 0) goto LAB_80091688;
        if (uVar12 == 0x7c1f) goto LAB_8009176c;
        *puVar8 = (short)(uVar14 >> 0x10);
        if (uVar12 != 0xfe00) {
          puVar2 = puVar9 + 3;
          goto LAB_80091688;
        }
      }
    }
LAB_8009156c:
    puVar11 = DAT_8009b480;
    if (uVar16 == 0) {
      if (uVar5 >> 0x16 == 0x1ff) goto LAB_800917a0;
      uVar4 = uVar5 << 10;
      uVar12 = uVar6 + 10;
      uVar6 = uVar12 & 0xf;
      if ((uVar12 & 0x10) != 0) {
        uVar12 = *puVar7;
        puVar7 = (uint *)((int)puVar7 + 2);
        uVar4 = uVar4 | (uint)(ushort)uVar12 << uVar6;
      }
      puVar8[1] = (ushort)iVar15 | (ushort)(uVar5 >> 0x16);
    }
    else {
      if (uVar5 >> 0x16 == 0x3ff) {
LAB_800917a0:
        while (puVar8 = puVar8 + 1, (int)puVar8 - (int)puVar11 < 0) {
          *puVar8 = 0xfe00;
        }
        return 0;
      }
      iVar3 = param_3 + 0x400;
      if (-1 < (int)(uVar16 - 3)) {
        iVar3 = param_3;
      }
      puVar10 = (ushort *)((uVar5 >> 0x18) * 4 + iVar3);
      uVar12 = (uint)*puVar10;
      uVar13 = (uint)puVar10[1];
      uVar14 = 0;
      uVar4 = uVar5 << (uVar12 & 0x1f);
      if (uVar13 != 0) {
        uVar14 = uVar4 >> (0x20 - uVar13 & 0x1f);
        bVar1 = -1 < (int)uVar4;
        uVar4 = uVar4 << (uVar13 & 0x1f);
        if (bVar1) {
          uVar14 = uVar14 - (0xffffffffU >> (0x20 - uVar13 & 0x1f));
        }
        uVar6 = uVar6 + uVar13;
      }
      uVar12 = uVar6 + uVar12;
      uVar6 = uVar12 & 0xf;
      if ((uVar12 & 0x10) != 0) {
        uVar5 = *puVar7;
        puVar7 = (uint *)((int)puVar7 + 2);
        uVar4 = uVar4 | (uint)(ushort)uVar5 << uVar6;
      }
      uVar5 = iVar20 + uVar14;
      if ((int)(uVar16 - 2) < 1) {
        uVar5 = iVar19 + uVar14;
        if (uVar16 == 2) {
          iVar19 = iVar19 + uVar14;
        }
        else {
          uVar5 = iVar18 + uVar14;
          iVar18 = iVar18 + uVar14;
        }
      }
      else {
        iVar20 = iVar20 + uVar14;
      }
      bVar1 = uVar16 == 6;
      puVar8[1] = (ushort)iVar15 | (ushort)((uVar5 & 0xff) << 2);
      uVar16 = uVar16 + 1;
      if (bVar1) {
        uVar16 = 1;
      }
    }
    puVar2 = puVar8 + 2;
    if (-1 < (int)puVar8 + (2 - (int)puVar17)) {
      DAT_8009b45c = puVar7;
      DAT_8009b460 = puVar8 + 2;
      DAT_8009b464 = uVar4;
      DAT_8009b468 = uVar6;
      DAT_8009b46c = iVar15;
      DAT_8009b470 = uVar16;
      DAT_8009b474 = iVar18;
      DAT_8009b478 = iVar19;
      DAT_8009b47c = iVar20;
      return 1;
    }
  } while( true );
}

