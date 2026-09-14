/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800304d0(void)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  ushort *puVar5;
  undefined1 *puVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int in_a3;
  int iVar14;
  undefined4 uVar15;
  int local_58 [4];
  undefined4 local_48;
  int local_40 [4];
  int local_30 [4];
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar15 = 0;
  local_58[0] = DAT_80010260;
  local_58[1] = DAT_80010264;
  local_58[2] = DAT_80010268;
  local_58[3] = DAT_8001026c;
  local_48 = DAT_80010270;
  local_40[0] = DAT_80010274;
  local_40[1] = DAT_80010278;
  local_40[2] = DAT_8001027c;
  local_40[3] = DAT_80010280;
  local_30[0] = DAT_80010284;
  local_30[1] = DAT_80010288;
  local_30[2] = DAT_8001028c;
  local_30[3] = DAT_80010290;
  local_20 = DAT_80010294;
  local_18 = DAT_8009c2dc;
  local_14 = DAT_8009c2e0;
  iVar8 = (int)(char)DAT_8009c66c;
  bVar2 = (&DAT_8009c650)[iVar8];
  if ((DAT_8009c672 & 0x80) == 0) {
    bVar4 = DAT_8009c672 | 0x80;
    bVar3 = DAT_8009c672 & 0x40;
    DAT_8009c672 = bVar4;
    if (bVar3 != 0) {
      puVar5 = &DAT_8009c660 + iVar8;
      uVar11 = (uint)*puVar5;
      piVar7 = local_58 + ((int)(char)bVar2 - 1U);
      *puVar5 = 0;
      uVar12 = (int)(char)bVar2 - 1U;
      do {
        iVar8 = *piVar7;
        if (iVar8 == 0) {
          trap(0x1c00);
        }
        if ((iVar8 == -1) && (uVar11 == 0x80000000)) {
          trap(0x1800);
        }
        piVar7 = piVar7 + -1;
        uVar13 = uVar12 - 1;
        *puVar5 = *puVar5 | (ushort)((int)uVar11 / iVar8 << ((uVar12 & 7) << 2));
        uVar11 = uVar11 - iVar8 * ((int)uVar11 / iVar8);
        uVar12 = uVar13;
      } while (-1 < (int)uVar13);
    }
  }
  else if (((DAT_8009c672 & 1) == 0) && (((DAT_8009c710 | DAT_8009c712) & 0x800) == 0)) {
    if (((DAT_8009c72c | DAT_8009c72e) & 0xc0) != 0) {
      uVar15 = 1;
      goto LAB_80030988;
    }
    if (((DAT_8009c72c | DAT_8009c72e) & 0x20) != 0) {
      uVar15 = 0xffffffff;
      goto LAB_80030988;
    }
    if (((DAT_8009c728 | DAT_8009c72a) & 0x5000) != 0) {
      iVar14 = (int)(char)DAT_8009c670;
      uVar12 = (uint)(ushort)(&DAT_8009c660)[iVar8];
      iVar9 = local_30[iVar14];
      if (((DAT_8009c728 | DAT_8009c72a) & 0x4000) != 0) {
        iVar9 = -iVar9;
      }
      if ((DAT_8009c672 & 0x40) == 0) {
        uVar10 = (&DAT_8009c660)[iVar8] + (short)iVar9 &
                 (short)*(undefined4 *)((int)local_30 + ((int)((uint)bVar2 << 0x18) >> 0x16)) - 1U;
      }
      else {
        uVar11 = (uint)*(ushort *)((int)&local_18 + iVar14 * 2);
        if (iVar14 < (char)bVar2) {
          piVar7 = local_40 + iVar14;
          do {
            uVar13 = uVar12 & uVar11;
            uVar12 = uVar12 & ~uVar11;
            in_a3 = uVar13 + iVar9;
            if (iVar9 < 0) {
              if (-1 < in_a3) break;
              uVar12 = uVar12 | *piVar7 - 1U & uVar11;
            }
            else if (in_a3 < *piVar7) break;
            in_a3 = 0;
            uVar11 = uVar11 << 4;
            iVar9 = iVar9 << 4;
            iVar14 = iVar14 + 1;
            piVar7 = piVar7 + 1;
          } while (iVar14 < (char)bVar2);
        }
        uVar10 = (ushort)uVar12 | (ushort)in_a3;
      }
      (&DAT_8009c660)[(char)DAT_8009c66c] = uVar10;
    }
    if (((DAT_8009c728 | DAT_8009c72a) & 0xa000) == 0) goto LAB_80030988;
    if (((DAT_8009c728 | DAT_8009c72a) & 0x2000) == 0) {
      DAT_8009c670 = DAT_8009c670 + 1;
      if ((int)((uint)bVar2 << 0x18) <= (int)((uint)DAT_8009c670 << 0x18)) {
        DAT_8009c670 = 0;
        DAT_8009c66c = DAT_8009c66c - 1;
        if ((int)((uint)DAT_8009c66c << 0x18) < 0) {
          DAT_8009c66c = 0;
          cVar1 = DAT_8009c650;
          goto LAB_8003092c;
        }
      }
    }
    else {
      DAT_8009c670 = DAT_8009c670 - 1;
      if ((int)((uint)DAT_8009c670 << 0x18) < 0) {
        DAT_8009c66c = DAT_8009c66c + 1;
        if ((int)(char)DAT_8009c66c < (int)DAT_8009c66d) {
          cVar1 = (&DAT_8009c650)[(char)DAT_8009c66c];
LAB_8003092c:
          DAT_8009c670 = cVar1 - 1;
        }
        else {
          DAT_8009c66c = DAT_8009c66d - 1;
          DAT_8009c670 = 0;
        }
      }
    }
  }
  iVar8 = 0x27;
  puVar6 = &DAT_800ec287;
  do {
    *puVar6 = 0x20;
    iVar8 = iVar8 + -1;
    puVar6 = puVar6 + -1;
  } while (-1 < iVar8);
  cVar1 = (&DAT_8009c654)[(char)DAT_8009c66c];
  iVar8 = (int)(char)DAT_8009c670;
  (&DAT_800ec260)[cVar1 - iVar8] = 0x2a;
  (&DAT_800ec261)[cVar1 - iVar8] = 0;
LAB_80030988:
  for (iVar8 = (int)DAT_8009c658; iVar8 != 0; iVar8 = iVar8 + -1) {
    FUN_8007f520(&DAT_8009c2e4);
  }
  FUN_8007f520(DAT_8009c674,DAT_8009c660,DAT_8009c662,DAT_8009c664);
  FUN_8007f520(&DAT_8009c2e8,&DAT_800ec260);
  return uVar15;
}

