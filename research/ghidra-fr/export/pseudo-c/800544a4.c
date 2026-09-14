/* Analysis pseudo-C, not buildable source. */

int FUN_800544a4(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  undefined *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int local_80 [18];
  int local_38;
  undefined4 *local_30;
  undefined *local_2c;
  
  iVar2 = FUN_800866f8(DAT_8009c7fa + 0x800);
  iVar2 = iVar2 * param_2;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xfff;
  }
  iVar3 = FUN_80086628(DAT_8009c7fa + 0x800);
  iVar3 = iVar3 * param_2;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xfff;
  }
  local_80[0] = ((int)((uint)DAT_800f4f46 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f4f46 << 0x10) >> 0x1f) >> 1;
  if (local_80[0] < param_2) {
    local_80[0] = param_2;
  }
  local_80[1] = ((int)((uint)DAT_800f5d66 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f5d66 << 0x10) >> 0x1f) >> 1;
  if (local_80[1] < param_2) {
    local_80[1] = param_2;
  }
  local_80[2] = ((int)((uint)DAT_800f4f40 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f4f40 << 0x10) >> 0x1f) >> 1;
  if (local_80[2] < param_2) {
    local_80[2] = param_2;
  }
  local_80[3] = ((int)((uint)DAT_800f5d60 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f5d60 << 0x10) >> 0x1f) >> 1;
  if (local_80[3] < param_2) {
    local_80[3] = param_2;
  }
  local_80[4] = ((int)((uint)DAT_800f4f42 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f4f42 << 0x10) >> 0x1f) >> 1;
  if (local_80[4] < param_2) {
    local_80[4] = param_2;
  }
  local_80[5] = ((int)((uint)DAT_800f5d62 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f5d62 << 0x10) >> 0x1f) >> 1;
  if (local_80[5] < param_2) {
    local_80[5] = param_2;
  }
  local_80[6] = ((int)((uint)DAT_800f4f44 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f4f44 << 0x10) >> 0x1f) >> 1;
  if (local_80[6] < param_2) {
    local_80[6] = param_2;
  }
  local_80[7] = ((int)((uint)DAT_800f5d64 << 0x10) >> 0x10) -
                ((int)((uint)DAT_800f5d64 << 0x10) >> 0x1f) >> 1;
  if (local_80[7] < param_2) {
    local_80[7] = param_2;
  }
  local_80[9] = DAT_800f6c28 + (iVar2 >> 0xc);
  local_80[8] = local_80[9] - DAT_800f4f48;
  local_80[9] = local_80[9] - DAT_800f5d68;
  local_80[10] = DAT_800f6c2c - DAT_800f4f4a;
  local_80[0xb] = DAT_800f6c2c - DAT_800f5d6a;
  local_80[0xd] = DAT_800f6c30 + (iVar3 >> 0xc);
  local_80[0xc] = local_80[0xd] - DAT_800f4f4c;
  local_80[0xd] = local_80[0xd] - DAT_800f5d6c;
  local_80[0xe] = local_80[0xc];
  local_80[0xf] = local_80[0xd];
  local_80[0x10] = FUN_80086dd8(local_80[8] * local_80[8] + local_80[0xc] * local_80[0xc]);
  local_80[0x11] = FUN_80086dd8(local_80[9] * local_80[9] + local_80[0xd] * local_80[0xd]);
  local_38 = 0;
  local_80[0xe] = local_80[0x10];
  local_80[0xf] = local_80[0x11];
  iVar2 = 0;
  if ((DAT_800f4f97 == '\0') || ((1 < DAT_800f4f38._3_1_ && ((DAT_800f4f38 & 0xffffff) == 0)))) {
    local_80[0xe] = 0xffffffff;
  }
  if ((DAT_800f5db7 == '\0') || ((1 < DAT_800f5d58._3_1_ && ((DAT_800f5d58 & 0xffffff) == 0)))) {
    local_80[0xf] = 0xffffffff;
  }
  iVar16 = 0;
  puVar12 = &DAT_800f0000;
  puVar11 = &DAT_800f6c28;
  iVar3 = 0;
  do {
    piVar10 = (int *)((int)local_80 + iVar3 + 0x18);
    iVar15 = *piVar10;
    iVar9 = *(int *)((int)local_80 + iVar3 + 8);
    if (iVar15 < iVar9) {
      iVar15 = iVar9;
    }
    if (iVar15 < *(int *)((int)local_80 + iVar3)) {
      iVar15 = *(int *)((int)local_80 + iVar3);
    }
    iVar4 = *(int *)((int)local_80 + iVar3 + 0x28);
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    if (iVar4 <= *(int *)((int)local_80 + iVar3 + 0x10)) {
      iVar4 = *(int *)((int)local_80 + iVar3 + 0x38);
      if ((-1 < iVar4) && (iVar4 < iVar15)) {
        if (iVar2 == 0) {
          iVar2 = iVar15;
          if (param_1 != 0) {
            iVar5 = (iVar15 - iVar4) * 0x1000;
            iVar4 = iVar5 / iVar15;
            if (iVar15 == 0) {
              trap(0x1c00);
            }
            if ((iVar15 == -1) && (iVar5 == -0x80000000)) {
              trap(0x1800);
            }
            iVar9 = iVar9 * iVar4;
            if (iVar9 < 0) {
              iVar9 = iVar9 + 0xfff;
            }
            iVar9 = iVar9 >> 0xc;
            if (*(int *)((int)local_80 + iVar3 + 0x20) < 1) {
              iVar9 = -iVar9;
            }
            iVar4 = *piVar10 * iVar4;
            if (iVar4 < 0) {
              iVar4 = iVar4 + 0xfff;
            }
            iVar4 = iVar4 >> 0xc;
            if (*(int *)((int)local_80 + iVar3 + 0x30) < 1) {
              iVar4 = -iVar4;
            }
            iVar8 = puVar11[3];
            iVar5 = puVar11[2];
            iVar6 = puVar11[5];
            iVar14 = iVar6 - iVar5;
            iVar3 = *(int *)(puVar12 + 0x6c28);
            iVar13 = iVar3 - iVar8;
            local_30 = puVar11;
            local_2c = puVar12;
            iVar15 = FUN_80086dd8(iVar14 * iVar14 + iVar13 * iVar13);
            iVar7 = 0;
            if (iVar15 != 0) {
              iVar3 = (iVar3 + iVar9) * iVar14 + (iVar5 + iVar4) * iVar13 +
                      (iVar8 * iVar5 - iVar3 * iVar6);
              iVar7 = iVar3 / iVar15;
              if (iVar15 == 0) {
                trap(0x1c00);
              }
              if ((iVar15 == -1) && (iVar3 == -0x80000000)) {
                trap(0x1800);
              }
            }
            if (DAT_8009c328 == '\0') {
              if (iVar7 < 0) {
                DAT_8009c329 = 0xff;
              }
              else {
                DAT_8009c329 = 1;
              }
              cVar1 = '\x1e';
LAB_80054ac4:
              DAT_8009c328 = cVar1;
            }
            else {
              cVar1 = DAT_8009c328 + -1;
              if (DAT_8009c328 != -1) goto LAB_80054ac4;
            }
            iVar3 = local_30[2];
            *(int *)(local_2c + 0x6c28) = *(int *)(local_2c + 0x6c28) + iVar9;
            local_30[2] = iVar3 + iVar4;
            puVar11 = local_30;
            puVar12 = local_2c;
          }
        }
        else {
          local_38 = local_38 + 1;
        }
      }
    }
    iVar16 = iVar16 + 1;
    iVar3 = iVar16 * 4;
    if (1 < iVar16) {
      if ((param_1 != 0) && (iVar2 != 0)) {
        FUN_8005b0bc(0);
      }
      if (((local_38 != 0) && (param_1 != 0)) && (param_3 + 1 < 3)) {
        FUN_800544a4(param_1,param_2,param_3 + 1);
      }
      return iVar2;
    }
  } while( true );
}

