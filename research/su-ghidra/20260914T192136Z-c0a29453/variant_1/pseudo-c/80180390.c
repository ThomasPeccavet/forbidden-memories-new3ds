/* Analysis pseudo-C, not buildable source. */

uint seed_80180390(void)

{
  short sVar1;
  bool bVar2;
  char cVar3;
  short sVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  int *piVar13;
  
  iVar6 = DAT_8018478c;
  if (DAT_801847c7 == '\0') {
    if (DAT_801847c8 == '\0') {
      if (DAT_801847c9 == '\0') {
        if (DAT_801847c6 == '\0') {
          iVar11 = (int)DAT_801847c4;
          if (iVar11 == 0) {
            if ((DAT_8018478c == 0) || ((*(ushort *)(DAT_8018478c + 8) & 0x40) == 0)) {
              iVar6 = 0;
              if (DAT_801847c5 == '\0') {
                if ((DAT_8009c728 & 0x5000) != 0) {
                  iVar6 = 0;
                  if (4 < DAT_801847c0) {
                    iVar6 = 5;
                  }
                  iVar11 = 6;
                  if (4 >= DAT_801847c0) {
                    iVar11 = 5;
                  }
                  FUN_80040734((&DAT_80184794)[DAT_801847c0],(uint)DAT_801847c0 << 1 | 1);
                  if ((DAT_8009c728 & 0x1000) == 0) {
                    iVar7 = ((uint)DAT_801847c0 - iVar6) + iVar11 + 1;
                  }
                  else {
                    iVar7 = ((uint)DAT_801847c0 - iVar6) + iVar11 + -1;
                  }
                  if (iVar11 == 0) {
                    trap(0x1c00);
                  }
                  if ((iVar11 == -1) && (iVar7 == -0x80000000)) {
                    trap(0x1800);
                  }
                  DAT_801847c0 = (char)(iVar7 % iVar11) + (char)iVar6;
                  FUN_80040734((&DAT_80184794)[DAT_801847c0],(uint)DAT_801847c0 << 1);
                  uVar10 = 6;
LAB_801809c4:
                  FUN_80048ae8(uVar10,0xff,0);
                  return 0xffffffff;
                }
                if ((DAT_8009c72c & 0x8e0) == 0) {
                  return 0xffffffff;
                }
                if ((DAT_8009c72c & 0x20) == 0) {
                  FUN_80048ae8(7,0xff,0);
                  if (DAT_801847c0 == 2) {
                    DAT_8009c738 = 0;
                    DAT_8009c77a = 0;
                    DAT_801847c9 = DAT_801847c9 + '\x01';
                    return 0xffffffff;
                  }
                  if (DAT_801847c0 < 3) {
                    if (DAT_801847c0 == 1) {
                      FUN_8003faf8();
                      DAT_801847c7 = DAT_801847c7 + '\x01';
                      return 0xffffffff;
                    }
                  }
                  else {
                    if (DAT_801847c0 == 3) {
                      DAT_8009c738 = 0;
                      DAT_8009c77a = 0;
                      DAT_801847c8 = DAT_801847c8 + '\x01';
                      return 0xffffffff;
                    }
                    if (DAT_801847c0 == 10) {
                      FUN_8003fba0();
                      DAT_801847c6 = DAT_801847c6 + '\x01';
                      return 0xffffffff;
                    }
                  }
                }
                else {
                  uVar10 = 9;
                  if (DAT_801847c0 < 5) goto LAB_801809c4;
                  FUN_80048ae8(8,0xff,0);
                  DAT_801847c1 = '\x01';
                }
                FUN_80180da4(1);
              }
              else {
                uVar9 = 0;
                piVar13 = &DAT_80184794;
                do {
                  iVar11 = *piVar13;
                  if ((iVar11 != 0) && (0 < *(short *)(iVar11 + 0x60))) {
                    bVar2 = DAT_801847c0 < 5;
                    *(short *)(iVar11 + 0x60) = *(short *)(iVar11 + 0x60) + -1;
                    if (bVar2) {
                      if ((int)uVar9 < 5) goto LAB_80180720;
LAB_801807ac:
                      iVar11 = *piVar13;
                      uVar5 = *(ushort *)(iVar11 + 8) & 0xffbf;
                    }
                    else {
                      if ((int)uVar9 < 5) goto LAB_801807ac;
LAB_80180720:
                      iVar11 = *piVar13;
                      sVar8 = *(short *)(iVar11 + 0x38);
                      sVar1 = *(short *)(iVar11 + 0x36);
                      uVar12 = 0x10 - (int)*(short *)(iVar11 + 0x60);
                      sVar4 = *(short *)(iVar11 + 0x38);
                      if (uVar12 != 0x10) {
                        iVar7 = FUN_80086628(uVar12 * 0x40);
                        iVar7 = iVar7 * ((int)sVar8 - (int)sVar1);
                        iVar11 = *piVar13;
                        if (iVar7 < 0) {
                          iVar7 = iVar7 + 0xfff;
                        }
                        sVar4 = *(short *)(iVar11 + 0x36) + (short)(iVar7 >> 0xc);
                      }
                      *(short *)(iVar11 + 0x30) = sVar4;
                      if ((uVar12 & 1) != 0) {
                        FUN_80180ee4(*piVar13);
                      }
                      iVar11 = *piVar13;
                      uVar5 = *(ushort *)(iVar11 + 8) | 0x40;
                    }
                    *(ushort *)(iVar11 + 8) = uVar5;
                    iVar6 = iVar6 + 1;
                    FUN_80040734(*piVar13,uVar9 << 1 | (uint)(DAT_801847c0 != uVar9));
                  }
                  uVar9 = uVar9 + 1;
                  piVar13 = piVar13 + 1;
                } while ((int)uVar9 < 0xb);
                if (iVar6 != 0) {
                  return 0xffffffff;
                }
                DAT_801847c5 = '\0';
                if (DAT_801847c2 != '\0') {
                  if (DAT_801847c1 == '\0') {
                    if (DAT_801847c0 != 1) {
                      DAT_801847c5 = 0;
                      return (uint)DAT_801847c0;
                    }
                    FUN_80180da4(0);
                    DAT_801847c0 = 5;
                  }
                  else {
                    iVar6 = 0;
                    if (DAT_801847c0 < 5) {
                      piVar13 = &DAT_80184794;
                      do {
                        iVar11 = *piVar13;
                        if (iVar11 != 0) {
                          *(ushort *)(iVar11 + 8) = *(ushort *)(iVar11 + 8) & 0xffbf;
                        }
                        iVar6 = iVar6 + 1;
                        piVar13 = piVar13 + 1;
                      } while (iVar6 < 0xb);
                      DAT_801847c4 = -1;
                    }
                    else {
                      FUN_80180da4(0);
                      DAT_801847c0 = 1;
                    }
                    DAT_801847c1 = '\0';
                  }
                }
              }
            }
            else {
              if (*(char *)(DAT_8018478c + 0x6c) == '\0') {
                cVar3 = *(char *)(DAT_8018478c + 0xe) + *(char *)(DAT_8018478c + 0x60);
                *(char *)(DAT_8018478c + 0xe) = cVar3;
                *(char *)(iVar6 + 0xd) = cVar3;
                *(char *)(iVar6 + 0xc) = cVar3;
                if (0x3e < *(byte *)(DAT_8018478c + 0xc) - 0x41) {
                  if ((int)((uint)*(byte *)(DAT_8018478c + 0xc) << 0x18) < 0) {
                    *(undefined1 *)(DAT_8018478c + 0x6c) = 0x3c;
                  }
                  *(short *)(DAT_8018478c + 0x60) = -*(short *)(DAT_8018478c + 0x60);
                }
              }
              else {
                *(char *)(DAT_8018478c + 0x6c) = *(char *)(DAT_8018478c + 0x6c) + -1;
              }
              if ((DAT_8009c72c & 0x800) == 0) {
                sVar8 = *(short *)(DAT_8018478c + 0x36) + DAT_8009c43c;
                *(short *)(DAT_8018478c + 0x36) = sVar8;
                if (2999 < sVar8) {
                  return 0xfffffffe;
                }
                return 0xffffffff;
              }
              FUN_80048ae8(7,0xff,0);
              *(ushort *)(DAT_8018478c + 8) = *(ushort *)(DAT_8018478c + 8) & 0xffbf;
              FUN_80180da4(0);
              DAT_801847c4 = '\x01';
            }
          }
          else {
            uVar9 = (uint)DAT_801847c3 + iVar11 * 8;
            DAT_801847c3 = (byte)uVar9;
            if ((iVar11 < 1) || (-1 < (int)(uVar9 * 0x1000000))) {
              if (-1 < iVar11) {
                return 0xffffffff;
              }
              if ((uVar9 & 0xff) != 0) {
                return 0xffffffff;
              }
            }
            if (DAT_801847c4 < '\0') {
              uVar5 = *(ushort *)(DAT_8018478c + 8);
              *(undefined1 *)(DAT_8018478c + 0xe) = 0x80;
              *(undefined1 *)(iVar6 + 0xd) = 0x80;
              *(undefined1 *)(iVar6 + 0xc) = 0x80;
              *(ushort *)(iVar6 + 8) = uVar5 | 0x40;
              *(undefined1 *)(DAT_8018478c + 0x6c) = 0x3c;
              *(undefined2 *)(DAT_8018478c + 0x36) = 0;
            }
            DAT_801847c4 = '\0';
          }
        }
        else {
          iVar6 = FUN_8003fa30();
          if (iVar6 == 0) {
            return 0xffffffff;
          }
          FUN_8003cd78();
          DAT_801847c6 = '\0';
        }
      }
      else {
        iVar6 = FUN_80040038();
        if (iVar6 != 0) {
          if (iVar6 == 1) {
            FUN_8003cd78();
            FUN_80180da4(1);
            DAT_801847c9 = '\0';
          }
          else {
            FUN_8003cd78();
            DAT_801847c9 = '\0';
          }
        }
      }
    }
    else {
      iVar6 = FUN_8003fffc();
      if (iVar6 != 0) {
        if (iVar6 == 1) {
          FUN_8003cd78();
          FUN_80180da4(1);
          DAT_801847c8 = '\0';
        }
        else {
          FUN_8003cd78();
          DAT_801847c8 = '\0';
        }
      }
    }
  }
  else {
    iVar6 = FUN_8003fb34();
    if (iVar6 != 0) {
      if (iVar6 == 1) {
        FUN_8003cd78();
        FUN_80180da4(1);
        DAT_801847c7 = '\0';
      }
      else {
        FUN_8003cd78();
        DAT_801847c7 = '\0';
      }
    }
  }
  return 0xffffffff;
}

