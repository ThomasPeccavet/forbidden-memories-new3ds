/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80085768(int param_1,int *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  
  uVar5 = DAT_800ff48c;
  uVar4 = DAT_800ff488;
  uVar3 = DAT_800ff484;
  uVar2 = DAT_800ff480;
  uVar1 = DAT_800ff474;
  uVar8 = (uint)*(byte *)(param_2 + 3);
  uVar9 = (uint)*(byte *)((int)param_2 + 0xd);
  uVar10 = (uint)*(byte *)((int)param_2 + 0xe);
  local_80 = DAT_800ff470;
  local_7c = DAT_800ff474;
  local_78 = DAT_800ff478;
  local_74 = DAT_800ff47c;
  local_70 = DAT_800ff480;
  FUN_80085c84(&local_60);
  iVar6 = FUN_80086dd8(*param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2]);
  uVar7 = 0xffffffff;
  if (iVar6 != 0) {
    if (param_1 == 1) {
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (*param_2 * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      local_7c = CONCAT22((short)((*param_2 * -0x1000) / iVar6),(short)uVar1);
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (param_2[1] * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (param_2[2] * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      local_5e = (undefined2)((uVar8 * 0x1000) / 0xff);
      local_58 = (undefined2)((uVar9 * 0x1000) / 0xff);
      local_52 = (undefined2)((uVar10 * 0x1000) / 0xff);
      local_78 = CONCAT22((short)((param_2[2] * -0x1000) / iVar6),
                          (short)((param_2[1] * -0x1000) / iVar6));
    }
    else if (param_1 < 2) {
      if (param_1 == 0) {
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (*param_2 * -0x1000 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (param_2[1] * -0x1000 == -0x80000000)) {
          trap(0x1800);
        }
        local_80 = CONCAT22((short)((param_2[1] * -0x1000) / iVar6),
                            (short)((*param_2 * -0x1000) / iVar6));
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (param_2[2] * -0x1000 == -0x80000000)) {
          trap(0x1800);
        }
        local_60 = (undefined2)((uVar8 * 0x1000) / 0xff);
        local_5a = (undefined2)((uVar9 * 0x1000) / 0xff);
        local_54 = (undefined2)((uVar10 * 0x1000) / 0xff);
        local_7c = CONCAT22((short)((uint)uVar1 >> 0x10),(short)((param_2[2] * -0x1000) / iVar6));
      }
    }
    else if (param_1 == 2) {
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (*param_2 * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (param_2[1] * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      local_74 = CONCAT22((short)((param_2[1] * -0x1000) / iVar6),
                          (short)((*param_2 * -0x1000) / iVar6));
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (param_2[2] * -0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      local_5c = (undefined2)((uVar8 * 0x1000) / 0xff);
      local_56 = (undefined2)((uVar9 * 0x1000) / 0xff);
      local_50 = (undefined2)((uVar10 * 0x1000) / 0xff);
      local_70 = CONCAT22((short)((uint)uVar2 >> 0x10),(short)((param_2[2] * -0x1000) / iVar6));
    }
    DAT_800ff470 = local_80;
    DAT_800ff474 = local_7c;
    DAT_800ff478 = local_78;
    DAT_800ff47c = local_74;
    DAT_800ff480 = local_70;
    DAT_800ff484 = uVar3;
    DAT_800ff488 = uVar4;
    DAT_800ff48c = uVar5;
    FUN_80085c20(&local_60);
    uVar7 = 0;
  }
  return uVar7;
}

