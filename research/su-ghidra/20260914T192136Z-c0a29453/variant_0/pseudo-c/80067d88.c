/* Analysis pseudo-C, not buildable source. */

int * FUN_80067d88(int *param_1,byte param_2,undefined1 param_3,undefined1 param_4,byte param_5)

{
  undefined2 uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte local_10 [8];
  int local_8;
  undefined4 local_4;
  
  iVar7 = 0;
  iVar6 = 0;
  local_10[0] = param_2;
  local_10[1] = param_3;
  local_10[2] = param_4;
  pbVar2 = local_10 + 1;
  iVar5 = 1;
  do {
    if (local_10[iVar7] < *pbVar2) {
      iVar7 = iVar5;
    }
    if (*pbVar2 < local_10[iVar6]) {
      iVar6 = iVar5;
    }
    iVar3 = iVar5 + 1;
    pbVar2 = local_10 + iVar5 + 1;
    iVar5 = iVar3;
  } while (iVar3 < 3);
  uVar4 = (uint)param_5 * 2;
  iVar5 = (uint)local_10[iVar7] + (uint)local_10[iVar6];
  uVar8 = (uint)(iVar5 * 0x1000) / uVar4;
  if (param_5 == 0) {
    trap(0x1c00);
  }
  if ((uVar4 == 0xffffffff) && (iVar5 == 0x80000)) {
    trap(0x1800);
  }
  local_8 = 0;
  iVar6 = (uint)local_10[iVar7] - (uint)local_10[iVar6];
  local_4 = uVar8 & 0xffff;
  if (iVar6 != 0) {
    iVar3 = iVar6 * 0x1000;
    if ((uVar8 & 0xffff) < 0x801) {
      if (iVar5 == 0) {
        trap(0x1c00);
      }
      if ((iVar5 == -1) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
      uVar1 = (undefined2)(iVar3 / iVar5);
    }
    else {
      iVar5 = uVar4 - iVar5;
      if (iVar5 == 0) {
        trap(0x1c00);
      }
      if ((iVar5 == -1) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
      uVar1 = (undefined2)(iVar3 / iVar5);
    }
    local_4 = CONCAT22(uVar1,(short)uVar8);
    iVar5 = ((uint)local_10[(iVar7 + 1) % 3] - (uint)local_10[(iVar7 + 2) % 3]) * 0x1000;
    if (iVar6 == 0) {
      trap(0x1c00);
    }
    if ((iVar6 == -1) && (iVar5 == -0x80000000)) {
      trap(0x1800);
    }
    local_8 = iVar7 * 0x2000 + iVar5 / iVar6;
    if (local_8 < 0) {
      local_8 = local_8 + 0x6000;
    }
  }
  *param_1 = local_8;
  param_1[1] = local_4;
  return param_1;
}

