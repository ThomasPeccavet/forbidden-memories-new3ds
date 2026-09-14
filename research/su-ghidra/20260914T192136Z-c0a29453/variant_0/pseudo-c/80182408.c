/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80182408(void)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  short sVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined **ppuVar14;
  short *psVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined2 *puVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  undefined4 uVar22;
  int iVar23;
  undefined *local_38 [2];
  uint local_30;
  
  iVar20 = 0;
  iVar19 = 0;
  iVar23 = 1;
  iVar21 = 1;
  uVar5 = *(byte *)(DAT_8018480c + 0x69) - 4;
  local_30 = uVar5;
  if (DAT_80185efd != '\0') {
    iVar19 = FUN_8003fa30();
    if (iVar19 == 0) {
      return 0;
    }
    if (iVar19 == 1) {
      puVar6 = &DAT_801d1200;
      puVar12 = &DAT_801d2200;
      puVar13 = &DAT_801d2880;
      puVar10 = &DAT_801d1880;
      do {
        uVar16 = puVar10[1];
        uVar17 = puVar10[2];
        uVar22 = puVar10[3];
        *puVar6 = *puVar10;
        puVar6[1] = uVar16;
        puVar6[2] = uVar17;
        puVar6[3] = uVar22;
        puVar10 = puVar10 + 4;
        puVar6 = puVar6 + 4;
      } while (puVar10 != (undefined4 *)0x801d1c80);
      do {
        uVar16 = puVar13[1];
        uVar17 = puVar13[2];
        uVar22 = puVar13[3];
        *puVar12 = *puVar13;
        puVar12[1] = uVar16;
        puVar12[2] = uVar17;
        puVar12[3] = uVar22;
        puVar13 = puVar13 + 4;
        puVar12 = puVar12 + 4;
      } while (puVar13 != (undefined4 *)0x801d2c80);
      iVar19 = 0;
      puVar18 = &DAT_80185ec8;
      do {
        *puVar18 = 0;
        FUN_801835b8(iVar19,1);
        FUN_80184704(iVar19);
        puVar7 = &DAT_80185ef4 + iVar19;
        iVar19 = iVar19 + 1;
        *puVar7 = 0;
        puVar18 = puVar18 + 0xb;
      } while (iVar19 < 2);
      FUN_8003cd78();
      DAT_80185efb = 0;
      DAT_80185efc = 0;
      DAT_80185efd = 0;
      return 0;
    }
    FUN_8006b260(DAT_80185efa);
    FUN_8003cd78();
    DAT_80185efc = 0;
    DAT_80185efd = 0;
    return 0;
  }
  if (DAT_80185efc != '\0') {
    puVar6 = &DAT_801d1200;
    puVar13 = &DAT_801d2200;
    puVar10 = &DAT_801d2880;
    puVar12 = &DAT_801d1880;
    local_38[0] = &DAT_801d18d0;
    local_38[1] = &DAT_801d28d0;
    do {
      uVar16 = puVar6[1];
      uVar17 = puVar6[2];
      uVar22 = puVar6[3];
      *puVar12 = *puVar6;
      puVar12[1] = uVar16;
      puVar12[2] = uVar17;
      puVar12[3] = uVar22;
      puVar6 = puVar6 + 4;
      puVar12 = puVar12 + 4;
    } while (puVar6 != (undefined4 *)0x801d1600);
    do {
      uVar16 = puVar13[1];
      uVar17 = puVar13[2];
      uVar22 = puVar13[3];
      *puVar10 = *puVar13;
      puVar10[1] = uVar16;
      puVar10[2] = uVar17;
      puVar10[3] = uVar22;
      puVar13 = puVar13 + 4;
      puVar10 = puVar10 + 4;
    } while (puVar13 != (undefined4 *)0x801d2600);
    uVar5 = 0;
    iVar19 = 0;
    psVar15 = (short *)&DAT_80185ec8;
    ppuVar14 = local_38;
    do {
      if (*psVar15 != 0) {
        iVar20 = 1;
        do {
          iVar21 = *(ushort *)((int)&DAT_80185ec8 + iVar20 * 2 + iVar19) - 1;
          cVar1 = (*ppuVar14)[iVar21];
          if (cVar1 != '\0') {
            (*ppuVar14)[iVar21] = cVar1 + -1;
          }
          pbVar11 = local_38[uVar5 ^ 1] + iVar21;
          bVar2 = *pbVar11;
          if (bVar2 < 0xfa) {
            *pbVar11 = bVar2 + 1;
          }
          bVar3 = iVar20 < (int)(uint)*(ushort *)((int)&DAT_80185ec8 + iVar19);
          iVar20 = iVar20 + 1;
        } while (bVar3);
      }
      iVar19 = iVar19 + 0x16;
      ppuVar14 = ppuVar14 + 1;
      uVar5 = uVar5 + 1;
      psVar15 = psVar15 + 0xb;
    } while ((int)uVar5 < 2);
    FUN_80040138();
    DAT_80185efd = 1;
    return 0;
  }
  if (DAT_80185efb != '\0') {
    if (((DAT_8009c728 & 0x5000) != 0) || ((DAT_8009c72a & 0x5000) != 0)) {
      FUN_80048ae8(6,0xff,0);
      if (((DAT_8009c728 & 0x1000) == 0) && ((DAT_8009c72a & 0x1000) == 0)) {
        iVar19 = DAT_80185efa + 4;
      }
      else {
        iVar19 = DAT_80185efa + 2;
      }
      DAT_80185efa = (char)iVar19 + (char)((ulonglong)((longlong)iVar19 * 0x55555556) >> 0x20) * -3;
      FUN_8006b260(DAT_80185efa);
      return 0;
    }
    if (((DAT_8009c72c & 0x20) != 0) || ((DAT_8009c72e & 0x20) != 0)) {
      uVar5 = (DAT_8009c72c >> 5 ^ 1) & 1;
      FUN_80048ae8(8,0xff,0);
      FUN_800360d8(&DAT_800f097c);
      (&DAT_80185ef4)[uVar5] = 0;
      FUN_8006b170(uVar5 ^ 1);
      DAT_80185efb = 0;
      return 0;
    }
    if (((DAT_8009c72c & 0xc0) == 0) && ((DAT_8009c72e & 0xc0) == 0)) {
      return 0;
    }
    FUN_80048ae8(0x30,0xff,0);
    if (DAT_80185efa == 1) {
      FUN_800360d8(&DAT_800f097c);
      iVar19 = 1;
      puVar7 = &DAT_80185ef5;
      do {
        *puVar7 = 0;
        iVar19 = iVar19 + -1;
        puVar7 = puVar7 + -1;
      } while (-1 < iVar19);
      DAT_80185efb = 0;
      return 0;
    }
    if (1 < DAT_80185efa) {
      if (DAT_80185efa == 2) {
        return 1;
      }
      return 0;
    }
    if (DAT_80185efa == 0) {
      FUN_800360d8(&DAT_800f097c);
      DAT_80185efc = 1;
      return 0;
    }
    return 0;
  }
  if ((uint)DAT_80185eb8 == (uint)DAT_80185eba) {
    iVar8 = ((uint)DAT_80185eb8 + (uint)DAT_80185ef6) * 4;
    psVar15 = (short *)(&DAT_80184828 + iVar8);
    if (DAT_80185ef4 == '\0') {
      if ((DAT_8009c72c & 0x80) != 0) {
        if ((DAT_80185ef5 != '\0') && (uVar16 = 9, (uint)DAT_80185ec8 + (uint)DAT_80185ede == 0))
        goto LAB_80182ce0;
        FUN_80048ae8(0x30,0xff,0);
        FUN_8006b170(0);
        DAT_80185ef4 = '\x01';
        goto LAB_80182e88;
      }
      if ((DAT_8009c72c & 0x10) != 0) {
        if (*psVar15 != 0) {
          DAT_8009c5dd = 0x14;
          DAT_8009c5dc = 2;
          DAT_8009c5d8 = *psVar15;
        }
        goto LAB_80182e88;
      }
      if ((DAT_8009c728 & 0x900) != 0) {
        FUN_80048ae8(0x2f,0xff,0);
        if ((DAT_8009c728 & 0x100) == 0) {
          iVar20 = DAT_80185ef8 + 7;
        }
        else {
          iVar20 = DAT_80185ef8 + 5;
        }
        DAT_80185ef8 = (char)iVar20 +
                       (char)((ulonglong)((longlong)iVar20 * 0x2aaaaaab) >> 0x20) * -6;
        FUN_801835b8(0,0);
LAB_80182af0:
        iVar20 = 1;
        goto LAB_80182e88;
      }
      if ((DAT_8009c72c & 0xa000) != 0) {
        if ((DAT_8009c72c & 0x8000) == 0) {
          uVar5 = uVar5 | 1;
        }
        else {
          uVar5 = uVar5 & 0xfffffffe;
        }
        goto LAB_80182af0;
      }
      if ((DAT_8009c72c & 0x20) != 0) {
        if (DAT_80185ec8 != 0) {
          FUN_80184324(0,(&DAT_80185ec8)[DAT_80185ec8],1);
          FUN_80048ae8(8,0xff,0);
          iVar20 = 1;
          DAT_80185ec8 = DAT_80185ec8 - 1;
          goto LAB_80182e88;
        }
        uVar16 = 9;
        if ((DAT_80185ede == 0) && (DAT_80185ef5 == '\0')) goto LAB_8018315c;
LAB_80182ce0:
        FUN_80048ae8(uVar16,0xff,0);
        goto LAB_80182e88;
      }
      if ((DAT_8009c72c & 0x40) != 0) {
        if (DAT_80185ec8 < 10) {
          uVar16 = 9;
          if (*psVar15 == 0) goto LAB_80182ce0;
          if (*(short *)(&DAT_8018482a + iVar8) != 0) {
            FUN_80048ae8(7,0xff,0);
            DAT_80185ec8 = DAT_80185ec8 + 1;
            (&DAT_80185ec8)[DAT_80185ec8] = *psVar15;
            iVar20 = 1;
            *(short *)(&DAT_8018482a + iVar8) = *(short *)(&DAT_8018482a + iVar8) + -1;
            goto LAB_80182e88;
          }
        }
        uVar16 = 9;
        goto LAB_80182ce0;
      }
      if ((DAT_8009c710 & 0xc) == 0) {
        if ((DAT_8009c728 & 3) == 0) {
          if ((DAT_8009c728 & 0x5000) != 0) {
            if ((DAT_8009c728 & 0x1000) == 0) {
              if (DAT_80185ef6 < 7) {
                FUN_80048ae8(6,0xff,0);
                iVar23 = 2;
                DAT_80185ef6 = DAT_80185ef6 + 1;
              }
              else if (DAT_80185eba < 0x2ca) {
                FUN_80048ae8(6,0xff,0);
                DAT_80185eb8 = DAT_80185eba + 1;
                goto LAB_80182e7c;
              }
            }
            else if (DAT_80185ef6 == 0) {
              if (DAT_80185eba != 0) {
                FUN_80048ae8(6,0xff,0);
                DAT_80185eb8 = DAT_80185eba - 1;
LAB_80182e7c:
                iVar20 = 1;
                DAT_80185eba = DAT_80185eb8;
              }
            }
            else {
              FUN_80048ae8(6,0xff,0);
              iVar23 = 2;
              DAT_80185ef6 = DAT_80185ef6 - 1;
            }
          }
        }
        else {
          if ((DAT_8009c728 & 1) == 0) {
            uVar9 = (uint)DAT_80185eba;
            DAT_80185eba = 0x2ca;
            if (uVar9 + 0x32 < 0x2ca) {
              DAT_80185eba = (ushort)(uVar9 + 0x32);
            }
          }
          else {
            iVar20 = DAT_80185eba - 0x32;
            if (iVar20 < 0) {
              iVar20 = 0;
            }
            DAT_80185eba = (ushort)iVar20;
          }
          if (DAT_80185eb8 != DAT_80185eba) {
            FUN_80048ae8(6,0xff,0);
          }
          iVar20 = 1;
          DAT_80185eb8 = DAT_80185eba;
        }
        goto LAB_80182e88;
      }
      if ((DAT_8009c710 & 4) == 0) {
        uVar9 = (uint)DAT_80185eba;
        DAT_80185eba = 0x2ca;
        if (uVar9 + 8 < 0x2ca) {
          DAT_80185eba = (ushort)(uVar9 + 8);
        }
      }
      else {
        iVar8 = DAT_80185eba - 8;
        if (iVar8 < 0) {
          iVar8 = 0;
        }
        DAT_80185eba = (ushort)iVar8;
      }
      uVar16 = 6;
      if (DAT_80185eb8 != DAT_80185eba) goto LAB_80182ce0;
    }
    else {
      if ((DAT_8009c72c & 0x20) != 0) {
        FUN_80048ae8(8,0xff,0);
        FUN_800360d8(&DAT_800f097c);
        DAT_80185ef4 = '\0';
      }
LAB_80182e88:
      if (DAT_80185eb8 != DAT_80185eba) goto LAB_80182ea0;
    }
  }
  else {
LAB_80182ea0:
    sVar4 = 1;
    if (DAT_80185eba <= DAT_80185eb8) {
      sVar4 = -1;
    }
    DAT_80185eb8 = DAT_80185eb8 + sVar4;
    iVar20 = iVar20 + 1;
  }
  if ((uint)DAT_80185ebc == (uint)DAT_80185ebe) {
    iVar8 = ((uint)DAT_80185ebc + (uint)DAT_80185ef7) * 4;
    psVar15 = (short *)(&DAT_80185370 + iVar8);
    if (DAT_80185ef5 == '\0') {
      if ((DAT_8009c72e & 0x80) == 0) {
        if ((DAT_8009c72e & 0x10) == 0) {
          if ((DAT_8009c72a & 0x900) == 0) {
            if ((DAT_8009c72e & 0xa000) == 0) {
              if ((DAT_8009c72e & 0x20) == 0) {
                if ((DAT_8009c72e & 0x40) == 0) {
                  if ((DAT_8009c712 & 0xc) == 0) {
                    if ((DAT_8009c72a & 3) == 0) {
                      if ((DAT_8009c72a & 0x5000) != 0) {
                        if ((DAT_8009c72a & 0x1000) == 0) {
                          if (DAT_80185ef7 < 7) {
                            FUN_80048ae8(6,0xff,0);
                            iVar21 = 2;
                            DAT_80185ef7 = DAT_80185ef7 + 1;
                          }
                          else if (DAT_80185ebe < 0x2ca) {
                            FUN_80048ae8(6,0xff,0);
                            DAT_80185ebe = DAT_80185ebe + 1;
                            goto LAB_80183438;
                          }
                        }
                        else if (DAT_80185ef7 == 0) {
                          if (DAT_80185ebe != 0) {
                            FUN_80048ae8(6,0xff,0);
                            DAT_80185ebe = DAT_80185ebe - 1;
                            goto LAB_80183438;
                          }
                        }
                        else {
                          FUN_80048ae8(6,0xff,0);
                          iVar21 = 2;
                          DAT_80185ef7 = DAT_80185ef7 - 1;
                        }
                      }
                    }
                    else {
                      if ((DAT_8009c72a & 1) == 0) {
                        uVar9 = 0x2ca;
                        if (DAT_80185ebe + 0x32 < 0x2ca) {
                          uVar9 = DAT_80185ebe + 0x32;
                        }
                        DAT_80185ebe = (ushort)uVar9;
                      }
                      else {
                        iVar19 = DAT_80185ebe - 0x32;
                        if (iVar19 < 0) {
                          iVar19 = 0;
                        }
                        DAT_80185ebe = (ushort)iVar19;
                      }
                      if (DAT_80185ebc != DAT_80185ebe) {
                        FUN_80048ae8(6,0xff,0);
                      }
LAB_80183438:
                      iVar19 = 1;
                      DAT_80185ebc = DAT_80185ebe;
                    }
                    goto LAB_80183440;
                  }
                  if ((DAT_8009c712 & 4) == 0) {
                    uVar9 = 0x2ca;
                    if (DAT_80185ebe + 8 < 0x2ca) {
                      uVar9 = DAT_80185ebe + 8;
                    }
                    DAT_80185ebe = (ushort)uVar9;
                  }
                  else {
                    iVar8 = DAT_80185ebe - 8;
                    if (iVar8 < 0) {
                      iVar8 = 0;
                    }
                    DAT_80185ebe = (ushort)iVar8;
                  }
                  uVar16 = 6;
                  if (DAT_80185ebc == DAT_80185ebe) goto LAB_80183480;
                }
                else {
                  uVar16 = 9;
                  if ((DAT_80185ede < 10) && (*psVar15 != 0)) {
                    if (*(short *)(&DAT_80185372 + iVar8) != 0) {
                      FUN_80048ae8(7,0xff,0);
                      DAT_80185ede = DAT_80185ede + 1;
                      (&DAT_80185ede)[DAT_80185ede] = *psVar15;
                      iVar19 = 1;
                      *(short *)(&DAT_80185372 + iVar8) = *(short *)(&DAT_80185372 + iVar8) + -1;
                      goto LAB_80183440;
                    }
                    uVar16 = 9;
                  }
                }
              }
              else {
                if (DAT_80185ede != 0) {
                  FUN_80184324(1,(&DAT_80185ede)[DAT_80185ede],1);
                  FUN_80048ae8(8,0xff,0);
                  iVar19 = 1;
                  DAT_80185ede = DAT_80185ede - 1;
                  goto LAB_80183440;
                }
                uVar16 = 9;
                if ((DAT_80185ec8 == 0) && (DAT_80185ef4 == '\0')) {
LAB_8018315c:
                  FUN_80048ae8(8,0xff,0);
                  return 1;
                }
              }
LAB_8018329c:
              FUN_80048ae8(uVar16,0xff,0);
              goto LAB_80183440;
            }
            if ((DAT_8009c72e & 0x8000) == 0) {
              uVar5 = uVar5 | 2;
            }
            else {
              uVar5 = uVar5 & 0xfffffffd;
            }
          }
          else {
            FUN_80048ae8(0x2f,0xff,0);
            if ((DAT_8009c72a & 0x100) == 0) {
              iVar19 = DAT_80185ef9 + 7;
            }
            else {
              iVar19 = DAT_80185ef9 + 5;
            }
            DAT_80185ef9 = (char)iVar19 +
                           (char)((ulonglong)((longlong)iVar19 * 0x2aaaaaab) >> 0x20) * -6;
            FUN_801835b8(1,0);
          }
          iVar19 = 1;
        }
        else if (*psVar15 != 0) {
          DAT_8009c5dd = 0x14;
          DAT_8009c5dc = 2;
          DAT_8009c5d8 = *psVar15;
        }
      }
      else {
        if ((DAT_80185ef4 != '\0') && (uVar16 = 9, (uint)DAT_80185ec8 + (uint)DAT_80185ede == 0))
        goto LAB_8018329c;
        FUN_80048ae8(0x30,0xff,0);
        FUN_8006b170(1);
        DAT_80185ef5 = '\x01';
      }
    }
    else if ((DAT_8009c72e & 0x20) != 0) {
      FUN_80048ae8(8,0xff,0);
      FUN_800360d8(&DAT_800f097c);
      DAT_80185ef5 = '\0';
    }
LAB_80183440:
    if (DAT_80185ebc == DAT_80185ebe) goto LAB_80183480;
  }
  sVar4 = 1;
  if (DAT_80185ebe <= DAT_80185ebc) {
    sVar4 = -1;
  }
  DAT_80185ebc = DAT_80185ebc + sVar4;
  iVar19 = iVar19 + 1;
LAB_80183480:
  if (iVar23 != 0) {
    *(ushort *)(DAT_80184818 + 0x32) = (ushort)DAT_80185ef6 * 0x16 + 0x24;
  }
  if (iVar21 != 0) {
    *(ushort *)(DAT_80184820 + 0x32) = (ushort)DAT_80185ef7 * 0x16 + 0x24;
  }
  if (uVar5 != local_30) {
    FUN_80048ae8(0x1e,0xff,0);
    FUN_80040734(DAT_8018480c,uVar5 + 4);
  }
  if (iVar20 != 0) {
    FUN_80184704(0);
  }
  if (iVar19 != 0) {
    FUN_80184704(1);
  }
  if ((DAT_80185ef4 != '\0') && (DAT_80185ef5 != '\0')) {
    DAT_80185efa = 0;
    FUN_800360d8(&DAT_800f097c);
    FUN_800360d8(&DAT_800f097c);
    FUN_8006b260(DAT_80185efa);
    DAT_80185efb = '\x01';
  }
  return 0;
}

