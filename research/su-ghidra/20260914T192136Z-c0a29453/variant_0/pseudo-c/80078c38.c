/* Analysis pseudo-C, not buildable source. */

void FUN_80078c38(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  short *psVar6;
  undefined4 local_18 [2];
  byte local_10 [8];
  
  if (DAT_800f7100 != 1) {
    if ((DAT_800f7104 == 0) || ((*DAT_800948d8 & 0x1000000) == 0)) {
      iVar2 = FUN_8007adb8(1,local_10);
      if (iVar2 != 5) {
        if ((local_10[0] & 4) == 0) {
          DAT_800f7120 = DAT_800f70e4 + DAT_800f70d4 * 0x10;
          if (*DAT_800f7120 == 0) {
            *DAT_800948b8 = 0;
            *DAT_800948c4 = 0;
            *DAT_800948b8 = 0;
            *DAT_800948c4 = 0x80;
            *DAT_800948c8 = 0x20943;
            *DAT_800948cc = 0x1323;
            uVar5 = 0;
            if (DAT_800f7160 == 0) {
              do {
                puVar4 = (undefined1 *)((int)local_18 + uVar5);
                uVar5 = uVar5 + 1;
                *puVar4 = *DAT_800948c0;
              } while (uVar5 < 4);
              uVar5 = 0;
              do {
                uVar5 = uVar5 + 1;
              } while (uVar5 < 8);
            }
            if (DAT_800f70e8 == 0) {
              FUN_80079580(3,DAT_800f7120,0,8,0x11000000,0,0);
            }
            else {
              FUN_80079554(DAT_800f7120,DAT_800f70e8 + DAT_800f70cc * 0x800,8,0);
            }
            puVar1 = DAT_800948c8;
            uVar5 = *DAT_800948e8;
            while ((uVar5 & 0x1000000) != 0) {
              uVar5 = *DAT_800948e8;
            }
            *(undefined4 *)(DAT_800f7120 + 0xe) = local_18[0];
            *puVar1 = 0x20843;
            *DAT_800948cc = 0x1325;
            if ((DAT_800f70fc == 1) && (DAT_800f70f8 != 0)) {
              if (DAT_800f70f8 != (ushort)DAT_800f7120[4]) {
                *DAT_800f7120 = 0;
                if (DAT_800f70e8 == 0) {
                  return;
                }
                DAT_800f70cc = DAT_800f70cc + 1;
                return;
              }
              DAT_800f70fc = 0;
            }
            if ((*DAT_800f7120 == 0x160) && (((ushort)DAT_800f7120[1] >> 10 & 0x1f) == DAT_800f70c0)
               ) {
              if (((int)DAT_800f70c8 == (uint)(ushort)DAT_800f7120[2]) &&
                 ((DAT_800f70ec == 0 || (DAT_800f70ec == (ushort)DAT_800f7120[4])))) {
                if (DAT_800f7120[2] == 0) {
                  DAT_800f70ec = (uint)(ushort)DAT_800f7120[4];
                  DAT_800f70c8 = 0;
                  if ((DAT_800f70d0 != 0) && (DAT_800f70d0 <= DAT_800f70ec)) {
                    DAT_800f70ec = 0;
                    DAT_800f70c8 = 0;
                    FUN_80078b18(DAT_800f70d8,DAT_800f70d4 - DAT_800f70d8);
                    DAT_800f70d4 = DAT_800f70d8;
                    *DAT_800f7120 = 0;
                    DAT_800f70fc = 1;
                    if (DAT_800f711c != (code *)0x0) {
                      (*DAT_800f711c)();
                    }
                    if (DAT_800f70e8 != 0) {
                      DAT_800f70cc = DAT_800f70cc + 1;
                    }
                    DAT_80094900 = 7;
                    return;
                  }
                  if ((DAT_800f70f0 - DAT_800f70d4) - 1U < (uint)(ushort)DAT_800f7120[3]) {
                    if (DAT_800f70d0 == 0) {
                      *DAT_800f7120 = 1;
                      DAT_800f70fc = 1;
                      if (DAT_800f711c != (code *)0x0) {
                        (*DAT_800f711c)();
                      }
                      if (DAT_800f70e8 != 0) {
                        DAT_800f70cc = DAT_800f70cc + 1;
                      }
                      DAT_80094900 = 8;
                      return;
                    }
                    if (*DAT_800f70e4 != 0) {
                      *DAT_800f7120 = 0;
                      if (DAT_800f70e8 != 0) {
                        DAT_800f70cc = DAT_800f70cc + 1;
                      }
                      DAT_80094900 = 9;
                      return;
                    }
                    *DAT_800f7120 = 1;
                    uVar5 = 0;
                    DAT_800f70d4 = 0;
                    psVar6 = DAT_800f70e4;
                    do {
                      uVar3 = *(undefined4 *)DAT_800f7120;
                      DAT_800f7120 = DAT_800f7120 + 2;
                      uVar5 = uVar5 + 1;
                      *(undefined4 *)psVar6 = uVar3;
                      psVar6 = psVar6 + 2;
                    } while (uVar5 < 8);
                    DAT_800f7120 = DAT_800f70e4;
                  }
                  DAT_800f70d8 = DAT_800f70d4;
                }
                DAT_80094900 = 10;
                DAT_800f70c8 = DAT_800f70c8 + 1;
                DAT_800f70e0 = DAT_800f70e4 + DAT_800f70f0 * 0x10 + DAT_800f70d4 * 0x3f0;
                uVar3 = 0x11000000;
                if (DAT_800f7104 == 0) {
                  uVar3 = 0x11400100;
                  *DAT_800948c8 = 0x21020843;
                }
                else {
                  *DAT_800948c8 = 0x20943;
                  *DAT_800948cc = 0x1323;
                }
                if ((ushort)DAT_800f7120[3] - 1 == (uint)(ushort)DAT_800f7120[2]) {
                  DAT_800f7100 = 1;
                  if (DAT_800f70e8 == 0) {
                    FUN_80079580(3,DAT_800f70e0,0,0x1f8,uVar3,1,0);
                  }
                  else {
                    FUN_80079554(DAT_800f70e0,DAT_800f70e8 + DAT_800f70cc * 0x800 + 0x20,0x1f8,1);
                    DAT_800f70cc = DAT_800f70cc + 1;
                  }
                  DAT_800f70c8 = 0;
                  DAT_800f70ec = 0;
                  DAT_800f70c0 = DAT_800f70c4;
                }
                else if (DAT_800f70e8 == 0) {
                  FUN_80079580(3,DAT_800f70e0,0,0x1f8,uVar3,0,0);
                }
                else {
                  FUN_80079554(DAT_800f70e0,DAT_800f70e8 + DAT_800f70cc * 0x800 + 0x20,0x1f8,0);
                  DAT_800f70cc = DAT_800f70cc + 1;
                }
                *DAT_800948cc = 0x1325;
                *DAT_800f7120 = 3;
                DAT_800f70d4 = DAT_800f70d4 + 1;
                if ((DAT_800f70e8 != 0) && (DAT_800f7100 != 0)) {
                  FUN_800788e8();
                }
              }
              else {
                DAT_800f70ec = 0;
                DAT_800f70c8 = 0;
                FUN_80078b18(DAT_800f70d8,DAT_800f70d4 - DAT_800f70d8);
                DAT_800f70d4 = DAT_800f70d8;
                *DAT_800f7120 = 0;
                if (DAT_800f70e8 != 0) {
                  DAT_800f70cc = DAT_800f70cc + 1;
                }
                DAT_80094900 = 6;
              }
            }
            else {
              if (DAT_800f70e8 != 0) {
                DAT_800f70cc = 0;
              }
              DAT_80094900 = 5;
              *DAT_800f7120 = 0;
            }
          }
          else {
            if (DAT_800f70e8 != 0) {
              DAT_800f70cc = DAT_800f70cc + 1;
            }
            DAT_80094900 = 4;
          }
        }
        else {
          DAT_80094900 = 3;
        }
      }
    }
    else {
      DAT_800f70f4 = 1;
      if (DAT_800f70e8 != 0) {
        DAT_800f70cc = DAT_800f70cc + 1;
      }
      DAT_80094900 = 1;
    }
  }
  return;
}

