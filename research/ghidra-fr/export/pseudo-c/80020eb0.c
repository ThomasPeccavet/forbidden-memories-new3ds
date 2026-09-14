/* Analysis pseudo-C, not buildable source. */

void FUN_80020eb0(void)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  char *unaff_s1;
  
  piVar9 = &DAT_801799d8;
  if ((DAT_8009c564 & 0x8000) == 0) {
    DAT_8009c564 = DAT_8009c564 | 0x8000;
    FUN_80040258();
    DAT_8009c6f4 = DAT_8009c584 != 0;
    DAT_8009c561 = DAT_8009c584;
    FUN_80014d38(0,0,(uint)DAT_8009c44b * 0x22 + 0x2290,0x22,FUN_80020b44,0,0);
    iVar7 = DAT_8009c4e8;
    DAT_8009c50c = 0x72e0;
    if ((DAT_8009c584 != 0) && (DAT_8009c50c = 0x72e0, -1 < DAT_8009c6f3)) {
      DAT_8009c50c = 0x72f0;
    }
    *(undefined2 *)(DAT_8009c4e8 + 0x28) = 0xff8c;
    *(undefined2 *)(iVar7 + 0x2c) = 0x30;
    *(undefined1 *)(iVar7 + 0x6c) = 1;
    *(code **)(iVar7 + 0x24) = FUN_8001ebd0;
    *(undefined2 *)(iVar7 + 0x2a) = *(undefined2 *)(iVar7 + 0x32);
    iVar7 = DAT_8009c55c;
    uVar2 = *(undefined2 *)(DAT_8009c55c + 0x32);
    *(undefined2 *)(DAT_8009c55c + 0x28) = 0x198;
    *(undefined2 *)(iVar7 + 0x2c) = 0x30;
    *(undefined1 *)(iVar7 + 0x6c) = 1;
    *(code **)(iVar7 + 0x24) = FUN_8001ebd0;
    DAT_8009c585 = 1;
    *(undefined2 *)(iVar7 + 0x2a) = uVar2;
  }
  else if (DAT_8009c57e == 0) {
    bVar6 = DAT_8009c585 & 0xf;
    if (bVar6 == 2) {
      if ((DAT_8009c585 & 0x80) == 0) {
        DAT_8009c585 = DAT_8009c585 | 0x80;
        iVar10 = 0;
        iVar7 = 0;
        do {
          if (DAT_8009c44b == 1) {
            if (DAT_8009c6f3 < '\0') {
              iVar8 = (uint)DAT_8009c584 * 0x28;
              puVar3 = (undefined *)0x80091b80;
            }
            else {
              iVar8 = (uint)DAT_8009c584 * 0x28;
              puVar3 = &DAT_80091b30;
            }
LAB_80021288:
            unaff_s1 = puVar3 + iVar8 + iVar7;
          }
          else {
            if (DAT_8009c44b == 2) {
              if (DAT_8009c6f3 < '\0') {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091c20;
              }
              else {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091bd0;
              }
              goto LAB_80021288;
            }
            if (DAT_8009c44b == 3) {
              if (DAT_8009c6f3 < '\0') {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091cc0;
              }
              else {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091c70;
              }
              goto LAB_80021288;
            }
            if (DAT_8009c44b == 4) {
              if (DAT_8009c6f3 < '\0') {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091d60;
              }
              else {
                iVar8 = (uint)DAT_8009c584 * 0x28;
                puVar3 = (undefined *)0x80091d10;
              }
              goto LAB_80021288;
            }
          }
          if ((*unaff_s1 != '\0') && (DAT_8009c2bc = iVar10 + 1, *piVar9 = 0, unaff_s1[2] != '\0'))
          {
            uVar4 = FUN_80040350();
            iVar8 = FUN_800403d0(uVar4,2);
            FUN_80042bd8(iVar8,*unaff_s1,unaff_s1[1],0,DAT_8009c584,unaff_s1[2],0x11,9,&DAT_801af000
                        );
            if (0x19 < *(byte *)(iVar8 + 0x69)) {
              *(short *)(iVar8 + 0x40) = *(short *)(iVar8 + 0x40) + 0x10;
            }
            *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x28;
            *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 0x50000000;
            bVar6 = unaff_s1[3];
            *(undefined2 *)(iVar8 + 0x4a) = 0x18;
            *(ushort *)(iVar8 + 0x48) = (ushort)bVar6;
            FUN_80042c48(iVar8);
            *(undefined4 *)(iVar8 + 0x2c) = *(undefined4 *)(iVar8 + 0x30);
            uVar1 = FUN_8008f708();
            *(ushort *)(iVar8 + 0x28) = (uVar1 & 0x3f) + 0x140;
            uVar2 = FUN_80035dfc(0x1000);
            *(undefined2 *)(iVar8 + 0x2a) = uVar2;
            *(undefined1 *)(iVar8 + 0x6c) = 1;
            *(code **)(iVar8 + 0x24) = FUN_80020cb0;
            *piVar9 = iVar8;
          }
          piVar9 = piVar9 + 3;
          iVar10 = iVar10 + 1;
          iVar7 = iVar7 + 4;
        } while (iVar10 < 10);
      }
      else if (((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) &&
              (iVar7 = FUN_80042e70(1), iVar7 == 0)) {
        DAT_8009c585 = 3;
      }
    }
    else if (bVar6 < 3) {
      if (bVar6 == 1) {
        if ((DAT_8009c585 & 0x80) == 0) {
          if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
            iVar7 = (int)DAT_8009c6f3;
            DAT_8009c57e = 8;
            if (iVar7 < 0) {
              iVar7 = 1;
            }
            DAT_8009c585 = DAT_8009c585 | 0x80;
            FUN_80014d38(0,0,iVar7 * 3 + 0x2218,3,0,0,&DAT_801781d8);
            FUN_80047738(DAT_8009c50c);
          }
        }
        else if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
          DAT_8009c585 = 2;
          FUN_8004022c(DAT_8009c50c);
        }
      }
    }
    else if (bVar6 == 3) {
      if ((DAT_8009c585 & 0x80) == 0) {
        DAT_8009c5c2 = 600;
        DAT_8009c585 = DAT_8009c585 | 0x80;
      }
      if ((DAT_8009c585 & 0x40) == 0) {
        DAT_8009c5c2 = DAT_8009c5c2 - 1;
        if ((((int)((uint)DAT_8009c5c2 << 0x10) < 1) || ((DAT_8009c72c & 0xe0) != 0)) ||
           (uVar5 = FUN_800474cc(), (uVar5 & 0x80) == 0)) {
          DAT_8009c585 = DAT_8009c585 | 0x40;
          iVar7 = 0;
          if (0 < DAT_8009c2bc) {
            do {
              iVar10 = *piVar9;
              if (iVar10 != 0) {
                *(undefined1 *)(iVar10 + 0x6c) = 1;
                *(code **)(iVar10 + 0x24) = FUN_80020e4c;
              }
              iVar7 = iVar7 + 1;
              piVar9 = piVar9 + 3;
            } while (iVar7 < DAT_8009c2bc);
          }
        }
      }
      else {
        iVar7 = FUN_80042e70(1);
        if (iVar7 == 0) {
          DAT_8009c585 = 4;
        }
      }
    }
    else if (bVar6 == 4) {
      if ((DAT_8009c585 & 0x80) == 0) {
        DAT_8009c585 = DAT_8009c585 | 0x80;
      }
      if ((DAT_800eb24e & 0x80) == 0) {
        DAT_8009c564 = 0xd;
      }
    }
  }
  return;
}

