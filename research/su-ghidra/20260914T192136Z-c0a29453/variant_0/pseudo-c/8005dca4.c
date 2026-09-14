/* Analysis pseudo-C, not buildable source. */

ushort * FUN_8005dca4(int *param_1)

{
  ushort uVar1;
  short sVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  code *pcVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  
  iVar16 = param_1[6];
  iVar19 = *param_1 + 4;
  iVar17 = param_1[7];
  uVar4 = (uint)*(ushort *)(*param_1 + 2);
  iVar15 = param_1[8];
  iVar13 = 0;
  if (uVar4 != 0) {
    uVar14 = 0xffff;
    do {
      uVar1 = *(ushort *)(iVar19 + 10);
      if (uVar1 != 0) {
        if (uVar1 != uVar14) {
          *(ushort *)(iVar19 + 10) = uVar1 - 1;
        }
        iVar18 = 1;
        if (*(char *)(iVar19 + 0xd) < '\0') {
          iVar18 = -1;
        }
        if (*(short *)(iVar19 + 0x10) == 0x7000) {
          iVar18 = 1;
LAB_8005dd70:
          *(undefined2 *)(iVar19 + 0x10) = 0;
        }
        else if (*(short *)(iVar19 + 0x10) == 0x6000) {
          iVar18 = -1;
          goto LAB_8005dd70;
        }
LAB_8005dd74:
        do {
          if ((*(short *)(iVar19 + 0x10) == 0) || (*(short *)(iVar19 + 0x12) == 0)) {
            *(undefined1 *)(iVar19 + 0x1b) = 0;
            if (iVar18 == 1) {
              pcVar10 = (char *)(*(ushort *)(iVar19 + 0x16) + 1);
              if ((*(uint *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17) & 0x80000000) == 0) {
LAB_8005deb0:
                iVar12 = 1;
                pcVar10 = (char *)(*(ushort *)(iVar19 + 0x16) + 1);
                *(ushort *)(iVar19 + 0x14) = *(ushort *)(iVar19 + 0x16);
                if (*(char *)(iVar19 + 0xd) < '\0') {
                  iVar12 = -1;
                }
                do {
                  while( true ) {
                    pcVar9 = *(char **)(((uint)pcVar10 & 0xffff) * 4 + iVar17);
                    pcVar6 = pcVar10;
                    if (((uint)pcVar9 & 0x80000000) == 0) goto LAB_8005df98;
                    if (((uint)pcVar9 & 0xc0000000) != 0x80000000) break;
                    uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                    if ((uVar7 == 0) || (*(byte *)(iVar19 + 0xc) == uVar7)) {
                      uVar5 = ((uint)pcVar9 & 0x3f800000) >> 0x17;
                      pcVar10 = pcVar9;
                      if ((uVar7 != 0) || (uVar5 != 0)) {
                        *(char *)(iVar19 + 0xc) = (char)uVar5;
                      }
                    }
                    else {
LAB_8005df70:
                      pcVar10 = pcVar10 + iVar12;
                    }
                  }
                  if (((uint)pcVar9 & 0xc0000000) != 0xc0000000) {
                    pcVar10 = s_S3000000_C_80011778;
                    iVar12 = 0x57;
                    FUN_8008fa78(s_Assertion_failed__file___s___lin_80011750);
                    FUN_80090dd8(1);
                    goto LAB_8005df70;
                  }
                  uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                  if (((uint)pcVar9 & 0x3f800000) != 0x800000) goto LAB_8005df70;
                  pcVar6 = (char *)0xffff;
                  if (uVar7 == 0) goto LAB_8005df98;
                  pcVar10 = pcVar10 + iVar12;
                } while (*(byte *)(iVar19 + 0xc) != uVar7);
                pcVar6 = (char *)0xffff;
LAB_8005df98:
                *(short *)(iVar19 + 0x16) = (short)pcVar6;
                goto LAB_8005e1a0;
              }
              iVar12 = 1;
              if (*(char *)(iVar19 + 0xd) < '\0') {
                iVar12 = -1;
              }
              do {
                while( true ) {
                  pcVar9 = *(char **)(((uint)pcVar10 & 0xffff) * 4 + iVar17);
                  pcVar6 = pcVar10;
                  if (((uint)pcVar9 & 0x80000000) == 0) goto LAB_8005dea0;
                  if (((uint)pcVar9 & 0xc0000000) != 0x80000000) break;
                  uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                  if ((uVar7 == 0) || (*(byte *)(iVar19 + 0xc) == uVar7)) {
                    uVar5 = ((uint)pcVar9 & 0x3f800000) >> 0x17;
                    pcVar10 = pcVar9;
                    if ((uVar7 != 0) || (uVar5 != 0)) {
                      *(char *)(iVar19 + 0xc) = (char)uVar5;
                    }
                  }
                  else {
LAB_8005de78:
                    pcVar10 = pcVar10 + iVar12;
                  }
                }
                if (((uint)pcVar9 & 0xc0000000) != 0xc0000000) {
                  pcVar10 = s_S3000000_C_80011778;
                  iVar12 = 0x57;
                  FUN_8008fa78(s_Assertion_failed__file___s___lin_80011750);
                  FUN_80090dd8(1);
                  goto LAB_8005de78;
                }
                uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                if (((uint)pcVar9 & 0x3f800000) != 0x800000) goto LAB_8005de78;
                pcVar6 = (char *)0xffff;
                if (uVar7 == 0) goto LAB_8005dea0;
                pcVar10 = pcVar10 + iVar12;
              } while (*(byte *)(iVar19 + 0xc) != uVar7);
              pcVar6 = (char *)0xffff;
LAB_8005dea0:
              *(short *)(iVar19 + 0x16) = (short)pcVar6;
              if (((uint)pcVar6 & 0xffff) != uVar14) goto LAB_8005deb0;
            }
            else {
              pcVar10 = (char *)((uint)*(ushort *)(iVar19 + 0x14) + iVar18);
              if ((*(uint *)((uint)*(ushort *)(iVar19 + 0x14) * 4 + iVar17) & 0x80000000) != 0) {
                iVar12 = 1;
                if (*(char *)(iVar19 + 0xd) < '\0') {
                  iVar12 = -1;
                }
                do {
                  while( true ) {
                    pcVar9 = *(char **)(((uint)pcVar10 & 0xffff) * 4 + iVar17);
                    pcVar6 = pcVar10;
                    if (((uint)pcVar9 & 0x80000000) == 0) goto LAB_8005e0a4;
                    if (((uint)pcVar9 & 0xc0000000) != 0x80000000) break;
                    uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                    if ((uVar7 == 0) || (*(byte *)(iVar19 + 0xc) == uVar7)) {
                      uVar5 = ((uint)pcVar9 & 0x3f800000) >> 0x17;
                      pcVar10 = pcVar9;
                      if ((uVar7 != 0) || (uVar5 != 0)) {
                        *(char *)(iVar19 + 0xc) = (char)uVar5;
                      }
                    }
                    else {
LAB_8005e07c:
                      pcVar10 = pcVar10 + iVar12;
                    }
                  }
                  if (((uint)pcVar9 & 0xc0000000) != 0xc0000000) {
                    pcVar10 = s_S3000000_C_80011778;
                    iVar12 = 0x57;
                    FUN_8008fa78(s_Assertion_failed__file___s___lin_80011750);
                    FUN_80090dd8(1);
                    goto LAB_8005e07c;
                  }
                  uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                  if (((uint)pcVar9 & 0x3f800000) != 0x800000) goto LAB_8005e07c;
                  pcVar6 = (char *)0xffff;
                  if (uVar7 == 0) goto LAB_8005e0a4;
                  pcVar10 = pcVar10 + iVar12;
                } while (*(byte *)(iVar19 + 0xc) != uVar7);
                pcVar6 = (char *)0xffff;
LAB_8005e0a4:
                *(short *)(iVar19 + 0x14) = (short)pcVar6;
                if (((uint)pcVar6 & 0xffff) == uVar14) goto LAB_8005e1ac;
              }
              iVar12 = 1;
              pcVar10 = (char *)((uint)*(ushort *)(iVar19 + 0x14) + iVar18);
              *(ushort *)(iVar19 + 0x16) = *(ushort *)(iVar19 + 0x14);
              if (*(char *)(iVar19 + 0xd) < '\0') {
                iVar12 = -1;
              }
              do {
                while( true ) {
                  pcVar9 = *(char **)(((uint)pcVar10 & 0xffff) * 4 + iVar17);
                  pcVar6 = pcVar10;
                  if (((uint)pcVar9 & 0x80000000) == 0) goto LAB_8005e19c;
                  if (((uint)pcVar9 & 0xc0000000) != 0x80000000) break;
                  uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                  if ((uVar7 == 0) || (*(byte *)(iVar19 + 0xc) == uVar7)) {
                    uVar5 = ((uint)pcVar9 & 0x3f800000) >> 0x17;
                    pcVar10 = pcVar9;
                    if ((uVar7 != 0) || (uVar5 != 0)) {
                      *(char *)(iVar19 + 0xc) = (char)uVar5;
                    }
                  }
                  else {
LAB_8005e174:
                    pcVar10 = pcVar10 + iVar12;
                  }
                }
                if (((uint)pcVar9 & 0xc0000000) != 0xc0000000) {
                  pcVar10 = s_S3000000_C_80011778;
                  iVar12 = 0x57;
                  FUN_8008fa78(s_Assertion_failed__file___s___lin_80011750);
                  FUN_80090dd8(1);
                  goto LAB_8005e174;
                }
                uVar7 = ((uint)pcVar9 & 0x7f0000) >> 0x10;
                if (((uint)pcVar9 & 0x3f800000) != 0x800000) goto LAB_8005e174;
                pcVar6 = (char *)0xffff;
                if (uVar7 == 0) goto LAB_8005e19c;
                pcVar10 = pcVar10 + iVar12;
              } while (*(byte *)(iVar19 + 0xc) != uVar7);
              pcVar6 = (char *)0xffff;
LAB_8005e19c:
              *(short *)(iVar19 + 0x14) = (short)pcVar6;
LAB_8005e1a0:
              if (((uint)pcVar6 & 0xffff) != uVar14) {
                if (iVar18 == 1) {
                  sVar2 = (ushort)*(byte *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17 + 2) *
                          0x10;
                  *(short *)(iVar19 + 0x12) = sVar2;
                  *(short *)(iVar19 + 0x10) = sVar2 - *(short *)(iVar19 + 0x10);
                }
                else {
                  *(ushort *)(iVar19 + 0x12) =
                       (ushort)*(byte *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17 + 2) << 4;
                }
                goto LAB_8005e208;
              }
            }
LAB_8005e1ac:
            *(undefined2 *)(iVar19 + 10) = 0;
            goto LAB_8005e378;
          }
LAB_8005e208:
          pcVar11 = *(code **)((*(byte *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17 + 3) & 0x7f)
                               * 4 + iVar16 + 4);
          piVar8 = param_1 + param_1[5] + 5;
          *piVar8 = iVar19;
          piVar8[1] = iVar15 + (uint)*(ushort *)((uint)*(ushort *)(iVar19 + 0x14) * 4 + iVar17) * 4;
          piVar8[2] = iVar15 + (uint)*(ushort *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17) * 4;
          if (*(ushort *)(iVar19 + 8) == uVar14) {
            piVar8[3] = 0;
          }
          else {
            piVar8[3] = iVar15 + (uint)*(ushort *)((uint)*(ushort *)(iVar19 + 8) * 4 + iVar17) * 4;
          }
          if (*(short *)(iVar19 + 0x14) == *(short *)(iVar19 + 0x16)) goto LAB_8005e378;
          iVar12 = (*pcVar11)(param_1);
          if (iVar12 == 1) {
            *(undefined2 *)(iVar19 + 0x10) = 0;
            goto LAB_8005dd74;
          }
        } while (*(char *)((uint)*(ushort *)(iVar19 + 0x16) * 4 + iVar17 + 2) == '\0');
        iVar12 = (uint)*(ushort *)(iVar19 + 0x10) - (int)*(char *)(iVar19 + 0xd);
        *(short *)(iVar19 + 0x10) = (short)iVar12;
        if ((iVar18 == 1) && (iVar12 * 0x10000 < 0)) {
          uVar3 = 0x7000;
        }
        else if ((iVar18 != -1) ||
                (uVar3 = 0x6000,
                (int)*(short *)(iVar19 + 0x10) < (int)(uint)*(ushort *)(iVar19 + 0x12)))
        goto LAB_8005e378;
        *(undefined2 *)(iVar19 + 0x10) = uVar3;
      }
LAB_8005e378:
      iVar13 = iVar13 + 1;
      iVar19 = iVar19 + (uint)*(ushort *)(iVar19 + 4) * 4;
    } while (iVar13 < (int)uVar4);
  }
  return (ushort *)*param_1 + (uint)*(ushort *)*param_1 * 2;
}

