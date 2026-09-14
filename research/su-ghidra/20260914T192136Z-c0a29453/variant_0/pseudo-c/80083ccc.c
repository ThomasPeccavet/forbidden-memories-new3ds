/* Analysis pseudo-C, not buildable source. */

void FUN_80083ccc(undefined1 *param_1,undefined1 *param_2)

{
  undefined2 uVar1;
  short sVar2;
  uint *puVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  uint local_40;
  int local_3c;
  uint local_38;
  int local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  int local_24;
  
  puVar3 = &local_40;
  sVar6 = *(short *)(param_2 + 10) + *(short *)(param_2 + 0x12) + DAT_800ff444;
  sVar4 = *(short *)(param_2 + 0xc) + *(short *)(param_2 + 0x14) + DAT_800ff446;
  if ((*(ushort *)(param_2 + 0x16) & 1) == 0) {
    local_2c = (uint)(byte)param_2[9];
    local_30 = (uint)(byte)param_2[9];
    local_24 = (uint)(byte)param_2[9] + (int)*(short *)(param_2 + 0x10);
  }
  else {
    local_2c = ((uint)(byte)param_2[9] + (int)*(short *)(param_2 + 0x10)) - 1;
    local_30 = local_2c;
    local_24 = (byte)param_2[9] - 1;
  }
  local_28 = local_24;
  if ((*(ushort *)(param_2 + 0x16) & 2) == 0) {
    local_38 = (uint)(byte)param_2[8];
    local_40 = (uint)(byte)param_2[8];
    local_34 = (uint)(byte)param_2[8] + (int)*(short *)(param_2 + 0xe);
  }
  else {
    local_38 = ((uint)(byte)param_2[8] + (int)*(short *)(param_2 + 0xe)) - 1;
    local_40 = local_38;
    local_34 = (byte)param_2[8] - 1;
  }
  local_3c = local_34;
  iVar5 = 0;
  local_40 = local_38;
  local_30 = local_2c;
  do {
    if ((int)*puVar3 < 0) {
      *puVar3 = 0;
    }
    if ((int)puVar3[4] < 0) {
      puVar3[4] = 0;
    }
    if (0xff < (int)*puVar3) {
      *puVar3 = 0xff;
    }
    if (0xff < (int)puVar3[4]) {
      puVar3[4] = 0xff;
    }
    iVar5 = iVar5 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar5 < 4);
  param_1[3] = *param_2;
  *param_1 = param_2[1];
  param_1[1] = param_2[2];
  param_1[2] = param_2[3];
  *(undefined2 *)(param_1 + 0x12) = *(undefined2 *)(param_2 + 4);
  uVar1 = *(undefined2 *)(param_2 + 6);
  *(short *)(param_1 + 4) = sVar6;
  *(short *)(param_1 + 6) = sVar4;
  *(undefined2 *)(param_1 + 10) = uVar1;
  param_1[8] = (undefined1)local_40;
  param_1[9] = (undefined1)local_30;
  sVar2 = *(short *)(param_2 + 0xe);
  *(short *)(param_1 + 0xe) = sVar4;
  *(short *)(param_1 + 0xc) = sVar2 + sVar6;
  param_1[0x10] = (undefined1)local_3c;
  *(short *)(param_1 + 0x14) = sVar6;
  param_1[0x11] = (undefined1)local_2c;
  *(short *)(param_1 + 0x16) = *(short *)(param_2 + 0x10) + sVar4;
  param_1[0x18] = (undefined1)local_38;
  param_1[0x19] = (undefined1)local_28;
  *(short *)(param_1 + 0x1c) = *(short *)(param_2 + 0xe) + sVar6;
  *(short *)(param_1 + 0x1e) = *(short *)(param_2 + 0x10) + sVar4;
  param_1[0x20] = (undefined1)local_34;
  param_1[0x21] = (undefined1)local_24;
  return;
}

