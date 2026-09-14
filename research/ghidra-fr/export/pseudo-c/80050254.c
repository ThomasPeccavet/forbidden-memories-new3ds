/* Analysis pseudo-C, not buildable source. */

uint FUN_80050254(uint param_1,ushort *param_2,int *param_3,uint *param_4,int *param_5)

{
  bool bVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  
  uVar16 = (uint)*(ushort *)(*param_3 + 2);
  iVar15 = param_3[5] + *(int *)(*param_3 + 4) * 4;
  if (2 < param_1) {
    return 0;
  }
  uVar2 = *param_2;
  if (uVar2 == 0x15) {
    iVar13 = 6;
    iVar6 = 2;
    iVar11 = 0x1c;
LAB_80050388:
    iVar12 = 0x34;
  }
  else {
    if (uVar2 < 0x16) {
      if (uVar2 != 0xd) {
        if (uVar2 < 0xe) {
          if (uVar2 != 9) {
            return 0;
          }
          iVar13 = 6;
          iVar6 = 2;
          iVar11 = 0x14;
          iVar12 = 0x20;
          goto LAB_8005038c;
        }
        if (uVar2 != 0x11) {
          return 0;
        }
      }
      iVar13 = 6;
      iVar6 = 2;
      iVar11 = 0x18;
      iVar12 = 0x28;
      goto LAB_8005038c;
    }
    if (uVar2 != 0x20d) {
      if (uVar2 < 0x20e) {
        if (uVar2 != 0x209) {
          return 0;
        }
        iVar13 = 10;
        iVar6 = 6;
        iVar11 = 0x18;
        iVar12 = 0x20;
        goto LAB_8005038c;
      }
      if (uVar2 != 0x211) {
        if (uVar2 != 0x215) {
          return 0;
        }
        iVar13 = 10;
        iVar6 = 6;
        iVar11 = 0x20;
        goto LAB_80050388;
      }
    }
    iVar13 = 10;
    iVar6 = 6;
    iVar11 = 0x1c;
    iVar12 = 0x28;
  }
LAB_8005038c:
  iVar14 = uVar16 - 1;
  if (iVar14 != -1) {
    puVar9 = (ushort *)(iVar15 + 0x1c);
    puVar10 = (ushort *)(iVar15 + iVar6);
    do {
      puVar8 = (ushort *)(iVar15 + iVar13);
      uVar5 = *puVar8 >> 7 & 3;
      uVar2 = *puVar8 + (short)param_1 * 4 + -10;
      if ((int)param_1 < 2) {
        *puVar8 = uVar2;
        if (2 < uVar5) {
          *puVar8 = uVar2 & 0xff7f;
        }
        if (uVar5 < 2) {
          *puVar10 = ((*puVar10 >> 6 & 0xf) + 0xd0 + (short)param_1 * 0x10) * 0x40 | *puVar10 & 0x3f
          ;
        }
      }
      else if (uVar5 < 2) {
        uVar2 = *puVar10 >> 6;
        if (uVar2 < 0x100) {
          uVar4 = (*puVar10 & 0x3f) << 4;
          uVar2 = uVar2 & 0xf;
          sVar3 = uVar2 + 0xd0;
          if (0x1ff < uVar4) {
            sVar3 = uVar2 + 0xf0;
          }
          *puVar10 = sVar3 << 6 | (ushort)((int)((uVar4 & 0xff) + 0x280) >> 4) & 0x3f;
        }
      }
      if (param_4 == (uint *)0x0) goto LAB_800506b0;
      uVar2 = *param_2;
      if (uVar2 == 0x15) {
        uVar4 = *param_4;
        if ((int)*param_4 < (int)(uint)puVar9[-9]) {
          uVar4 = (uint)puVar9[-9];
        }
        *param_4 = uVar4;
        uVar7 = (uint)puVar9[-6];
        if ((int)uVar4 < (int)uVar7) {
          *param_4 = uVar7;
          uVar4 = uVar7;
        }
        if ((int)uVar4 < (int)(uint)puVar9[-4]) {
          uVar4 = (uint)puVar9[-4];
        }
        *param_4 = uVar4;
        uVar7 = (uint)puVar9[-2];
        bVar1 = (int)uVar4 < (int)uVar7;
LAB_8005069c:
        if (bVar1) {
          uVar4 = uVar7;
        }
        *param_4 = uVar4;
      }
      else {
        if (0x15 < uVar2) {
          if (uVar2 == 0x20d) {
            uVar4 = *param_4;
            if ((int)*param_4 < (int)(uint)puVar9[-6]) {
              uVar4 = (uint)puVar9[-6];
            }
            *param_4 = uVar4;
            uVar7 = (uint)puVar9[-4];
            if ((int)uVar4 < (int)uVar7) {
              *param_4 = uVar7;
              uVar4 = uVar7;
            }
            uVar7 = (uint)puVar9[-2];
            bVar1 = (int)uVar4 < (int)uVar7;
          }
          else if (uVar2 < 0x20e) {
            if (uVar2 != 0x209) goto LAB_800506b0;
            uVar4 = *param_4;
            uVar7 = (uint)puVar9[-6];
            bVar1 = (int)uVar4 < (int)uVar7;
          }
          else if (uVar2 == 0x211) {
            uVar4 = *param_4;
            uVar7 = (uint)puVar9[-5];
            bVar1 = (int)uVar4 < (int)uVar7;
          }
          else {
            if (uVar2 != 0x215) goto LAB_800506b0;
            uVar4 = *param_4;
            if ((int)*param_4 < (int)(uint)puVar9[-7]) {
              uVar4 = (uint)puVar9[-7];
            }
            *param_4 = uVar4;
            uVar7 = (uint)puVar9[-4];
            if ((int)uVar4 < (int)uVar7) {
              *param_4 = uVar7;
              uVar4 = uVar7;
            }
            if ((int)uVar4 < (int)(uint)puVar9[-2]) {
              uVar4 = (uint)puVar9[-2];
            }
            *param_4 = uVar4;
            uVar7 = (uint)*puVar9;
            bVar1 = (int)uVar4 < (int)uVar7;
          }
          goto LAB_8005069c;
        }
        if (uVar2 == 0xd) {
          uVar4 = *param_4;
          if ((int)*param_4 < (int)(uint)puVar9[-8]) {
            uVar4 = (uint)puVar9[-8];
          }
          *param_4 = uVar4;
          uVar7 = (uint)puVar9[-6];
          if ((int)uVar4 < (int)uVar7) {
            *param_4 = uVar7;
            uVar4 = uVar7;
          }
          uVar7 = (uint)puVar9[-4];
          bVar1 = (int)uVar4 < (int)uVar7;
          goto LAB_8005069c;
        }
        if (uVar2 < 0xe) {
          if (uVar2 == 9) {
            uVar4 = *param_4;
            uVar7 = (uint)puVar9[-8];
            bVar1 = (int)uVar4 < (int)uVar7;
            goto LAB_8005069c;
          }
        }
        else if (uVar2 == 0x11) {
          uVar4 = *param_4;
          uVar7 = (uint)puVar9[-7];
          bVar1 = (int)uVar4 < (int)uVar7;
          goto LAB_8005069c;
        }
      }
LAB_800506b0:
      puVar9 = (ushort *)((int)puVar9 + iVar11);
      puVar10 = (ushort *)((int)puVar10 + iVar11);
      iVar14 = iVar14 + -1;
      *param_5 = *param_5 + iVar12;
      iVar15 = iVar15 + iVar11;
    } while (iVar14 != -1);
  }
  return uVar16;
}

