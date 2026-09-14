/* Analysis pseudo-C, not buildable source. */

void FUN_8004dbb4(void)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  int iVar7;
  int *piVar8;
  short *psVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  undefined4 *puVar13;
  int *piVar14;
  short *psVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  int iVar19;
  int local_58 [2];
  short local_50;
  short local_4e;
  short local_4c;
  short local_48 [4];
  ushort local_40;
  short local_3e;
  short local_3c;
  short local_38;
  short local_36;
  short local_34;
  int local_30;
  
  local_58[0] = FUN_8005c304();
  iVar19 = 0;
  local_30 = 0;
  local_58[1] = local_58[0] + 0xc;
  if ((DAT_8009c310 != 0) && (DAT_8009c30c != (undefined4 *)0x0)) {
    if ((DAT_8009c311 != '\0') && ((DAT_8009c313 != '\x01' || (DAT_8009c314 != '\x01')))) {
      puVar13 = &DAT_800f3ec8;
      iVar12 = 0;
      if (DAT_8009c310 != 0) {
        do {
          FUN_8004e818(puVar13);
          iVar12 = iVar12 + 1;
          puVar13 = puVar13 + 10;
        } while (iVar12 < (int)(uint)DAT_8009c310);
      }
      DAT_8009c311 = '\0';
      DAT_8009c312 = 0xff;
    }
    puVar13 = DAT_8009c30c;
    if (*(short *)((int)DAT_8009c30c + 0x22) != 0x4000) {
      iVar12 = FUN_8005bf24();
      uVar6 = *(ushort *)((int)DAT_8009c30c + 0x22);
      if ((int)((uint)*(ushort *)(DAT_8009c30c + 9) + iVar12) < (int)(uint)uVar6) {
        sVar2 = FUN_8005bf24();
        uVar6 = *(short *)(DAT_8009c30c + 9) + sVar2;
      }
      *(ushort *)(puVar13 + 9) = uVar6;
    }
    iVar12 = 0;
    piVar14 = local_58;
    psVar15 = &DAT_800f3ea8;
    iVar18 = 0;
    do {
      psVar9 = (short *)((int)DAT_8009c30c + iVar18);
      sVar2 = psVar9[3];
      uVar6 = psVar9[3];
      if (sVar2 != 0) {
        if (sVar2 < 4) {
          if (sVar2 < 2) {
            if (sVar2 == 1) {
              FUN_8004ec04(DAT_8009c30c,iVar12,*(undefined2 *)(DAT_8009c30c + 9),0,local_48);
              iVar16 = 0;
              psVar9 = local_48;
              do {
                iVar4 = iVar16 * 4;
                iVar16 = iVar16 + 1;
                *(int *)(iVar4 + *piVar14) = (int)*psVar9;
                psVar9 = psVar9 + 1;
              } while (iVar16 < 3);
            }
          }
          else {
            iVar19 = iVar19 + 1;
            sVar2 = *psVar9;
            iVar16 = (int)psVar9[1];
            iVar4 = FUN_8005bee0((int)sVar2);
            if (iVar4 == 1) {
              FUN_8005c0b8((int)sVar2,&local_40);
              iVar4 = (uint)local_40 - (uint)*(ushort *)((int)DAT_8009c30c + iVar18 + 0x10);
              sVar2 = local_3e - *(short *)((int)DAT_8009c30c + iVar18 + 0x12);
              sVar3 = local_3c - *(short *)((int)DAT_8009c30c + iVar18 + 0x14);
              if (*(short *)((int)DAT_8009c30c + iVar18 + 6) == 2) {
                if (iVar16 == 0) {
                  iVar16 = 10;
                }
                iVar4 = iVar4 * 0x10000 >> 0x10;
                if (iVar4 < 1) {
                  iVar4 = iVar4 + iVar16;
                  if (0 < iVar4) {
                    iVar4 = 0;
                  }
                }
                else {
                  iVar4 = iVar4 - iVar16;
                  if (iVar4 < 0) {
                    iVar4 = 0;
                  }
                }
                iVar5 = (int)sVar2;
                local_38 = (short)iVar4;
                if (iVar5 < 1) {
                  iVar5 = iVar5 + iVar16;
                  if (0 < iVar5) goto LAB_8004e0c8;
                }
                else {
                  iVar5 = iVar5 - iVar16;
                  if (iVar5 < 0) {
LAB_8004e0c8:
                    iVar5 = 0;
                  }
                }
                iVar4 = (int)sVar3;
                local_36 = (short)iVar5;
                if (iVar4 < 1) {
                  iVar4 = iVar4 + iVar16;
                  if (0 < iVar4) {
                    iVar4 = 0;
                  }
                }
                else {
                  iVar4 = iVar4 - iVar16;
                  if (iVar4 < 0) {
                    iVar4 = 0;
                  }
                }
                local_34 = (short)iVar4;
                if (local_38 < 1) {
                  if (local_38 < -0x3c) {
                    local_38 = -0x3c;
                  }
                }
                else if (0x3c < local_38) {
                  local_38 = 0x3c;
                }
                if (local_36 < 1) {
                  if (local_36 < -0x3c) {
                    local_36 = -0x3c;
                  }
                }
                else if (0x3c < local_36) {
                  local_36 = 0x3c;
                }
                if (local_34 < 1) {
                  if (local_34 < -0x3c) {
                    local_34 = -0x3c;
                  }
                }
                else if (0x3c < local_34) {
                  local_34 = 0x3c;
                }
                *(int *)*piVar14 = *(int *)*piVar14 + (int)local_38;
                *(int *)(*piVar14 + 4) = *(int *)(*piVar14 + 4) + (int)local_36;
                puVar13 = DAT_8009c30c;
                *(int *)(*piVar14 + 8) = *(int *)(*piVar14 + 8) + (int)local_34;
                *(short *)((int)puVar13 + iVar18 + 0x10) =
                     *(short *)((int)puVar13 + iVar18 + 0x10) + local_38;
                *(short *)((int)puVar13 + iVar18 + 0x12) =
                     *(short *)((int)puVar13 + iVar18 + 0x12) + local_36;
                *(short *)((int)puVar13 + iVar18 + 0x14) =
                     *(short *)((int)puVar13 + iVar18 + 0x14) + local_34;
              }
              else {
                iVar4 = iVar4 * 0x10000;
                if (iVar16 == 0) {
                  iVar16 = 2000;
                }
                iVar5 = iVar4 >> 0x10;
                if (iVar5 < 1) {
                  iVar7 = -iVar16;
                  bVar1 = iVar7 < iVar5;
                }
                else {
                  bVar1 = iVar5 < iVar16;
                  iVar7 = iVar16;
                }
                local_38 = (short)iVar7;
                if (bVar1) {
                  local_38 = (short)((uint)iVar4 >> 0x10);
                }
                iVar4 = (int)sVar2;
                if (iVar4 < 1) {
                  iVar5 = -iVar16;
                  bVar1 = iVar5 < iVar4;
                }
                else {
                  bVar1 = iVar4 < iVar16;
                  iVar5 = iVar16;
                }
                local_36 = (short)iVar5;
                if (bVar1) {
                  local_36 = sVar2;
                }
                iVar4 = (int)sVar3;
                if (iVar4 < 1) {
                  iVar16 = -iVar16;
                  bVar1 = iVar16 < iVar4;
                }
                else {
                  bVar1 = iVar4 < iVar16;
                }
                local_34 = (short)iVar16;
                if (bVar1) {
                  local_34 = sVar3;
                }
                *(int *)*piVar14 = (int)*psVar15 + (int)local_38;
                *(int *)(*piVar14 + 4) = (int)psVar15[1] + (int)local_36;
                *(int *)(*piVar14 + 8) = (int)psVar15[2] + (int)local_34;
              }
            }
          }
        }
        else if (sVar2 == 5) {
          iVar16 = (int)*psVar9;
          iVar19 = iVar19 + 1;
          if (*(ushort *)(DAT_8009c30c + 9) < *(ushort *)((int)DAT_8009c30c + 0x22)) {
            iVar4 = FUN_8008f708();
            iVar5 = FUN_8008f708();
            if (iVar16 == 0) {
              trap(0x1c00);
            }
            if ((iVar16 == -1) && (iVar4 >> 8 == -0x80000000)) {
              trap(0x1800);
            }
            if (iVar16 == 0) {
              trap(0x1c00);
            }
            if ((iVar16 == -1) && (iVar5 >> 8 == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)*piVar14 = ((int)*psVar15 + (iVar4 >> 8) % iVar16) - ((iVar5 >> 8) % iVar16) / 2
            ;
            iVar4 = FUN_8008f708();
            iVar5 = FUN_8008f708();
            if (iVar16 == 0) {
              trap(0x1c00);
            }
            if ((iVar16 == -1) && (iVar4 >> 8 == -0x80000000)) {
              trap(0x1800);
            }
            if (iVar16 == 0) {
              trap(0x1c00);
            }
            if ((iVar16 == -1) && (iVar5 >> 8 == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)(*piVar14 + 8) =
                 ((int)psVar15[2] + (iVar4 >> 8) % iVar16) - ((iVar5 >> 8) % iVar16) / 2;
          }
          else {
            *(int *)*piVar14 = (int)*psVar15;
            *(int *)(*piVar14 + 8) = (int)psVar15[2];
          }
        }
        else if (((4 < sVar2) && (sVar2 < 0x82)) && (0x7f < sVar2)) {
          uVar10 = (uint)*(ushort *)(DAT_8009c30c + 9);
          uVar17 = (uint)*(ushort *)((int)DAT_8009c30c + 0x22);
          iVar16 = FUN_8005bee0((int)(short)(uVar6 & 0xff7f));
          if (iVar16 == 1) {
            FUN_8005c0b8((int)(short)(uVar6 & 0xff7f),&local_50);
            psVar9 = (short *)((int)DAT_8009c30c + iVar18);
            local_50 = local_50 + *psVar9;
            local_4e = local_4e + psVar9[1];
            local_4c = local_4c + psVar9[2];
            iVar16 = uVar17 - uVar10;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (*psVar15 * iVar16 == -0x80000000)) {
              trap(0x1800);
            }
            iVar4 = (int)local_50 * uVar10;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (iVar4 == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)*piVar14 = (*psVar15 * iVar16) / (int)uVar17 + iVar4 / (int)uVar17;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (psVar15[1] * iVar16 == -0x80000000)) {
              trap(0x1800);
            }
            iVar4 = (int)local_4e * uVar10;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (iVar4 == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)(*piVar14 + 4) = (psVar15[1] * iVar16) / (int)uVar17 + iVar4 / (int)uVar17;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (psVar15[2] * iVar16 == -0x80000000)) {
              trap(0x1800);
            }
            iVar4 = (int)local_4c * uVar10;
            if (uVar17 == 0) {
              trap(0x1c00);
            }
            if ((uVar17 == 0xffffffff) && (iVar4 == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)(*piVar14 + 8) = (psVar15[2] * iVar16) / (int)uVar17 + iVar4 / (int)uVar17;
          }
        }
        local_30 = local_30 + 1;
      }
      piVar14 = piVar14 + 1;
      psVar15 = psVar15 + 4;
      iVar12 = iVar12 + 1;
      iVar18 = iVar18 + 8;
    } while (iVar12 < 2);
    uVar17 = 0;
    piVar14 = local_58;
    do {
      psVar15 = (short *)(DAT_8009c30c + uVar17 * 2);
      if (psVar15[3] == 4) {
        uVar11 = (uint)*(ushort *)(DAT_8009c30c + 9);
        uVar10 = (uint)*(ushort *)((int)DAT_8009c30c + 0x22);
        if (uVar10 == 0) {
          trap(0x1c00);
        }
        if ((uVar10 == 0xffffffff) && ((int)psVar15[1] * uVar11 == -0x80000000)) {
          trap(0x1800);
        }
        if (uVar10 == 0) {
          trap(0x1c00);
        }
        if ((uVar10 == 0xffffffff) && ((int)psVar15[2] * uVar11 == -0x80000000)) {
          trap(0x1800);
        }
        iVar12 = (int)DAT_800f3eb8;
        iVar16 = (int)((int)psVar15[1] * uVar11) / (int)uVar10 + (int)DAT_800f3eba;
        iVar18 = (int)((int)psVar15[2] * uVar11) / (int)uVar10 + (int)DAT_800f3ebc;
        if (*psVar15 != 0) {
          iVar4 = iVar12 * (uVar10 - uVar11) + (int)*psVar15 * uVar11;
          iVar12 = iVar4 / (int)uVar10;
          if (uVar10 == 0) {
            trap(0x1c00);
          }
          if ((uVar10 == 0xffffffff) && (iVar4 == -0x80000000)) {
            trap(0x1800);
          }
        }
        iVar4 = FUN_800866f8(iVar18);
        iVar18 = FUN_80086628(iVar18);
        iVar4 = iVar12 * iVar4;
        iVar12 = iVar12 * iVar18;
        if (iVar4 < 0) {
          iVar4 = iVar4 + 0xfff;
        }
        if (iVar12 < 0) {
          iVar12 = iVar12 + 0xfff;
        }
        iVar5 = FUN_800866f8(iVar16);
        iVar18 = FUN_80086628(iVar16);
        iVar18 = (iVar4 >> 0xc) * iVar18;
        iVar5 = (iVar4 >> 0xc) * iVar5;
        if (iVar18 < 0) {
          iVar18 = iVar18 + 0xfff;
        }
        if (iVar5 < 0) {
          iVar5 = iVar5 + 0xfff;
        }
        piVar8 = local_58 + (uVar17 ^ 1);
        *(int *)*piVar14 = *(int *)*piVar8 + (iVar5 >> 0xc);
        *(int *)(*piVar14 + 4) = *(int *)(*piVar8 + 4) + (iVar12 >> 0xc);
        *(int *)(*piVar14 + 8) = *(int *)(*piVar8 + 8) + (iVar18 >> 0xc);
      }
      uVar17 = uVar17 + 1;
      piVar14 = piVar14 + 1;
    } while ((int)uVar17 < 2);
    if ((local_30 == 0) && (*(short *)((int)DAT_8009c30c + 0x22) == 0x4000)) {
      DAT_8009c30c = (undefined4 *)0x0;
      DAT_8009c310 = 0;
    }
    else {
      if (*(ushort *)((int)DAT_8009c30c + 0x22) <= *(ushort *)(DAT_8009c30c + 9)) {
        FUN_8004f080(0);
        puVar13 = DAT_8009c30c + 0x1ffc3058;
        DAT_8009c30c = DAT_8009c30c + 10;
        if ((int)(uint)DAT_8009c310 <= (int)puVar13 * -0x33333333 >> 3) {
          if (DAT_8009c310 < 2) {
            DAT_8009c30c = (undefined4 *)0x0;
            DAT_8009c310 = 0;
          }
          else {
            DAT_8009c30c = &DAT_800f3ec8;
            DAT_800f3eee = 0;
          }
        }
        if ((DAT_8009c30c != (undefined4 *)0x0) &&
           (FUN_8004e818(), *(short *)(DAT_8009c30c + 8) == 0)) {
          FUN_8004dbb4();
        }
      }
      if (iVar19 == 2) {
        FUN_8005b5cc(1,0x1000,0,0,0);
      }
      else {
        FUN_8005b0bc(0);
      }
    }
  }
  return;
}

