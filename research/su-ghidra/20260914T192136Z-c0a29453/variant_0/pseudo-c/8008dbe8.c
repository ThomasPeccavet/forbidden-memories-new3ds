/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_8008dbe8(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  uint *puVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined1 *puVar14;
  undefined4 *puVar15;
  int iVar16;
  int local_30;
  
  iVar16 = 0;
  local_30 = 0;
  FUN_8008f4d8(&DAT_800ffa00,0x80);
  iVar11 = 0;
  FUN_8008f4d8(&DAT_800ffa00,0x80);
  do {
    FUN_8008d4e8();
    FUN_8008b2e8(param_1,0,&DAT_800ffa00);
    iVar6 = FUN_8008d6c8();
    if (iVar6 == 0) break;
    if (iVar6 == 4) {
      FUN_8008d4e8();
      FUN_8008b328(param_1);
      FUN_8008d6c8();
    }
    iVar11 = iVar11 + 1;
  } while (iVar11 < 8);
  if (iVar6 == 0) {
    iVar6 = -2;
    if (DAT_800ffa00 == 'M') {
      iVar6 = -2;
      if (DAT_800ffa01 == 'C') {
        iVar11 = 0;
        puVar15 = &DAT_800ff7c0;
        iVar6 = 1;
        do {
          *(undefined1 *)(iVar6 + -0x7ff00611) = 0;
          FUN_8008f4d8(&DAT_800ffa00,0x80);
          iVar13 = 0;
          FUN_8008f4d8(&DAT_800ffa00,0x80);
          do {
            FUN_8008d4e8();
            FUN_8008b2e8(param_1,iVar6,&DAT_800ffa00);
            iVar7 = FUN_8008d6c8();
            if (iVar7 == 0) break;
            if (iVar7 == 4) {
              FUN_8008d4e8();
              FUN_8008b328(param_1);
              FUN_8008d6c8();
            }
            iVar13 = iVar13 + 1;
          } while (iVar13 < 8);
          uVar4 = DAT_800ffa08;
          uVar3 = DAT_800ffa04;
          iVar11 = iVar11 + 1;
          if (iVar7 != 0) {
            return iVar7;
          }
          *puVar15 = _DAT_800ffa00;
          puVar15[1] = uVar3;
          puVar15[2] = uVar4;
          uVar4 = DAT_800ffa14;
          uVar3 = DAT_800ffa10;
          puVar15[3] = DAT_800ffa0c;
          puVar15[4] = uVar3;
          puVar15[5] = uVar4;
          uVar3 = DAT_800ffa1c;
          puVar15[6] = DAT_800ffa18;
          puVar15[7] = uVar3;
          puVar15 = puVar15 + 8;
          iVar6 = iVar6 + 1;
        } while (iVar11 < 0xf);
        uVar12 = 0;
        iVar11 = 0;
        do {
          if (*(int *)((int)&DAT_800ff7c0 + iVar11) == 0x51) {
            (&DAT_800ff9f0)[uVar12] = 1;
            sVar2 = *(short *)((int)&DAT_800ff7c8 + iVar11);
            uVar8 = uVar12;
            while ((sVar2 != -1 &&
                   (uVar8 = (uint)*(ushort *)(&DAT_800ff7c8 + uVar8 * 8), uVar8 < 0xf))) {
              (&DAT_800ff9f0)[uVar8] = 1;
              sVar2 = *(short *)(&DAT_800ff7c8 + uVar8 * 8);
            }
          }
          uVar12 = uVar12 + 1;
          iVar11 = uVar12 * 0x20;
        } while ((int)uVar12 < 0xf);
        iVar11 = 0;
        do {
          if ((&DAT_800ff9f0)[iVar11] == '\0') {
            (&DAT_800ff7c0)[iVar11 * 8] = 0xa0;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 0xf);
        iVar6 = 0;
        iVar11 = -0x7ff00836;
        do {
          if (((&DAT_800ff7c0)[iVar6 * 8] == 0x51) &&
             (iVar13 = FUN_8008f7f8(iVar11,param_2), iVar13 == 0)) {
            FUN_8008fa78(s___s____s__8001255c,iVar11,param_2);
            return -3;
          }
          iVar6 = iVar6 + 1;
          iVar11 = iVar11 + 0x20;
        } while (iVar6 < 0xf);
        iVar6 = 0;
        iVar11 = 0;
        do {
          uVar12 = *(uint *)((int)&DAT_800ff7c0 + iVar11);
          (&DAT_800ff9f0)[iVar6] = 0;
          if ((uVar12 & 0xf0) == 0xa0) {
            iVar16 = iVar16 + 1;
          }
          iVar6 = iVar6 + 1;
          iVar11 = iVar6 * 0x20;
        } while (iVar6 < 0xf);
        iVar6 = -1;
        if (param_3 <= iVar16) {
          iVar7 = 0;
          iVar11 = 0;
          iVar6 = 0;
          iVar16 = -0x7ff00836;
          puVar10 = &DAT_800ff7c0;
          iVar13 = 0;
          puVar14 = &DAT_800ff9f0;
          do {
            if ((*puVar10 & 0xf0) == 0xa0) {
              if (iVar7 == 0) {
                *puVar10 = 0x51;
                *(int *)((int)&DAT_800ff7c4 + iVar13) = param_3 << 0xd;
                FUN_8008fa08(iVar16,param_2,0x14);
              }
              else {
                *(short *)(&DAT_800ff7c8 + iVar11 * 8) = (short)iVar6;
                *puVar10 = 0x52;
              }
              *puVar14 = 1;
              iVar7 = iVar7 + 1;
              iVar11 = iVar6;
              if (param_3 <= iVar7) {
                *(undefined2 *)((int)&DAT_800ff7c8 + iVar13) = 0xffff;
                if (1 < iVar7) {
                  *puVar10 = 0x53;
                }
                break;
              }
            }
            puVar10 = puVar10 + 8;
            iVar13 = iVar13 + 0x20;
            puVar14 = puVar14 + 1;
            iVar6 = iVar6 + 1;
            iVar16 = iVar16 + 0x20;
          } while (iVar6 < 0xf);
          iVar11 = 0xe;
          puVar15 = &DAT_800ff980;
          do {
            if ((&DAT_800ff9f0)[iVar11] != '\0') {
              FUN_8008f4d8(&DAT_800ffa00,0x80);
              _DAT_800ffa00 = *puVar15;
              DAT_800ffa04 = puVar15[1];
              DAT_800ffa08 = puVar15[2];
              DAT_800ffa0c = puVar15[3];
              DAT_800ffa10 = puVar15[4];
              DAT_800ffa14 = puVar15[5];
              DAT_800ffa18 = puVar15[6];
              DAT_800ffa1c = puVar15[7];
              iVar6 = 0;
              bVar5 = 0;
              iVar16 = 0x7e;
              pbVar9 = (byte *)&DAT_800ffa00;
              do {
                bVar1 = *pbVar9;
                pbVar9 = pbVar9 + 1;
                iVar16 = iVar16 + -1;
                bVar5 = bVar5 ^ bVar1;
              } while (-1 < iVar16);
              *pbVar9 = bVar5;
              do {
                FUN_8008d4e8();
                FUN_8008b2d8(param_1,iVar11 + 1,&DAT_800ffa00);
                iVar16 = FUN_8008d6c8();
                if (iVar16 == 0) break;
                if (iVar16 == 4) {
                  FUN_8008d4e8();
                  FUN_8008b328(param_1);
                  FUN_8008d6c8();
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < 8);
              if (iVar16 != 0) {
                return iVar16;
              }
            }
            iVar11 = iVar11 + -1;
            puVar15 = puVar15 + -8;
          } while (-1 < iVar11);
          do {
            FUN_8008d4e8();
            FUN_8008b2c8(param_1);
            iVar6 = FUN_8008d5f0();
            if (iVar6 == 0) {
              return 0;
            }
            FUN_8008d4e8();
            FUN_8008b328(param_1);
            FUN_8008d6c8();
            local_30 = local_30 + 1;
          } while (local_30 < 8);
        }
      }
    }
  }
  return iVar6;
}

