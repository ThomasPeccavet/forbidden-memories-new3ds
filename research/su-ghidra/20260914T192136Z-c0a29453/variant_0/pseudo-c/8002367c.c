/* Analysis pseudo-C, not buildable source. */

int FUN_8002367c(void)

{
  bool bVar1;
  int *piVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  undefined4 *puVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  piVar2 = DAT_8009c5b0;
  iVar5 = 0;
  if (DAT_8009c57e != 0) {
    if ((DAT_8009c57e & 0x8000) == 0) {
      uVar3 = DAT_8009c57e | 0x8000;
      uVar4 = DAT_8009c57e & 1;
      DAT_8009c57e = uVar3;
      if (uVar4 != 0) {
        FUN_80022e50(0x10,0x14e,0x3fe,*(undefined2 *)(&DAT_8009c2b0 + (uint)DAT_8009c504 * 2),
                     (int)*(short *)(&DAT_800919b4 +
                                    (char)DAT_8009c5b0[4] * 2 +
                                    (uint)*(byte *)(DAT_8009c5b0 + 6) * 8 +
                                    (uint)DAT_8009c504 * 0x10));
      }
      if ((DAT_8009c57e & 4) != 0) {
        FUN_80022e50(0x10,600,0x100,*(undefined2 *)(&DAT_8009c2b0 + (uint)DAT_8009c504 * 2),0);
        iVar9 = 5;
        FUN_80040690(piVar2[1]);
        iVar5 = -0x7fea3b50;
        puVar6 = &DAT_801a7b64;
        piVar2[1] = 0;
        do {
          if ((4 < iVar9 % 0xf) && ((*(ushort *)((int)puVar6 + 0x16) & 0x8000) != 0)) {
            iVar8 = *(int *)(iVar5 + 0x4b6b4);
            *(undefined1 *)(iVar8 + 0x6c) = 1;
            *(undefined2 *)(iVar8 + 0x60) = 4;
            *(code **)(iVar8 + 0x24) = FUN_80022ab0;
          }
          iVar5 = iVar5 + 0x1c;
          iVar9 = iVar9 + 1;
          puVar6 = puVar6 + 7;
        } while (iVar9 < 0x1e);
        DAT_8009c57e = DAT_8009c57e | 0x4000;
      }
      if ((DAT_8009c57e & 2) != 0) {
        iVar5 = FUN_800180e0(0,0x100);
        *(undefined1 *)((int)piVar2 + 0x16) = 0x24;
        if (*(char *)((int)piVar2 + 0x13) != '\0') {
          FUN_80040734(iVar5,*(char *)((int)piVar2 + 0x13));
          *(undefined1 *)((int)piVar2 + 0x16) = 7;
        }
        FUN_80042c1c(iVar5,(int)(((uint)*(byte *)((int)piVar2 + 0x17) * -2 + -2) * 0x1000000) >>
                           0x18);
        *(undefined2 *)(iVar5 + 0x28) = 0;
        *(short *)(iVar5 + 0x2a) = (short)piVar2[3];
        FUN_800434a8(iVar5);
        *(undefined2 *)(iVar5 + 0x60) = 0xfc00;
        *(undefined1 *)(iVar5 + 0x6c) = 2;
        *piVar2 = iVar5;
        if (piVar2[2] != 0) {
          iVar8 = 0;
          sVar7 = 0xe;
          iVar9 = 0;
          do {
            if (*(int *)(iVar9 + piVar2[2]) != 0) {
              *(short *)(*(int *)(iVar9 + piVar2[2]) + 0x30) = *(short *)(iVar5 + 0x30) + sVar7;
              *(short *)(*(int *)(iVar9 + piVar2[2]) + 0x32) = *(short *)(iVar5 + 0x32) + -0x1c;
            }
            sVar7 = sVar7 + 0x3c;
            iVar8 = iVar8 + 1;
            iVar9 = iVar9 + 0xc;
          } while (iVar8 < 5);
        }
        FUN_800230ac(piVar2,0);
      }
      if ((DAT_8009c57e & 8) != 0) {
        iVar5 = *piVar2;
        *(undefined2 *)(iVar5 + 0x2a) = 0x100;
        *(undefined2 *)(iVar5 + 0x28) = *(undefined2 *)(iVar5 + 0x30);
        FUN_800434a8(iVar5);
        *(undefined2 *)(iVar5 + 0x60) = 0x400;
        *(undefined1 *)(iVar5 + 0x6c) = 2;
        FUN_800230ac(piVar2,1);
      }
    }
    iVar5 = 0;
    bVar1 = false;
    if (((DAT_8009c57e & 0x40) != 0) && (iVar9 = piVar2[1], *(short *)(iVar9 + 0x60) != 0)) {
      iVar5 = (int)CONCAT21(*(undefined2 *)(iVar9 + 0x28),*(undefined1 *)(iVar9 + 0x62)) +
              (int)*(short *)(iVar9 + 0x36);
      *(char *)(iVar9 + 0x62) = (char)iVar5;
      *(short *)(iVar9 + 0x28) = (short)((uint)iVar5 >> 8);
      iVar5 = (int)CONCAT21(*(undefined2 *)(iVar9 + 0x2a),*(undefined1 *)(iVar9 + 100)) +
              (int)*(short *)(iVar9 + 0x3a);
      *(short *)(iVar9 + 0x2a) = (short)((uint)iVar5 >> 8);
      *(char *)(iVar9 + 100) = (char)iVar5;
      uVar4 = *(short *)(iVar9 + 0x60) - 1;
      *(ushort *)(iVar9 + 0x60) = uVar4;
      iVar5 = 1;
      if ((int)((uint)uVar4 << 0x10) < 1) {
        iVar5 = 0;
        *(undefined2 *)(iVar9 + 0x60) = 0;
        *(undefined4 *)(iVar9 + 0x28) = *(undefined4 *)(iVar9 + 0x2c);
      }
    }
    iVar9 = *piVar2;
    if (((DAT_8009c57e & 2) != 0) && (*(char *)(iVar9 + 0x6c) != '\0')) {
      iVar5 = 1;
      FUN_80043560(iVar9,(int)*(short *)(iVar9 + 0x28),(int)*(short *)(iVar9 + 0x2a),
                   (int)*(short *)(iVar9 + 0x60));
      uVar4 = *(short *)(iVar9 + 0x60) + 0x40;
      *(ushort *)(iVar9 + 0x60) = uVar4;
      bVar1 = true;
      if (-1 < (int)((uint)uVar4 << 0x10)) {
        *(undefined1 *)(iVar9 + 0x6c) = 0;
        *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x28);
      }
    }
    if (((DAT_8009c57e & 8) != 0) && (*(char *)(iVar9 + 0x6c) != '\0')) {
      iVar5 = 1;
      FUN_80043560(iVar9,(int)*(short *)(iVar9 + 0x28),(int)*(short *)(iVar9 + 0x2a),
                   (int)*(short *)(iVar9 + 0x60));
      uVar4 = *(short *)(iVar9 + 0x60) - 0x40;
      *(ushort *)(iVar9 + 0x60) = uVar4;
      bVar1 = true;
      if ((int)((uint)uVar4 << 0x10) < 0) {
        FUN_800360d8(&DAT_800f0850 + (uint)*(byte *)(piVar2 + 5) * 100);
        FUN_80040690(iVar9);
        *piVar2 = 0;
        if (piVar2[2] != 0) {
          iVar10 = 0;
          iVar8 = 0;
          do {
            iVar10 = iVar10 + 1;
            FUN_80040690(*(undefined4 *)(iVar8 + piVar2[2]));
            *(undefined4 *)(iVar8 + piVar2[2]) = 0;
            FUN_80040690(*(undefined4 *)(iVar8 + piVar2[2] + 4));
            *(undefined4 *)(iVar8 + piVar2[2] + 4) = 0;
            iVar8 = iVar8 + 0xc;
          } while (iVar10 < 5);
        }
        *(undefined1 *)(iVar9 + 0x6c) = 0;
        bVar1 = false;
      }
    }
    if (bVar1) {
      FUN_80039910(&DAT_800f0850 + (uint)*(byte *)(piVar2 + 5) * 100,*(short *)(iVar9 + 0x30) + 0x10
                   ,(int)*(short *)(iVar9 + 0x32) + (int)*(char *)((int)piVar2 + 0x16));
    }
    if ((DAT_8009c57e & 0x4000) != 0) {
      iVar5 = 1;
      iVar9 = FUN_80042e70(1);
      if (iVar9 != 0) {
        return 1;
      }
      DAT_8009c57e = DAT_8009c57e & 0xbfff;
    }
    sVar7 = DAT_8009c4cc + -1;
    if (DAT_8009c4cc != 0) {
      iVar5 = 1;
      DAT_8009c5c8 = DAT_8009c5c8 + DAT_8009c4dc;
      DAT_8009c540 = DAT_8009c540 + DAT_8009c570;
      DAT_800f11e0 = (undefined2)((uint)DAT_8009c5c8 >> 0x10);
      DAT_800f11e4 = (undefined2)((uint)DAT_8009c540 >> 0x10);
      DAT_8009c53c = DAT_8009c53c + DAT_8009c56c;
      DAT_8009c518 = DAT_8009c518 + DAT_8009c534;
      DAT_800f1204 = DAT_8009c518 >> 0x10;
      DAT_800f11e2 = (undefined2)((uint)DAT_8009c53c >> 0x10);
      bVar1 = DAT_8009c4cc == 1;
      DAT_8009c4cc = sVar7;
      if (bVar1) {
        DAT_800f1204 = (int)DAT_8009c530;
        DAT_800f11e0 = DAT_8009c4ca;
        DAT_800f11e4 = DAT_8009c566;
        DAT_800f11e2 = DAT_8009c562;
        if ((DAT_8009c57e & 1) != 0) {
          iVar8 = 5;
          iVar9 = -0x7fea3b50;
          puVar6 = &DAT_801a7b64;
          do {
            if ((4 < iVar8 % 0xf) && ((*(ushort *)((int)puVar6 + 0x16) & 0x8000) != 0)) {
              iVar10 = *(int *)(iVar9 + 0x4b6b4);
              *(undefined1 *)(iVar10 + 0x6c) = 1;
              *(undefined2 *)(iVar10 + 0x60) = 4;
              *(code **)(iVar10 + 0x24) = FUN_80022730;
            }
            iVar9 = iVar9 + 0x1c;
            iVar8 = iVar8 + 1;
            puVar6 = puVar6 + 7;
          } while (iVar8 < 0x1e);
          DAT_8009c57e = DAT_8009c57e | 0x4000;
        }
      }
      FUN_80013448();
    }
    if (iVar5 == 0) {
      if ((DAT_8009c57e & 1) != 0) {
        FUN_800235a0(piVar2);
        FUN_80023548(piVar2);
      }
      DAT_8009c57e = 0;
    }
  }
  return iVar5;
}

