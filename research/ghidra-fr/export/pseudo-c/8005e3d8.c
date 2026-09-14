/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8005e3d8(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined4 uVar8;
  uint *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  int *piVar16;
  
  piVar16 = (int *)(param_1 + *(int *)(param_1 + 0x14) * 4 + 0x14);
  puVar9 = (uint *)*piVar16;
  if (*(short *)((int)puVar9 + 0x12) == 0) {
    uVar8 = 1;
  }
  else {
    iVar14 = (int)(short)puVar9[4];
    uVar13 = (uint)*(ushort *)((int)puVar9 + 0x12);
    iVar12 = uVar13 - iVar14;
    iVar11 = *(short *)piVar16[1] * iVar14 + *(short *)piVar16[2] * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar11 == -0x80000000)) {
      trap(0x1800);
    }
    puVar15 = (undefined4 *)
              (*(int *)((*puVar9 >> 0x18) * 4 + param_1 + 0x14) + (*puVar9 & 0xffffff) * 4);
    puVar15[6] = iVar11 / (int)uVar13;
    iVar11 = *(short *)(piVar16[1] + 2) * iVar14 + *(short *)(piVar16[2] + 2) * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar11 == -0x80000000)) {
      trap(0x1800);
    }
    puVar15[7] = iVar11 / (int)uVar13;
    iVar11 = *(short *)(piVar16[1] + 4) * iVar14 + *(short *)(piVar16[2] + 4) * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar11 == -0x80000000)) {
      trap(0x1800);
    }
    puVar15[8] = iVar11 / (int)uVar13;
    iVar11 = piVar16[2];
    sVar5 = *(short *)(iVar11 + 6);
    sVar6 = *(short *)(iVar11 + 8);
    sVar7 = *(short *)(iVar11 + 10);
    iVar11 = piVar16[1];
    sVar1 = *(short *)(iVar11 + 6);
    sVar2 = *(short *)(iVar11 + 8);
    sVar3 = *(short *)(iVar11 + 10);
    if (uVar13 == 0x10) {
      iVar11 = (int)sVar1 - (int)sVar5;
      if (iVar11 < 0) {
        iVar11 = (int)sVar5 - (int)sVar1;
      }
      if (0x800 < iVar11) {
        if (sVar5 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar5 = sVar5 + sVar4;
      }
      iVar11 = (int)sVar2 - (int)sVar6;
      if (iVar11 < 0) {
        iVar11 = (int)sVar6 - (int)sVar2;
      }
      if (0x800 < iVar11) {
        if (sVar6 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar6 = sVar6 + sVar4;
      }
      iVar11 = (int)sVar3 - (int)sVar7;
      if (iVar11 < 0) {
        iVar11 = (int)sVar7 - (int)sVar3;
      }
      if (0x800 < iVar11) {
        if (sVar7 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar7 = sVar7 + sVar4;
      }
    }
    iVar12 = uVar13 - iVar14;
    iVar11 = sVar1 * iVar14 + sVar5 * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar11 == -0x80000000)) {
      trap(0x1800);
    }
    iVar10 = sVar2 * iVar14 + sVar6 * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar10 == -0x80000000)) {
      trap(0x1800);
    }
    iVar12 = sVar3 * iVar14 + sVar7 * iVar12;
    if (uVar13 == 0) {
      trap(0x1c00);
    }
    if ((uVar13 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    *(short *)(puVar15 + 0x11) = (short)(iVar11 / (int)uVar13);
    *(short *)((int)puVar15 + 0x46) = (short)(iVar10 / (int)uVar13);
    *(short *)(puVar15 + 0x12) = (short)(iVar12 / (int)uVar13);
    FUN_80088fe8(puVar15 + 0x11,puVar15 + 1);
    *puVar15 = 0;
    uVar8 = 0;
    if ((undefined2 *)piVar16[3] != (undefined2 *)0x0) {
      *(undefined2 *)piVar16[3] = *(undefined2 *)(puVar15 + 6);
      *(undefined2 *)(piVar16[3] + 2) = *(undefined2 *)(puVar15 + 7);
      *(undefined2 *)(piVar16[3] + 4) = *(undefined2 *)(puVar15 + 8);
      *(undefined2 *)(piVar16[3] + 6) = *(undefined2 *)(puVar15 + 0x11);
      *(undefined2 *)(piVar16[3] + 8) = *(undefined2 *)((int)puVar15 + 0x46);
      *(undefined2 *)(piVar16[3] + 10) = *(undefined2 *)(puVar15 + 0x12);
      uVar8 = 0;
    }
  }
  return uVar8;
}

