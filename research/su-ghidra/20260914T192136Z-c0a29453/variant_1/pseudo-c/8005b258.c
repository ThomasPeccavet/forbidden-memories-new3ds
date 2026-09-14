/* Analysis pseudo-C, not buildable source. */

void FUN_8005b258(int param_1,uint param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined2 local_84;
  undefined2 local_82;
  undefined2 local_80;
  undefined4 local_7c;
  short local_78;
  short local_76;
  short local_74;
  undefined1 auStack_70 [32];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [32];
  undefined1 auStack_20 [8];
  
  param_1 = param_1 * 0xe20;
  if ((int)(uint)(byte)(&DAT_800f4f8f)[param_1] < (int)param_2) {
    param_2 = (uint)(byte)(&DAT_800f4f90)[param_1];
  }
  FUN_8008a428(*(int *)(&DAT_800f4e8c + param_1) + param_2 * 0x50,auStack_70);
  FUN_80085558(auStack_70);
  FUN_80089c48(param_3,&local_78,auStack_20);
  local_80 = 0;
  local_82 = 0;
  local_84 = 0;
  FUN_80088dd8(&local_84,&local_c4);
  local_b0 = (int)local_78;
  local_ac = (int)local_76;
  local_a8 = (int)local_74;
  local_c8 = 1;
  local_a4 = local_c4;
  local_a0 = local_c0;
  local_9c = local_bc;
  local_98 = local_b8;
  local_94 = local_b4;
  local_7c = 0;
  local_90 = local_b0;
  local_8c = local_ac;
  local_88 = local_a8;
  FUN_8008f548(&local_48,0,8);
  local_48 = CONCAT22(0x1000 - DAT_8009c7fa,(undefined2)local_48);
  local_44 = CONCAT22(local_44._2_2_,DAT_8009c7fc);
  local_50 = local_48;
  local_4c = local_44;
  *param_4 = 0;
  *(short *)(param_4 + 0x11) = 0x1000 - *(short *)(DAT_800f4e90 + 0x44);
  *(short *)((int)param_4 + 0x46) = 0x1000 - *(short *)(DAT_800f4e90 + 0x46);
  *(short *)(param_4 + 0x12) = 0x1000 - *(short *)(DAT_800f4e90 + 0x48);
  FUN_80088948(param_4 + 0x11,param_4 + 1);
  FUN_80088dd8(&local_50,auStack_40);
  FUN_800872f8(param_4 + 1,auStack_40);
  param_4[8] = 0;
  param_4[7] = 0;
  param_4[6] = 0;
  param_4[0x13] = &local_c8;
  return;
}

