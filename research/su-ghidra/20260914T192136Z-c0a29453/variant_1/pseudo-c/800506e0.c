/* Analysis pseudo-C, not buildable source. */

void FUN_800506e0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  ushort *puVar9;
  int iVar10;
  uint uVar11;
  undefined *puVar12;
  undefined *puVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  iVar14 = 0;
  iVar17 = 0;
  iVar10 = 0;
  iVar16 = 0;
  iVar15 = 0;
  iVar2 = param_1 * 0xe20;
  puVar12 = &DAT_800f4178 + iVar2;
  (&DAT_800f4f7e)[param_1 * 0x710] = 0;
  *(undefined2 *)(&DAT_800f4f80 + iVar2) = 0;
  *(undefined4 *)(&DAT_800f4f50 + iVar2) = 0;
  *(undefined4 *)(&DAT_800f4f54 + iVar2) = 0;
  *(undefined4 *)(&DAT_800f4f58 + iVar2) = 0;
  *(undefined4 *)(&DAT_800f4f5c + iVar2) = 0;
  *(undefined4 *)(&DAT_800f4f68 + iVar2) = 0;
  puVar13 = puVar12;
  do {
    *(undefined2 *)(puVar13 + 0x7c4) = 0;
    iVar8 = 0;
    iVar4 = iVar15;
    iVar6 = iVar16;
    do {
      iVar8 = iVar8 + 1;
      *(undefined2 *)(puVar12 + iVar4 + 0x2c8) = 0xffff;
      *(undefined2 *)(puVar12 + iVar6 + 0x750) = 0;
      iVar4 = iVar4 + 2;
      iVar6 = iVar6 + 2;
    } while (iVar8 < 0x3a);
    iVar16 = iVar16 + 0x76;
    iVar15 = iVar15 + 0x74;
    iVar10 = iVar10 + 1;
    puVar13 = puVar13 + 0x76;
  } while (iVar10 < 10);
  iVar15 = 7;
  iVar10 = iVar2 + -0x7ff0be81;
  do {
    *(undefined1 *)(iVar10 + 0xbec) = 0;
    iVar15 = iVar15 + -1;
    iVar10 = iVar10 + -1;
  } while (-1 < iVar15);
  piVar5 = *(int **)(param_2 + 0x10);
  if (piVar5 != (int *)0x0) {
    do {
      if (piVar5[2] != 0) {
        if (*(char *)((int)piVar5 + 0xf) == '\x03') {
          iVar14 = piVar5[1];
        }
        if (*(char *)((int)piVar5 + 0xf) == '\x02') {
          iVar17 = piVar5[1];
        }
      }
      piVar5 = (int *)*piVar5;
    } while (piVar5 != (int *)0xffffffff);
    if (iVar14 != 0) {
      puVar9 = *(ushort **)(iVar14 + 8);
      uVar11 = 0;
      puVar7 = puVar9;
      if (*puVar9 != 0) {
        do {
          uVar3 = uVar11;
          if ((int)uVar11 < 0) {
            uVar3 = uVar11 + 7;
          }
          iVar10 = (int)uVar3 >> 3;
          bVar1 = puVar12[iVar10 + 0xbec];
          if ((*(uint *)(puVar7 + 2) & 0x100) != 0) {
            bVar1 = bVar1 | (byte)(1 << (uVar11 + iVar10 * -8 & 0x1f));
          }
          puVar12[iVar10 + 0xbec] = bVar1;
          uVar11 = uVar11 + 1;
          puVar7 = puVar7 + 2;
        } while (uVar11 < *puVar9);
      }
      *(undefined4 *)(&DAT_800f4f50 + iVar2) = *(undefined4 *)(iVar14 + 0xc);
      *(undefined4 *)(&DAT_800f4f54 + iVar2) = *(undefined4 *)(iVar14 + 0x10);
    }
    if (iVar17 != 0) {
      *(undefined4 *)(&DAT_800f4f58 + iVar2) = *(undefined4 *)(iVar17 + 4);
      *(undefined4 *)(&DAT_800f4f5c + iVar2) = *(undefined4 *)(iVar17 + 8);
    }
  }
  return;
}

