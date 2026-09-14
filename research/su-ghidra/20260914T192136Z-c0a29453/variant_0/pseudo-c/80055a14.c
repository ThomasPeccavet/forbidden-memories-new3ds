/* Analysis pseudo-C, not buildable source. */

void FUN_80055a14(void)

{
  char cVar1;
  ushort uVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  short sVar8;
  ushort *puVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  uint uVar13;
  char cVar14;
  ushort uVar15;
  int iVar16;
  undefined4 uVar17;
  uint uVar18;
  undefined *puVar19;
  undefined1 uVar20;
  undefined *puVar21;
  uint uVar22;
  undefined4 local_40;
  int local_38;
  int local_30;
  
  puVar9 = &DAT_800f4088;
  local_38 = 0;
  local_30 = 0;
  do {
    if (((*puVar9 & 1) != 0) && (uVar13 = *puVar9 >> 1 & 1, (&DAT_800f4f97)[uVar13 * 0xe20] != '\0')
       ) {
      iVar10 = FUN_8005d9cc(uVar13,*(byte *)((int)puVar9 + 0x13));
      if (iVar10 == 0) {
        uVar2 = puVar9[5];
        uVar13 = (uint)puVar9[6];
        uVar18 = (uint)puVar9[7];
        uVar22 = *puVar9 >> 1 & 1;
        uVar7 = *puVar9 >> 3;
        iVar11 = uVar22 * 0xe20;
        puVar21 = &DAT_800f4178 + iVar11;
        uVar3 = (&DAT_800f4f7e)[uVar22 * 0x710];
        cVar1 = (&DAT_800f4d6d)[iVar11];
        uVar12 = FUN_8005cbb0(uVar22,0);
        uVar17 = (&DAT_800f4f38)[uVar22 * 0x388];
        iVar16 = uVar18 - uVar13;
        iVar10 = (uint)(byte)puVar9[8] * iVar16;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (iVar10 == -0x80000000)) {
          trap(0x1800);
        }
        uVar4 = (byte)puVar9[10] * uVar13;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (uVar4 == 0x80000000)) {
          trap(0x1800);
        }
        iVar5 = (uint)*(byte *)((int)puVar9 + 0x11) * iVar16;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (iVar5 == -0x80000000)) {
          trap(0x1800);
        }
        uVar6 = *(byte *)((int)puVar9 + 0x15) * uVar13;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (uVar6 == 0x80000000)) {
          trap(0x1800);
        }
        iVar16 = (uint)(byte)puVar9[9] * iVar16;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (iVar16 == -0x80000000)) {
          trap(0x1800);
        }
        uVar13 = (byte)puVar9[0xb] * uVar13;
        if (uVar18 == 0) {
          trap(0x1c00);
        }
        if ((uVar18 == 0xffffffff) && (uVar13 == 0x80000000)) {
          trap(0x1800);
        }
        local_40 = CONCAT13(*(byte *)((int)puVar9 + 0x13),
                            CONCAT12((char)(iVar16 / (int)uVar18) + (char)(uVar13 / uVar18),
                                     CONCAT11((char)(iVar5 / (int)uVar18) + (char)(uVar6 / uVar18),
                                              (char)(iVar10 / (int)uVar18) + (char)(uVar4 / uVar18))
                                    ));
        (&DAT_800f4f38)[uVar22 * 0x388] = local_40;
        iVar10 = 0;
        uVar20 = (undefined1)(uVar7 & 0x1f);
        puVar19 = puVar21;
        if ((&DAT_800f4f93)[iVar11] != '\0') {
          do {
            uVar15 = (ushort)(byte)(&DAT_800f4d6d)[iVar11];
            if ((uVar7 & 0x1f) != 0) {
              *(undefined1 *)(*(int *)(puVar19 + 0x1e0) + 0xc) = uVar20;
              uVar15 = uVar7 & 0x1f;
            }
            FUN_80050d8c(puVar21,iVar10,uVar15,uVar2);
            iVar10 = iVar10 + 1;
            puVar19 = puVar19 + 4;
          } while (iVar10 < (int)(uint)(byte)(&DAT_800f4f93)[iVar11]);
        }
        if ((uVar7 & 0x1f) != 0) {
          (&DAT_800f4d6d)[iVar11] = uVar20;
        }
        DAT_8009c32c = local_30 + -0x7ff0bf77;
        DAT_8009c32b = (byte)(*puVar9 >> 2) & 1;
        iVar10 = 0;
        FUN_8005721c(uVar22);
        DAT_8009c32c = 0;
        DAT_8009c32b = 0;
        puVar19 = puVar21;
        if ((&DAT_800f4f93)[iVar11] != '\0') {
          do {
            cVar14 = (&DAT_800f4d6d)[iVar11];
            if (cVar1 != '\0') {
              *(char *)(*(int *)(puVar19 + 0x1e0) + 0xc) = cVar1;
              cVar14 = cVar1;
            }
            FUN_80050d8c(puVar21,iVar10,cVar14,uVar3);
            iVar10 = iVar10 + 1;
            puVar19 = puVar19 + 4;
          } while (iVar10 < (int)(uint)(byte)(&DAT_800f4f93)[iVar11]);
        }
        if (cVar1 != '\0') {
          (&DAT_800f4d6d)[iVar11] = cVar1;
        }
        FUN_8005cbb0(uVar22,uVar12);
        (&DAT_800f4f38)[uVar22 * 0x388] = uVar17;
      }
      sVar8 = FUN_8005bf24();
      uVar2 = puVar9[6];
      puVar9[6] = uVar2 + sVar8;
      if (puVar9[7] <= (ushort)(uVar2 + sVar8)) {
        *puVar9 = *puVar9 & 0xfffe;
      }
    }
    puVar9 = puVar9 + 0xc;
    local_30 = local_30 + 0x18;
    local_38 = local_38 + 1;
  } while (local_38 < 10);
  return;
}

