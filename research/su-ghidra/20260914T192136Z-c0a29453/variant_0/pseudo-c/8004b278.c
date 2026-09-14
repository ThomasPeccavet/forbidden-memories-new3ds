/* Analysis pseudo-C, not buildable source. */

void FUN_8004b278(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  bool bVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined1 *puVar14;
  int iVar15;
  byte *pbVar16;
  ushort uVar17;
  byte *pbVar18;
  int local_44;
  byte local_2c;
  
  local_44 = 0;
  pbVar16 = (byte *)(DAT_8009c7d8 + (uint)param_1 * 0x18);
  iVar6 = *(int *)(DAT_8009c7d8 + 0x4a8);
  bVar1 = *pbVar16;
  iVar12 = 0;
  iVar15 = iVar6;
  if (bVar1 != 0) {
    do {
      if (*(char *)(iVar15 + 0x20) != '\0') {
        local_44 = local_44 + 1;
      }
      iVar12 = iVar12 + 1;
      iVar15 = iVar15 + 0x10;
    } while (iVar12 < (int)(uint)bVar1);
  }
  pbVar18 = (byte *)(iVar6 + (uint)bVar1 * 0x10 + 0x20);
  uVar17 = 0;
  if (*pbVar18 != 0) {
    local_2c = param_2 & 0x7f;
    do {
      iVar15 = iVar6 + (local_44 * 0x10 + (uint)uVar17) * 0x20 + 0x820;
      if ((*(byte *)(iVar15 + 6) <= param_2) && (param_2 <= *(byte *)(iVar15 + 7))) {
        bVar2 = pbVar16[6];
        bVar4 = false;
        if (((bVar2 & 0xf0) == 0) ||
           (((bVar2 & 0xf) < bVar2 >> 4 || (iVar12 = FUN_8004ace4((uint)param_1), iVar12 == -1)))) {
          iVar12 = FUN_8004add0(param_1,param_2);
        }
        else {
          bVar4 = true;
        }
        iVar7 = DAT_8009c7d8;
        iVar13 = 0;
        if (iVar12 != -1) {
          iVar11 = 0;
          puVar9 = (ushort *)
                   (*(int *)(DAT_8009c7d8 + 0x4a8) + (uint)*(ushort *)(iVar6 + 0x12) * 0x200 + 0x820
                   );
          puVar14 = (undefined1 *)(DAT_8009c7d8 + iVar12 * 0x28 + 0x180);
          if (0 < *(short *)(iVar15 + 0x16)) {
            do {
              iVar13 = iVar13 + 1;
              iVar11 = iVar11 + (uint)*puVar9;
              puVar9 = puVar9 + 1;
            } while (iVar13 < *(short *)(iVar15 + 0x16));
          }
          uVar10 = (&DAT_80011360)[iVar12];
          iVar13 = *(int *)(DAT_8009c7d8 + 0x4b8);
          *(undefined4 *)(DAT_8009c7d8 + 0x4c4) = 0x6019f;
          *(undefined2 *)(iVar7 + 0x4cc) = 0;
          *(undefined2 *)(iVar7 + 0x4ce) = 0;
          *(undefined4 *)(iVar7 + 0x4c0) = uVar10;
          *(int *)(iVar7 + 0x4dc) = iVar13 + iVar11 * 8;
          uVar5 = *(undefined2 *)(iVar15 + 0x10);
          *(undefined2 *)(iVar7 + 0x4fa) = uVar5;
          *(undefined2 *)(puVar14 + 0x20) = uVar5;
          uVar5 = *(undefined2 *)(iVar15 + 0x12);
          *(undefined2 *)(iVar7 + 0x4fc) = uVar5;
          *(undefined2 *)(puVar14 + 0x22) = uVar5;
          uVar10 = 5;
          if ((*(ushort *)(iVar15 + 0x10) & 0x80) == 0) {
            uVar10 = 1;
          }
          *(undefined4 *)(iVar7 + 0x4e4) = uVar10;
          *(undefined2 *)(puVar14 + 0x24) = *(undefined2 *)(DAT_8009c7d8 + 0x4e4);
          pbVar16[4] = param_3;
          puVar14[0x12] = *(undefined1 *)(iVar15 + 4);
          puVar14[0x13] = *(undefined1 *)(iVar15 + 5);
          puVar14[0x11] = *(undefined1 *)(iVar15 + 0xc);
          uVar3 = *(undefined1 *)(iVar15 + 0xd);
          *puVar14 = (char)iVar12;
          puVar14[4] = (char)uVar17;
          puVar14[2] = bVar1;
          puVar14[5] = local_2c;
          puVar14[3] = param_1;
          puVar14[0xd] = 1;
          puVar14[0x10] = uVar3;
          puVar14[6] = local_2c;
          puVar14[8] = pbVar18[1];
          puVar14[10] = pbVar18[4];
          puVar14[9] = *(undefined1 *)(iVar15 + 2);
          uVar3 = *(undefined1 *)(iVar15 + 3);
          puVar14[0xe] = param_3;
          *(undefined2 *)(puVar14 + 0x1e) = 0xffff;
          puVar14[0xb] = uVar3;
          FUN_8004a58c(DAT_8009c7d8 + iVar12 * 0x28 + 0x180,DAT_8009c7d8 + (uint)param_1 * 0x18);
          iVar7 = DAT_8009c7d8;
          *(short *)(DAT_8009c7d8 + 0x4c8) =
               (short)((int)((uint)*(ushort *)(puVar14 + 0x14) *
                            (uint)*(ushort *)(DAT_8009c7d8 + 0x514)) >> 7);
          *(short *)(iVar7 + 0x4ca) =
               (short)((int)((uint)*(ushort *)(puVar14 + 0x16) * (uint)*(ushort *)(iVar7 + 0x516))
                      >> 7);
          puVar14[5] = local_2c;
          bVar2 = pbVar16[7];
          *(undefined2 *)(puVar14 + 0x1a) = 0xffff;
          *(ushort *)(puVar14 + 0x1c) = (ushort)bVar2;
          iVar7 = FUN_8004a84c(puVar14,pbVar16[7]);
          uVar8 = iVar7 + (uint)(byte)puVar14[6] * 0x80;
          uVar5 = FUN_8004a444((int)(uVar8 * 0x10000) >> 0x17,uVar8 & 0x7f,
                               *(undefined1 *)(iVar15 + 4),*(undefined1 *)(iVar15 + 5));
          iVar7 = DAT_8009c7d8 + 0x4c0;
          *(undefined2 *)(DAT_8009c7d8 + 0x4d4) = uVar5;
          FUN_800776b8(iVar7);
          if ((!bVar4) && ((pbVar16[6] & 0xf) < 0xf)) {
            pbVar16[6] = pbVar16[6] + 1;
          }
          puVar14[0xf] = 1;
          if (pbVar16[0x10] == 0) {
            if ((*(byte *)(iVar15 + 1) & 4) == 0) {
              do {
                FUN_80076db8(0,(&DAT_80011360)[iVar12]);
                uVar8 = FUN_800770a8();
              } while ((uVar8 & (&DAT_80011360)[iVar12]) != 0);
            }
            else {
              do {
                FUN_80076db8(1,(&DAT_80011360)[iVar12]);
                uVar8 = FUN_800770a8();
              } while ((uVar8 & (&DAT_80011360)[iVar12]) == 0);
            }
          }
          else if (pbVar16[0x10] == 1) {
            do {
              FUN_80076db8(0,(&DAT_80011360)[iVar12]);
              uVar8 = FUN_800770a8();
            } while ((uVar8 & (&DAT_80011360)[iVar12]) != 0);
          }
          else {
            do {
              FUN_80076db8(1,(&DAT_80011360)[iVar12]);
              uVar8 = FUN_800770a8();
            } while ((uVar8 & (&DAT_80011360)[iVar12]) == 0);
          }
        }
      }
      uVar17 = uVar17 + 1;
    } while (uVar17 < *pbVar18);
  }
  return;
}

