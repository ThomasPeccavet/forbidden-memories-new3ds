/* Analysis pseudo-C, not buildable source. */

void FUN_8004ec04(int param_1,int param_2,int param_3,uint param_4,short *param_5)

{
  short *psVar1;
  int iVar2;
  undefined4 **ppuVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  undefined4 *local_60 [5];
  undefined4 *local_4c;
  undefined4 *local_48;
  undefined4 *local_40 [2];
  int local_38;
  int local_34;
  short local_30 [12];
  
  uVar5 = (uint)DAT_8009c310;
  iVar2 = (param_1 + 0x7ff0c138) * -0x33333333 >> 3;
  if (uVar5 == 0) {
    trap(0x1c00);
  }
  if ((uVar5 == 0xffffffff) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  if (uVar5 == 0) {
    trap(0x1c00);
  }
  if ((uVar5 == 0xffffffff) && (iVar2 + 1 == -0x80000000)) {
    trap(0x1800);
  }
  if (uVar5 == 0) {
    trap(0x1c00);
  }
  if ((uVar5 == 0xffffffff) && (iVar2 + 2 == -0x80000000)) {
    trap(0x1800);
  }
  iVar6 = 1;
  local_60[0] = &DAT_800f3ec8 + (iVar2 % (int)uVar5) * 10;
  local_60[1] = &DAT_800f3ec8 + ((iVar2 + 1) % (int)uVar5) * 10;
  local_60[2] = &DAT_800f3ec8 + ((iVar2 + 2) % (int)uVar5) * 10;
  local_60[4] = local_60[0];
  local_4c = local_60[1];
  local_48 = local_60[2];
  FUN_8008f548(local_40,0,0x10);
  ppuVar3 = local_60;
  local_40[0] = (undefined4 *)(&DAT_800f3ea8 + param_2 * 4);
  do {
    ppuVar3 = ppuVar3 + 1;
    if (*(short *)((int)*ppuVar3 + param_2 * 8 + 6) != 1) break;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 3);
  iVar2 = iVar6 + -1;
  if (iVar6 < 3) {
    ppuVar3 = local_60 + iVar6;
    do {
      iVar6 = iVar6 + 1;
      *ppuVar3 = local_60[iVar2];
      ppuVar3 = ppuVar3 + 1;
    } while (iVar6 < 3);
  }
  iVar2 = 1;
  iVar6 = 0;
  do {
    iVar4 = iVar2;
    local_40[iVar4] = local_60[iVar6] + param_2 * 2;
    iVar2 = iVar4 + 1;
    iVar6 = iVar4;
  } while (iVar4 < 3);
  if (param_4 == 0) {
    iVar6 = 1;
    ppuVar3 = local_60;
    iVar2 = 0;
    param_4 = (uint)*(ushort *)((int)local_60[0] + 0x22);
    do {
      ppuVar3 = ppuVar3 + 1;
      if (*(undefined4 **)((int)local_60 + iVar2) != *ppuVar3) {
        param_4 = param_4 + *(ushort *)((int)*ppuVar3 + 0x22);
      }
      iVar6 = iVar6 + 1;
      iVar2 = iVar2 + 4;
    } while (iVar6 < 3);
  }
  else {
    uVar5 = (uint)DAT_8009c310;
    iVar2 = ((param_1 + 0x7ff0c138) * -0x33333333 >> 3) + uVar5 + -1;
    if (uVar5 == 0) {
      trap(0x1c00);
    }
    if ((uVar5 == 0xffffffff) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
    if (*(short *)((int)(&DAT_800f3ec8 + (iVar2 % (int)uVar5) * 10 + param_2 * 2) + 6) == 1) {
      local_40[0] = &DAT_800f3ec8 + (iVar2 % (int)uVar5) * 10 + param_2 * 2;
    }
  }
  iVar2 = 0;
  psVar7 = local_30;
  do {
    iVar6 = iVar2 * 2;
    FUN_8004fbd4((int)*(short *)(iVar6 + (int)local_40[0]),(int)*(short *)(iVar6 + (int)local_40[1])
                 ,(int)*(short *)(iVar6 + local_38),(int)*(short *)(iVar6 + local_34),psVar7,2);
    if (param_4 == 0) {
      trap(0x1c00);
    }
    if ((param_4 == 0xffffffff) && (*psVar7 * param_3 == -0x80000000)) {
      trap(0x1800);
    }
    iVar6 = ((*psVar7 * param_3) / (int)param_4 + (int)psVar7[1]) * param_3;
    if (param_4 == 0) {
      trap(0x1c00);
    }
    if ((param_4 == 0xffffffff) && (iVar6 == -0x80000000)) {
      trap(0x1800);
    }
    iVar6 = (iVar6 / (int)param_4 + (int)psVar7[2]) * param_3;
    if (param_4 == 0) {
      trap(0x1c00);
    }
    if ((param_4 == 0xffffffff) && (iVar6 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = iVar2 + 1;
    psVar1 = psVar7 + 3;
    psVar7 = psVar7 + 4;
    *param_5 = *psVar1 + (short)(iVar6 / (int)param_4);
    param_5 = param_5 + 1;
  } while (iVar2 < 3);
  return;
}

