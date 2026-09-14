/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8005e860(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined4 uVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int *piVar15;
  undefined4 *puVar16;
  int iVar17;
  int local_30;
  int local_2c;
  int local_28;
  
  piVar15 = (int *)(param_1 + *(int *)(param_1 + 0x14) * 4 + 0x14);
  puVar10 = (uint *)*piVar15;
  if (*(short *)((int)puVar10 + 0x12) == 0) {
    uVar8 = 1;
  }
  else {
    iVar17 = (int)(short)puVar10[4];
    uVar14 = (uint)*(ushort *)((int)puVar10 + 0x12);
    iVar13 = uVar14 - iVar17;
    iVar12 = *(short *)piVar15[1] * iVar17 + *(short *)piVar15[2] * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    puVar16 = (undefined4 *)
              (*(int *)((*puVar10 >> 0x18) * 4 + param_1 + 0x14) + (*puVar10 & 0xffffff) * 4);
    puVar16[6] = iVar12 / (int)uVar14;
    iVar12 = *(short *)(piVar15[1] + 2) * iVar17 + *(short *)(piVar15[2] + 2) * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    puVar16[7] = iVar12 / (int)uVar14;
    iVar12 = *(short *)(piVar15[1] + 4) * iVar17 + *(short *)(piVar15[2] + 4) * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    puVar16[8] = iVar12 / (int)uVar14;
    iVar12 = piVar15[2];
    sVar5 = *(short *)(iVar12 + 6);
    sVar6 = *(short *)(iVar12 + 8);
    sVar7 = *(short *)(iVar12 + 10);
    iVar12 = piVar15[1];
    sVar1 = *(short *)(iVar12 + 6);
    sVar2 = *(short *)(iVar12 + 8);
    sVar3 = *(short *)(iVar12 + 10);
    if (uVar14 == 0x10) {
      iVar12 = (int)sVar1 - (int)sVar5;
      if (iVar12 < 0) {
        iVar12 = (int)sVar5 - (int)sVar1;
      }
      if (0x800 < iVar12) {
        if (sVar5 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar5 = sVar5 + sVar4;
      }
      iVar12 = (int)sVar2 - (int)sVar6;
      if (iVar12 < 0) {
        iVar12 = (int)sVar6 - (int)sVar2;
      }
      if (0x800 < iVar12) {
        if (sVar6 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar6 = sVar6 + sVar4;
      }
      iVar12 = (int)sVar3 - (int)sVar7;
      if (iVar12 < 0) {
        iVar12 = (int)sVar7 - (int)sVar3;
      }
      if (0x800 < iVar12) {
        if (sVar7 < 1) {
          sVar4 = 0x1000;
        }
        else {
          sVar4 = -0x1000;
        }
        sVar7 = sVar7 + sVar4;
      }
    }
    iVar13 = uVar14 - iVar17;
    iVar12 = sVar1 * iVar17 + sVar5 * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    iVar11 = sVar2 * iVar17 + sVar6 * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar11 == -0x80000000)) {
      trap(0x1800);
    }
    iVar9 = sVar3 * iVar17 + sVar7 * iVar13;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar9 == -0x80000000)) {
      trap(0x1800);
    }
    *(short *)(puVar16 + 0x11) = (short)(iVar12 / (int)uVar14);
    *(short *)((int)puVar16 + 0x46) = (short)(iVar11 / (int)uVar14);
    *(short *)(puVar16 + 0x12) = (short)(iVar9 / (int)uVar14);
    FUN_80088fe8(puVar16 + 0x11,puVar16 + 1);
    iVar12 = *(short *)(piVar15[1] + 0xc) * iVar17 + *(short *)(piVar15[2] + 0xc) * iVar13;
    local_30 = iVar12 / (int)uVar14;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    iVar12 = *(short *)(piVar15[1] + 0xe) * iVar17 + *(short *)(piVar15[2] + 0xe) * iVar13;
    local_2c = iVar12 / (int)uVar14;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    iVar12 = *(short *)(piVar15[1] + 0x10) * iVar17 + *(short *)(piVar15[2] + 0x10) * iVar13;
    local_28 = iVar12 / (int)uVar14;
    if (uVar14 == 0) {
      trap(0x1c00);
    }
    if ((uVar14 == 0xffffffff) && (iVar12 == -0x80000000)) {
      trap(0x1800);
    }
    FUN_800875f8(puVar16 + 1,&local_30);
    *puVar16 = 0;
    uVar8 = 0;
    if ((undefined2 *)piVar15[3] != (undefined2 *)0x0) {
      *(undefined2 *)piVar15[3] = *(undefined2 *)(puVar16 + 6);
      *(undefined2 *)(piVar15[3] + 2) = *(undefined2 *)(puVar16 + 7);
      *(undefined2 *)(piVar15[3] + 4) = *(undefined2 *)(puVar16 + 8);
      *(undefined2 *)(piVar15[3] + 6) = *(undefined2 *)(puVar16 + 0x11);
      *(undefined2 *)(piVar15[3] + 8) = *(undefined2 *)((int)puVar16 + 0x46);
      *(undefined2 *)(piVar15[3] + 10) = *(undefined2 *)(puVar16 + 0x12);
      *(undefined2 *)(piVar15[3] + 0xc) = (undefined2)local_30;
      *(undefined2 *)(piVar15[3] + 0xe) = (undefined2)local_2c;
      *(undefined2 *)(piVar15[3] + 0x10) = (undefined2)local_28;
      uVar8 = 0;
    }
  }
  return uVar8;
}

