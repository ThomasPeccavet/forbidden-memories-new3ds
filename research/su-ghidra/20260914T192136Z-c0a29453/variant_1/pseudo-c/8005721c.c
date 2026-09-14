/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80058148) */
/* WARNING: Removing unreachable block (ram,0x80058130) */
/* WARNING: Removing unreachable block (ram,0x80058160) */

void FUN_8005721c(int param_1)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  ushort uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  short sVar13;
  uint uVar14;
  int *piVar15;
  ushort *puVar16;
  short sVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int *piVar22;
  int iVar23;
  int iVar24;
  short sVar25;
  int iVar27;
  int *piVar28;
  int iVar29;
  int iVar30;
  undefined *puVar31;
  short sVar32;
  int iVar33;
  short *psVar34;
  short sVar35;
  int iVar36;
  short sVar37;
  short asStack_8a8 [16];
  short local_888;
  ushort local_886;
  short local_884;
  undefined2 local_882;
  int local_880;
  undefined4 local_87c;
  undefined4 local_878;
  undefined4 local_874;
  short local_870 [2];
  short local_86c;
  short local_868;
  undefined1 local_865;
  byte local_864;
  byte local_863;
  byte local_862;
  undefined1 local_861;
  undefined4 local_860;
  undefined2 local_85c;
  undefined2 local_85a;
  undefined4 local_858;
  undefined1 local_854;
  undefined1 local_853;
  undefined1 local_852;
  undefined4 local_850 [2];
  ushort local_848 [1024];
  undefined4 local_48;
  int local_44;
  undefined4 *local_40;
  int local_3c;
  uint local_38;
  short *local_34;
  short local_30;
  int iVar26;
  
  if (param_1 < 2) {
    local_40 = DAT_8009c860;
  }
  else {
    local_40 = DAT_8009c864;
  }
  iVar9 = param_1 * 0xe20;
  piVar28 = (int *)(&DAT_800f4178 + iVar9);
  local_3c = param_1 * 0x10 + 0xd0;
  if ((&DAT_800f4f97)[iVar9] == '\0') {
    return;
  }
  if ((((param_1 == 2) && (DAT_800f6b58 == -0x1000)) && (DAT_800f6b5c == -0x1000)) &&
     (DAT_800f6b60 == -0x1000)) {
    return;
  }
  if ((((&DAT_800f4f89)[iVar9] != '\x01') && (1 < *(byte *)((int)&DAT_800f4f38 + iVar9 + 3))) &&
     (((&DAT_800f4f38)[param_1 * 0x388] & 0xffffff) == 0)) {
    return;
  }
  FUN_80085768(0,&DAT_800f4ee8 + iVar9);
  FUN_80085768(1,&DAT_800f4ef8 + iVar9);
  FUN_80085768(2,&DAT_800f4f08 + iVar9);
  FUN_80085cd8(*(undefined4 *)(&DAT_800f4f18 + iVar9),*(undefined4 *)(&DAT_800f4f1c + iVar9),
               *(undefined4 *)(&DAT_800f4f20 + iVar9));
  DAT_8009c370 = *(undefined4 *)(&DAT_800f4f68 + iVar9);
  DAT_8009c374._0_1_ = (&DAT_800f4f89)[iVar9];
  if ((&DAT_800f4f89)[iVar9] != '\x04') {
    (&DAT_800f4f89)[iVar9] = 0;
  }
  if (param_1 < 2) {
    *local_40 = 0xe;
    if ((((uint)(byte)(&DAT_800f4f3f)[iVar9] % 6 == 0) ||
        (*(char *)((int)&DAT_800f4f38 + iVar9 + 3) != '\0')) || ((byte)DAT_8009c374 != 0)) {
      if ((byte)DAT_8009c374 == 1) goto LAB_80057774;
      DAT_8009c378 = *(byte *)((int)&DAT_800f4f38 + iVar9 + 2);
      DAT_8009c374._3_1_ = *(byte *)((int)&DAT_800f4f38 + iVar9 + 1);
      DAT_8009c374._2_1_ = *(byte *)(&DAT_800f4f38 + param_1 * 0x388);
      uVar18 = (uint)*(byte *)((int)&DAT_800f4f38 + iVar9 + 3);
      uVar14 = (uint)DAT_8009c378 << 0x10 | (uint)DAT_8009c374._3_1_ << 8 | (uint)DAT_8009c374._2_1_
      ;
      if (uVar18 != 0) {
        uVar14 = uVar14 | 0x2000000;
      }
      DAT_8009c33c = uVar14 | 0x24000000;
      DAT_8009c340 = uVar14 | 0x2c000000;
      DAT_8009c344 = uVar14 | 0x34000000;
      DAT_8009c348 = uVar14 | 0x3c000000;
      DAT_8009c35c = uVar14 | 0x4a000000;
      DAT_8009c360 = uVar14 | 0x4e000000;
      DAT_8009c34c = uVar14 | 0x26000000;
      DAT_8009c350 = uVar14 | 0x2e000000;
      DAT_8009c354 = uVar14 | 0x36000000;
      DAT_8009c358 = uVar14 | 0x3e000000;
      if (uVar18 == 2) {
LAB_800576f8:
        DAT_8009c368 = 0x200000;
      }
      else if (uVar18 == 3) {
        DAT_8009c368 = 0x400000;
      }
      else if (uVar18 == 4) {
        DAT_8009c368 = 0x600000;
      }
      else {
        if (uVar18 == 5) goto LAB_800576f8;
        DAT_8009c368 = 0;
      }
      if (uVar18 == 5) {
        DAT_8009c36c = 0x3c280000;
      }
      else {
        DAT_8009c36c = 0;
      }
      DAT_8009c374._1_1_ = uVar18 - 1 < 4;
      if ((bool)DAT_8009c374._1_1_) {
        DAT_8009c364 = (uVar18 - 1) * 0x20 & 0x9ff | 0xe1000200;
      }
      else {
        DAT_8009c364 = 0xe1000220;
      }
      if ((&DAT_800f4f38)[param_1 * 0x388] == 0x808080) goto LAB_800575f0;
      DAT_8009c374._0_1_ = 3;
      (&DAT_800f4f3f)[iVar9] = 0;
    }
    else {
      iVar10 = FUN_8005bf24();
      iVar10 = iVar10 * 2;
      DAT_8009c378 = (&DAT_800f4f3e)[iVar9];
      DAT_8009c374._3_1_ = (&DAT_800f4f3d)[iVar9];
      DAT_8009c374._2_1_ = (&DAT_800f4f3c)[iVar9];
      uVar18 = (uint)(byte)(&DAT_800f4f3f)[iVar9];
      uVar14 = (uint)DAT_8009c378 << 0x10 | (uint)DAT_8009c374._3_1_ << 8 | (uint)DAT_8009c374._2_1_
      ;
      if (uVar18 != 0) {
        uVar14 = uVar14 | 0x2000000;
      }
      DAT_8009c33c = uVar14 | 0x24000000;
      DAT_8009c340 = uVar14 | 0x2c000000;
      DAT_8009c344 = uVar14 | 0x34000000;
      DAT_8009c348 = uVar14 | 0x3c000000;
      DAT_8009c35c = uVar14 | 0x4a000000;
      DAT_8009c360 = uVar14 | 0x4e000000;
      DAT_8009c34c = uVar14 | 0x26000000;
      DAT_8009c350 = uVar14 | 0x2e000000;
      DAT_8009c354 = uVar14 | 0x36000000;
      DAT_8009c358 = uVar14 | 0x3e000000;
      if (uVar18 == 2) {
LAB_800574f0:
        DAT_8009c368 = 0x200000;
      }
      else {
        DAT_8009c368 = 0x400000;
        if (uVar18 != 3) {
          if (uVar18 == 4) {
            DAT_8009c368 = 0x600000;
          }
          else {
            if (uVar18 == 5) goto LAB_800574f0;
            DAT_8009c368 = 0;
          }
        }
      }
      if (uVar18 == 5) {
        DAT_8009c36c = 0x3c280000;
      }
      else {
        DAT_8009c36c = 0;
      }
      DAT_8009c374._1_1_ = uVar18 - 1 < 4;
      if ((bool)DAT_8009c374._1_1_) {
        DAT_8009c364 = (uVar18 - 1) * 0x20 & 0x9ff | 0xe1000200;
      }
      else {
        DAT_8009c364 = 0xe1000220;
      }
      DAT_8009c374._0_1_ = 3;
      uVar14 = (uint)*(byte *)(&DAT_800f4f38 + param_1 * 0x388);
      if ((int)((uint)(byte)(&DAT_800f4f3c)[iVar9] + iVar10) <
          (int)(uint)*(byte *)(&DAT_800f4f38 + param_1 * 0x388)) {
        uVar14 = (uint)(byte)(&DAT_800f4f3c)[iVar9] + iVar10;
      }
      uVar18 = (uint)*(byte *)((int)&DAT_800f4f38 + iVar9 + 1);
      (&DAT_800f4f3c)[iVar9] = (char)uVar14;
      if ((int)((uint)(byte)(&DAT_800f4f3d)[iVar9] + iVar10) < (int)uVar18) {
        uVar18 = (uint)(byte)(&DAT_800f4f3d)[iVar9] + iVar10;
      }
      uVar14 = (uint)*(byte *)((int)&DAT_800f4f38 + iVar9 + 2);
      (&DAT_800f4f3d)[iVar9] = (char)uVar18;
      if ((int)((uint)(byte)(&DAT_800f4f3e)[iVar9] + iVar10) < (int)uVar14) {
        uVar14 = (uint)(byte)(&DAT_800f4f3e)[iVar9] + iVar10;
      }
      bVar1 = *(byte *)(&DAT_800f4f38 + param_1 * 0x388);
      (&DAT_800f4f3e)[iVar9] = (char)uVar14;
      if (((bVar1 <= (byte)(&DAT_800f4f3c)[iVar9]) &&
          (*(byte *)((int)&DAT_800f4f38 + iVar9 + 1) <= (byte)(&DAT_800f4f3d)[iVar9])) &&
         ((uint)*(byte *)((int)&DAT_800f4f38 + iVar9 + 2) <= (uVar14 & 0xff))) {
LAB_800575f0:
        (&DAT_800f4f3f)[iVar9] = 0;
      }
    }
  }
  else {
LAB_80057774:
    DAT_8009c374._2_1_ = 0x80;
    DAT_8009c374._3_1_ = 0x80;
    DAT_8009c378 = 0x80;
    DAT_8009c33c = 0x24808080;
    DAT_8009c340 = 0x2c808080;
    DAT_8009c344 = 0x34808080;
    DAT_8009c348 = 0x3c808080;
    DAT_8009c35c = 0x4a808080;
    DAT_8009c360 = 0x4e808080;
    DAT_8009c34c = 0x26808080;
    DAT_8009c350 = 0x2e808080;
    DAT_8009c354 = 0x36808080;
    DAT_8009c358 = 0x3e808080;
    DAT_8009c368 = 0;
    DAT_8009c36c = 0;
    DAT_8009c374._1_1_ = 0;
    DAT_8009c364 = 0xe1000220;
  }
  if (2 < (byte)DAT_8009c374) {
    DAT_8009c370 = 0;
  }
  iVar10 = 0;
  piVar22 = piVar28;
  if ((&DAT_800f4f92)[iVar9] != '\0') {
    do {
      bVar4 = false;
      if ((DAT_8009c32b == '\0') || (iVar10 <= (int)(uint)(byte)(&DAT_800f4f8f)[iVar9])) {
        if ((DAT_8009c32c != 0) &&
           ((0 < iVar10 && (iVar19 = iVar10 + -1, iVar10 <= (int)(uint)(byte)(&DAT_800f4f8f)[iVar9])
            ))) {
          iVar11 = iVar19;
          if (iVar19 < 0) {
            iVar11 = iVar10 + 6;
          }
          if ((((int)(uint)*(byte *)(DAT_8009c32c + (iVar11 >> 3)) >>
                (iVar19 + (iVar11 >> 3) * -8 & 0x1fU) & 1U) == 0) &&
             (bVar4 = true, DAT_8009c32b != '\0')) goto LAB_80057b80;
        }
        if (piVar22[1] != 0) {
          if ((*(int *)(&DAT_800f4e94 + iVar9) != 0) &&
             (*(int *)(*piVar22 + 0x4c) == *(int *)(&DAT_800f4e94 + iVar9))) {
            iVar19 = 0;
            bVar3 = false;
            piVar15 = piVar28;
            if ((byte)(&DAT_800f4f93)[iVar9] != 0) {
              do {
                if (*(int *)piVar15[0x78] ==
                    ((*piVar22 - *(int *)(&DAT_800f4e8c + iVar9)) * -0x33333333 >> 4) * 0x14 +
                    0x4000001) {
                  if (*(short *)(piVar15[0x78] + 10) == -1) {
                    iVar11 = iVar19;
                    if (iVar19 < 0) {
                      iVar11 = iVar19 + 7;
                    }
                    if ((((int)(uint)*(byte *)((int)piVar28 + (iVar11 >> 3) + 0xbec) >>
                          (iVar19 + (iVar11 >> 3) * -8 & 0x1fU) & 1U) != 0) &&
                       (*(short *)((int)piVar28 +
                                  ((uint)(byte)(&DAT_800f4d6d)[iVar9] * 0x3b + iVar19) * 2 + 0x750)
                        != 0)) {
                      bVar3 = true;
                    }
                  }
                  break;
                }
                iVar19 = iVar19 + 1;
                piVar15 = piVar15 + 1;
              } while (iVar19 < (int)(uint)(byte)(&DAT_800f4f93)[iVar9]);
            }
            if (bVar3) {
              FUN_800875f8(*piVar22 + 4,&DAT_800f4f28 + iVar9);
            }
            else {
              FUN_8005c334(*piVar22,&DAT_800f4f28 + iVar9);
            }
          }
          if ((*(int *)piVar22[1] != -1) || (((int *)piVar22[1])[2] != 0)) {
            if (bVar4) {
              FUN_8008f548(asStack_8a8,0,0x20);
              psVar34 = asStack_8a8;
LAB_80057b68:
              FUN_80085558(psVar34);
            }
            else {
              iVar19 = *piVar22;
              if (iVar19 != 0) {
                if ((byte)DAT_8009c374 == 0) {
                  FUN_8008a6e8(iVar19,&local_888);
                  psVar34 = &local_888;
                }
                else {
                  FUN_8008a9b8(iVar19,&local_868,&local_888);
                  uVar14 = 0;
                  psVar34 = &local_868;
                  iVar19 = 8;
                  do {
                    uVar18 = (uint)*psVar34;
                    if ((int)uVar18 < 0) {
                      uVar18 = -uVar18;
                    }
                    if ((int)(uVar14 & 0xffff) < (int)uVar18) {
                      uVar14 = uVar18;
                    }
                    iVar19 = iVar19 + -1;
                    psVar34 = psVar34 + 1;
                  } while (-1 < iVar19);
                  uVar14 = uVar14 & 0xffff;
                  psVar34 = &local_868;
                  if (uVar14 == 0) {
                    local_858 = CONCAT22(local_858._2_2_,0x1000);
                    local_860 = CONCAT22(local_860._2_2_,0x1000);
                    local_868 = 0x1000;
                  }
                  else {
                    iVar19 = 0;
                    do {
                      if (uVar14 == 0) {
                        trap(0x1c00);
                      }
                      if ((uVar14 == 0xffffffff) && ((int)*psVar34 << 0xc == -0x80000000)) {
                        trap(0x1800);
                      }
                      iVar19 = iVar19 + 1;
                      *psVar34 = (short)(((int)*psVar34 << 0xc) / (int)uVar14);
                      psVar34 = psVar34 + 1;
                    } while (iVar19 < 9);
                  }
                  FUN_80085588(&local_868);
                  psVar34 = &local_888;
                }
                goto LAB_80057b68;
              }
            }
            FUN_8008a0d8(piVar22,local_40,0x1f800000);
          }
        }
      }
LAB_80057b80:
      iVar10 = iVar10 + 1;
      piVar22 = piVar22 + 2;
    } while (iVar10 < (int)(uint)(byte)(&DAT_800f4f92)[iVar9]);
  }
  if (DAT_8009c32c != 0) {
    if (1 < param_1) {
      return;
    }
    *local_40 = 0xc;
    return;
  }
  if (param_1 < 2) {
    iVar10 = 0x7fff;
    sVar6 = 0x7fff;
    if (*(int *)(&DAT_800f4e94 + iVar9) != 0) {
      iVar26 = 0x7fff;
      sVar25 = 0x7fff;
      iVar19 = -0x8000;
      sVar7 = -0x8000;
      iVar11 = -0x8000;
      sVar13 = -0x8000;
      iVar24 = -0x8000;
      sVar17 = -0x8000;
      iVar36 = 0;
      iVar20 = 0;
      iVar33 = 0;
      iVar23 = 0;
      local_30 = 0x7fff;
      iVar27 = 0;
      piVar22 = piVar28;
      if ((byte)(&DAT_800f4f92)[iVar9] != 0) {
        do {
          iVar21 = *piVar22;
          if (((iVar21 != 0) && (piVar15 = (int *)piVar22[1], piVar15 != (int *)0x0)) &&
             ((*piVar15 != -1 || (piVar15[2] != 0)))) {
            iVar23 = iVar23 + 1;
            iVar33 = iVar33 + *(int *)(iVar21 + 0x38);
            iVar36 = iVar36 + *(int *)(iVar21 + 0x40);
            iVar20 = iVar20 + *(int *)(iVar21 + 0x3c);
          }
          iVar27 = iVar27 + 1;
          piVar22 = piVar22 + 2;
        } while (iVar27 < (int)(uint)(byte)(&DAT_800f4f92)[iVar9]);
      }
      if (iVar23 == 0) {
        iVar20 = *(int *)(&DAT_800f4e94 + iVar9);
        iVar27 = *(int *)(iVar20 + 0x38);
        sVar37 = (short)*(undefined4 *)(iVar20 + 0x3c);
        sVar35 = (short)*(undefined4 *)(iVar20 + 0x40);
      }
      else {
        iVar27 = iVar33 / iVar23;
        if (iVar23 == 0) {
          trap(0x1c00);
        }
        if ((iVar23 == -1) && (iVar33 == -0x80000000)) {
          trap(0x1800);
        }
        sVar37 = (short)(iVar20 / iVar23);
        if (iVar23 == 0) {
          trap(0x1c00);
        }
        if ((iVar23 == -1) && (iVar20 == -0x80000000)) {
          trap(0x1800);
        }
        sVar35 = (short)(iVar36 / iVar23);
        if (iVar23 == 0) {
          trap(0x1c00);
        }
        if ((iVar23 == -1) && (iVar36 == -0x80000000)) {
          trap(0x1800);
        }
      }
      iVar20 = *(char *)(&DAT_800f4e74 + param_1 * 0x388) * 0x10;
      if (0 < param_1) {
        iVar20 = *(char *)(&DAT_800f4e74 + param_1 * 0x388) * -0x10;
      }
      sVar32 = (short)(iVar27 + iVar20);
      (&DAT_800f4f48)[param_1 * 0x710] = sVar32;
      (&DAT_800f4f4a)[param_1 * 0x710] = sVar37 + *(char *)((int)&DAT_800f4e74 + iVar9 + 1) * 0x10;
      sVar5 = (short)*(char *)((int)&DAT_800f4e74 + iVar9 + 2);
      sVar37 = sVar5 * 0x10;
      if (0 < param_1) {
        sVar37 = sVar5 * -0x10;
      }
      sVar35 = sVar35 + sVar37;
      iVar23 = 0;
      iVar33 = 0;
      cVar2 = (&DAT_800f4f92)[iVar9];
      iVar36 = 0;
      (&DAT_800f4f4c)[param_1 * 0x710] = sVar35;
      if (cVar2 != '\0') {
        do {
          iVar21 = *piVar28;
          if ((((iVar21 != *(int *)(&DAT_800f4e94 + iVar9)) &&
               (iVar21 != (&DAT_800f4e90)[param_1 * 0x388])) && (iVar21 != 0)) &&
             (piVar22 = (int *)piVar28[1], piVar22 != (int *)0x0)) {
            if (*(int *)(iVar21 + 0x4c) == *(int *)(&DAT_800f4e94 + iVar9)) {
              iVar33 = iVar33 + 1;
              iVar23 = iVar23 + *(int *)(iVar21 + 0x3c);
            }
            if ((*piVar22 != -1) || (piVar22[2] != 0)) {
              iVar29 = *(int *)(iVar21 + 0x38);
              iVar30 = *(int *)(iVar21 + 0x40);
              iVar21 = *(int *)(iVar21 + 0x3c);
              if ((short)iVar19 < iVar29) {
                iVar19 = iVar29;
              }
              if (iVar29 < (short)iVar10) {
                iVar10 = iVar29;
              }
              if ((short)iVar11 < iVar21) {
                iVar11 = iVar21;
              }
              if (iVar21 < (short)iVar26) {
                iVar26 = iVar21;
              }
              if ((short)iVar24 < iVar30) {
                iVar24 = iVar30;
              }
              if (iVar30 < local_30) {
                local_30 = (short)iVar30;
              }
            }
          }
          sVar17 = (short)iVar24;
          sVar25 = (short)iVar26;
          sVar13 = (short)iVar11;
          sVar6 = (short)iVar10;
          sVar7 = (short)iVar19;
          iVar36 = iVar36 + 1;
          piVar28 = piVar28 + 2;
        } while (iVar36 < (int)(uint)(byte)(&DAT_800f4f92)[iVar9]);
      }
      if (iVar33 == 0) {
        iVar10 = *(int *)(*(int *)(&DAT_800f4e94 + iVar9) + 0x3c);
      }
      else {
        iVar10 = iVar23 / iVar33;
        if (iVar33 == 0) {
          trap(0x1c00);
        }
        if ((iVar33 == -1) && (iVar23 == -0x80000000)) {
          trap(0x1800);
        }
      }
      iVar11 = (int)sVar7 - (int)sVar6;
      iVar19 = (int)sVar17 - (int)local_30;
      sVar6 = (&DAT_800f4f46)[param_1 * 0x710];
      *(short *)(&DAT_800f4f4e + iVar9) =
           ((short)((ulonglong)((longlong)(iVar10 + -700) * 0x55555556) >> 0x20) -
           (short)(iVar10 + -700 >> 0x1f)) + *(char *)((int)&DAT_800f4e74 + iVar9 + 1) * 0x10;
      if (sVar6 < iVar11) {
        (&DAT_800f4f46)[param_1 * 0x710] = (short)iVar11;
      }
      if ((short)(&DAT_800f4f46)[param_1 * 0x710] < iVar19) {
        (&DAT_800f4f46)[param_1 * 0x710] = (short)iVar19;
      }
      iVar11 = iVar11 + 0x32;
      iVar24 = ((int)sVar13 - (int)sVar25) + 0x32;
      iVar10 = (int)(short)(&DAT_800f4f40)[param_1 * 0x710];
      iVar19 = iVar19 + 0x32;
      if (iVar10 == 0) {
        (&DAT_800f4f40)[param_1 * 0x710] = (short)iVar11;
      }
      else if (iVar11 < iVar10) {
        sVar6 = -(short)(iVar10 - iVar11);
        if (0x14 < iVar10 - iVar11) {
          sVar6 = -0x14;
        }
        (&DAT_800f4f40)[param_1 * 0x710] = (&DAT_800f4f40)[param_1 * 0x710] + sVar6;
      }
      else {
        sVar6 = (short)(iVar11 - iVar10);
        if (0x14 < iVar11 - iVar10) {
          sVar6 = 0x14;
        }
        (&DAT_800f4f40)[param_1 * 0x710] = (&DAT_800f4f40)[param_1 * 0x710] + sVar6;
      }
      iVar10 = (int)(short)(&DAT_800f4f42)[param_1 * 0x710];
      if (iVar10 == 0) {
        (&DAT_800f4f42)[param_1 * 0x710] = (short)iVar24;
      }
      else if (iVar24 < iVar10) {
        sVar6 = -(short)(iVar10 - iVar24);
        if (0x14 < iVar10 - iVar24) {
          sVar6 = -0x14;
        }
        (&DAT_800f4f42)[param_1 * 0x710] = (&DAT_800f4f42)[param_1 * 0x710] + sVar6;
      }
      else {
        sVar6 = (short)(iVar24 - iVar10);
        if (0x14 < iVar24 - iVar10) {
          sVar6 = 0x14;
        }
        (&DAT_800f4f42)[param_1 * 0x710] = (&DAT_800f4f42)[param_1 * 0x710] + sVar6;
      }
      iVar10 = (int)(short)(&DAT_800f4f44)[param_1 * 0x710];
      if (iVar10 == 0) {
        (&DAT_800f4f44)[param_1 * 0x710] = (short)iVar19;
      }
      else if (iVar19 < iVar10) {
        sVar6 = -(short)(iVar10 - iVar19);
        if (0x14 < iVar10 - iVar19) {
          sVar6 = -0x14;
        }
        (&DAT_800f4f44)[param_1 * 0x710] = (&DAT_800f4f44)[param_1 * 0x710] + sVar6;
      }
      else {
        sVar6 = (short)(iVar19 - iVar10);
        if (0x14 < iVar19 - iVar10) {
          sVar6 = 0x14;
        }
        (&DAT_800f4f44)[param_1 * 0x710] = (&DAT_800f4f44)[param_1 * 0x710] + sVar6;
      }
      if ((&DAT_800f4f8a)[iVar9] != '\0') {
        if ((byte)DAT_8009c374 == 1) goto LAB_800584f8;
        local_865 = 6;
        local_861 = 0x30;
        local_864 = DAT_8009c374._2_1_;
        local_863 = DAT_8009c374._3_1_;
        local_862 = DAT_8009c378;
        local_854 = (undefined1)((int)(uint)DAT_8009c374._2_1_ >> 4);
        local_853 = (undefined1)((int)(uint)DAT_8009c374._3_1_ >> 4);
        local_85c = CONCAT11(local_853,local_854);
        local_852 = (undefined1)((int)(uint)DAT_8009c378 >> 4);
        local_85a = CONCAT11(local_85a._1_1_,local_852);
        uVar12 = FUN_8005c328();
        FUN_80085558(uVar12);
        FUN_8005afa4(param_1,local_870);
        iVar11 = (int)local_870[0];
        iVar19 = (int)local_86c;
        iVar10 = 300;
        if ((299 < iVar11) && (iVar10 = 800, iVar11 < 0x321)) {
          iVar10 = iVar11;
        }
        if (iVar19 < 300) {
          iVar11 = 300;
        }
        else {
          iVar11 = 800;
          if (iVar19 < 0x321) {
            iVar11 = iVar19;
          }
        }
        local_886 = DAT_8009c322;
        if (DAT_8009c322 == 0x8000) {
          local_886 = (short)*(undefined4 *)(DAT_800f6ad0 + 0x1c) +
                      *(short *)(PTR_DAT_8009c318 + 0xa2);
        }
        iVar19 = 0;
        iVar24 = (iVar27 + iVar20) * 0x10000 >> 0x10;
        local_38 = (uint)(iVar24 < 0x4b1);
        local_34 = &local_868;
        psVar34 = &DAT_800929ac;
        local_878 = CONCAT22(local_886,sVar32 + (short)(iVar10 / 2));
        local_874 = CONCAT22(local_874._2_2_,sVar35);
        local_880 = (uint)local_886 << 0x10;
        do {
          iVar26 = (int)*psVar34 * (iVar10 / 2);
          if (iVar26 < 0) {
            iVar26 = iVar26 + 0xfff;
          }
          sVar6 = sVar32 + (short)(iVar26 >> 0xc);
          local_880 = CONCAT22(local_880._2_2_,sVar6);
          iVar26 = (int)psVar34[1] * (iVar11 / 2);
          if (iVar26 < 0) {
            iVar26 = iVar26 + 0xfff;
          }
          sVar7 = sVar35 + (short)(iVar26 >> 0xc);
          local_87c = CONCAT22(local_87c._2_2_,sVar7);
          local_888 = sVar32;
          local_884 = sVar35;
          if ((PTR_DAT_8009c318[0xa1] & 1) == 0) {
LAB_8005844c:
            iVar26 = FUN_800879d8(&local_888,&local_880,&local_878,&local_860,&local_858,local_850,
                                  &local_48,&local_44);
            local_48 = FUN_80087928(local_860,local_858,local_850[0]);
            if ((-1 < iVar26) && (-1 < local_44)) {
              FUN_8004d5b8(local_34,local_40,0xfff,2);
            }
          }
          else {
            local_888 = -0x4b0;
            if ((-0x4b1 < iVar24) && (local_888 = sVar32, local_38 == 0)) {
              local_888 = 0x4b0;
            }
            if (sVar35 < -0x4b0) {
              local_884 = -0x4b0;
            }
            else if (0x4b0 < sVar35) {
              local_884 = 0x4b0;
            }
            if (sVar6 < -0x4b0) {
              sVar6 = -0x4b0;
            }
            else if (0x4b0 < sVar6) {
              sVar6 = 0x4b0;
            }
            local_880 = CONCAT22(local_880._2_2_,sVar6);
            if (sVar7 < -0x4b0) {
              sVar7 = -0x4b0;
            }
            else if (0x4b0 < sVar7) {
              sVar7 = 0x4b0;
            }
            local_87c = CONCAT22(local_87c._2_2_,sVar7);
            if ((short)local_878 < -0x4b0) {
              sVar13 = -0x4b0;
            }
            else {
              sVar13 = (short)local_878;
              if (0x4b0 < (short)local_878) {
                sVar13 = 0x4b0;
              }
            }
            local_878 = CONCAT22(local_878._2_2_,sVar13);
            sVar17 = -0x4b0;
            if ((-0x4b1 < (short)local_874) && (sVar17 = (short)local_874, 0x4b0 < (short)local_874)
               ) {
              sVar17 = 0x4b0;
            }
            iVar26 = (int)sVar6;
            local_874 = CONCAT22(local_874._2_2_,sVar17);
            if (iVar26 != sVar13) {
LAB_8005840c:
              iVar26 = (int)sVar7;
              if (iVar26 == sVar17) {
                iVar20 = (int)local_884;
                if (iVar26 < 0) {
                  iVar26 = -iVar26;
                }
                if (iVar20 < 0) {
                  iVar20 = -iVar20;
                }
                if (iVar26 <= iVar20) goto LAB_800584b8;
              }
              goto LAB_8005844c;
            }
            iVar20 = (int)local_888;
            if (iVar26 < 0) {
              iVar26 = -iVar26;
            }
            if (iVar20 < 0) {
              iVar20 = -iVar20;
            }
            if (iVar20 < iVar26) goto LAB_8005840c;
          }
LAB_800584b8:
          local_878 = local_880;
          local_874 = local_87c;
          iVar19 = iVar19 + 1;
          psVar34 = psVar34 + 2;
        } while (iVar19 < 8);
      }
    }
  }
  if ((byte)DAT_8009c374 != 1) {
    if ((&DAT_800f4f88)[iVar9] == '\0') {
      cVar2 = *(char *)((int)&DAT_800f4f84 + iVar9 + 3);
      if (cVar2 != '\0') {
        if (cVar2 == (&DAT_800f4d6d)[iVar9]) {
          if ((&DAT_800f4f8e)[iVar9] != '#') {
            (&DAT_800f4d6e)[iVar9] = 0;
          }
        }
        else {
          FUN_8005c8d0(param_1,cVar2,0);
        }
      }
    }
    else {
      FUN_8005ac78(param_1,0xffffffff,0);
    }
    cVar2 = (&DAT_800f4f8b)[iVar9];
    if ((cVar2 != '\0') && (cVar2 != -1)) {
      if (cVar2 == -2) {
        iVar19 = 0;
        local_888 = 0x280;
        local_884 = 0x100;
        local_882 = 4;
        iVar10 = local_3c;
        do {
          local_886 = (short)iVar10;
          do {
            iVar11 = FUN_8008288c(3);
          } while (iVar11 != 0);
          do {
            iVar11 = FUN_8008246c(&local_888,local_848);
          } while (iVar11 != 0);
          do {
            iVar11 = FUN_8008288c(3);
            puVar16 = local_848;
          } while (iVar11 != 0);
          iVar11 = 0;
          do {
            if (*puVar16 != 0) {
              *puVar16 = *puVar16 | 0x8000;
            }
            iVar11 = iVar11 + 1;
            puVar16 = puVar16 + 1;
            local_886 = (short)iVar10;
          } while (iVar11 < 0x400);
          do {
            iVar11 = FUN_8008288c(3);
          } while (iVar11 != 0);
          do {
            iVar11 = FUN_80082380(&local_888,local_848);
          } while (iVar11 != 0);
          do {
            iVar11 = FUN_8008288c(3);
          } while (iVar11 != 0);
          iVar19 = iVar19 + 4;
          iVar10 = iVar10 + 4;
        } while (iVar19 < 8);
        FUN_8005c808(param_1,0);
        (&DAT_800f4f8b)[iVar9] = 0;
      }
      else {
        (&DAT_800f4f8b)[iVar9] = cVar2 + -1;
        local_85c = 2;
        local_85a = 8;
        local_860 = CONCAT22((short)param_1 * 0x10 + 0xd8,
                             (ushort)(byte)(&DAT_800f4f8b)[iVar9] * 2 + 0x280);
        do {
          iVar10 = FUN_8008288c(3);
        } while (iVar10 != 0);
        do {
          iVar10 = FUN_8008246c(&local_860,&local_880);
        } while (iVar10 != 0);
        do {
          iVar10 = FUN_8008288c(3);
          iVar19 = 0;
        } while (iVar10 != 0);
        puVar16 = (ushort *)&local_880;
        do {
          iVar19 = iVar19 + 1;
          uVar8 = FUN_80068264(*puVar16,6,0x1000);
          *puVar16 = uVar8 & 0x7fff;
          puVar16 = puVar16 + 1;
        } while (iVar19 < 0x10);
        local_860 = CONCAT22((undefined2)local_3c,(undefined2)local_860);
        do {
          iVar10 = FUN_8008288c(3);
        } while (iVar10 != 0);
        do {
          iVar10 = FUN_80082380(&local_860,&local_880);
        } while (iVar10 != 0);
        do {
          iVar10 = FUN_8008288c(3);
        } while (iVar10 != 0);
        if ((&DAT_800f4f8b)[iVar9] == '\0') {
          iVar10 = param_1 * 0xe20;
          puVar31 = &DAT_800f4178 + iVar10;
          if (((&DAT_800f4f97)[iVar10] != '\0') && (iVar19 = 0, (&DAT_800f4f92)[iVar10] != '\0')) {
            do {
              piVar28 = *(int **)(puVar31 + 4);
              if (piVar28 != (int *)0x0) {
                do {
                  if (piVar28[2] != 0) {
                    FUN_8005d644(&LAB_80068884,piVar28 + 3,piVar28[1]);
                  }
                  piVar28 = (int *)*piVar28;
                } while (piVar28 != (int *)0xffffffff);
              }
              iVar19 = iVar19 + 1;
              puVar31 = puVar31 + 8;
            } while (iVar19 < (int)(uint)(byte)(&DAT_800f4f92)[iVar10]);
          }
          (&DAT_800f4f8b)[iVar9] = 0xfe;
        }
      }
    }
    if (1 < param_1) {
      return;
    }
    *local_40 = 0xc;
    return;
  }
LAB_800584f8:
  if (param_1 < 2) {
    *local_40 = 0xc;
  }
  return;
}

