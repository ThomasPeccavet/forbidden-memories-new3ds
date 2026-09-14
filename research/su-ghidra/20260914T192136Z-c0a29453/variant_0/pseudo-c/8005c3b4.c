/* Analysis pseudo-C, not buildable source. */

void FUN_8005c3b4(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [32];
  
  FUN_8008f548(&local_40,0,8);
  local_3c = CONCAT22(local_3c._2_2_,DAT_8009c7fc);
  local_40 = CONCAT22(0x1000 - DAT_8009c7fa,(undefined2)local_40);
  local_48 = local_40;
  local_44 = local_3c;
  *param_3 = 0;
  *(short *)(param_3 + 0x11) = 0x1000 - *(short *)((&DAT_800f4e90)[param_1 * 0x388] + 0x44);
  *(short *)((int)param_3 + 0x46) = 0x1000 - *(short *)((&DAT_800f4e90)[param_1 * 0x388] + 0x46);
  *(short *)(param_3 + 0x12) = 0x1000 - *(short *)((&DAT_800f4e90)[param_1 * 0x388] + 0x48);
  FUN_80088948(param_3 + 0x11,param_3 + 1);
  FUN_80088dd8(&local_48,auStack_38);
  FUN_800872f8(param_3 + 1,auStack_38);
  param_3[8] = 0;
  param_3[7] = 0;
  param_3[6] = 0;
  param_3[0x13] = param_2;
  return;
}

