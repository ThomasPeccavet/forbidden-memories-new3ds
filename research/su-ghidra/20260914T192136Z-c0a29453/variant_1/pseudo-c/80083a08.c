/* Analysis pseudo-C, not buildable source. */

void FUN_80083a08(undefined1 *param_1,undefined1 *param_2,undefined4 param_3)

{
  short sVar1;
  short sVar2;
  short local_78;
  short local_76;
  undefined2 local_74;
  short local_70 [2];
  short local_6c;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  
  sVar2 = *(short *)(param_2 + 10) + DAT_800ff444;
  sVar1 = *(short *)(param_2 + 0xc) + DAT_800ff446;
  if ((*(ushort *)(param_2 + 0x16) & 1) == 0) {
    local_4c = (uint)(byte)param_2[9];
    local_48 = ((uint)(byte)param_2[9] + (int)*(short *)(param_2 + 0x10)) - 1;
  }
  else {
    local_4c = ((uint)(byte)param_2[9] + (int)*(short *)(param_2 + 0x10)) - 1;
    local_48 = (uint)(byte)param_2[9];
  }
  if ((*(ushort *)(param_2 + 0x16) & 2) == 0) {
    local_58 = (uint)(byte)param_2[8];
    local_5c = ((uint)(byte)param_2[8] + (int)*(short *)(param_2 + 0xe)) - 1;
  }
  else {
    local_58 = ((uint)(byte)param_2[8] + (int)*(short *)(param_2 + 0xe)) - 1;
    local_5c = (uint)(byte)param_2[8];
  }
  param_1[3] = *param_2;
  *param_1 = param_2[1];
  param_1[1] = param_2[2];
  param_1[2] = param_2[3];
  *(undefined2 *)(param_1 + 0x12) = *(undefined2 *)(param_2 + 4);
  *(undefined2 *)(param_1 + 10) = *(undefined2 *)(param_2 + 6);
  local_78 = *(short *)(param_2 + 0x12);
  local_76 = *(short *)(param_2 + 0x14);
  local_74 = 0;
  local_60 = local_58;
  local_54 = local_5c;
  local_50 = local_4c;
  local_44 = local_48;
  FUN_80087518(param_3,&local_78,local_70);
  *(short *)(param_1 + 4) = local_70[0] + sVar2;
  *(short *)(param_1 + 6) = local_6c + sVar1;
  param_1[8] = (undefined1)local_60;
  param_1[9] = (undefined1)local_50;
  local_78 = *(short *)(param_2 + 0x12) + *(short *)(param_2 + 0xe);
  FUN_80087518(param_3,&local_78,local_70);
  *(short *)(param_1 + 0xc) = local_70[0] + sVar2;
  *(short *)(param_1 + 0xe) = local_6c + sVar1;
  param_1[0x10] = (undefined1)local_5c;
  param_1[0x11] = (undefined1)local_4c;
  local_76 = *(short *)(param_2 + 0x14) + *(short *)(param_2 + 0x10);
  FUN_80087518(param_3,&local_78,local_70);
  *(short *)(param_1 + 0x1c) = local_70[0] + sVar2;
  *(short *)(param_1 + 0x1e) = local_6c + sVar1;
  param_1[0x20] = (undefined1)local_54;
  param_1[0x21] = (undefined1)local_44;
  local_78 = *(short *)(param_2 + 0x12);
  FUN_80087518(param_3,&local_78,local_70);
  *(short *)(param_1 + 0x14) = local_70[0] + sVar2;
  *(short *)(param_1 + 0x16) = local_6c + sVar1;
  param_1[0x18] = (undefined1)local_58;
  param_1[0x19] = (undefined1)local_48;
  return;
}

