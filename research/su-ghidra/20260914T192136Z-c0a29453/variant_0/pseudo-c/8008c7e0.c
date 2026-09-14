/* Analysis pseudo-C, not buildable source. */

undefined4
FUN_8008c7e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,uint param_5)

{
  char *pcVar1;
  
  if (DAT_800ff6d0 < 1) {
    if (DAT_800ff6e4 < 0) {
      if ((param_5 & 0x7f) == 0) {
        if ((param_4 & 0x7f) == 0) {
          FUN_8008cffc(param_1,&DAT_800ff6f4);
          FUN_8008f748(&DAT_800ff6f4,param_2);
          DAT_800ff6d0 = 4;
          DAT_800ff6d4 = 0;
          DAT_800ff6d8 = 0;
          DAT_800ff6ec = param_5;
          DAT_800ff6e0 = param_1;
          DAT_800ff6e8 = param_4;
          DAT_800ff6f0 = param_3;
          FUN_8008d068(FUN_8008c8f8);
          return 1;
        }
        pcVar1 = s_Access_Denied____invalid_offset_v_800124e0;
      }
      else {
        pcVar1 = s_Access_Denied____invalid_data_si_800124b4;
      }
    }
    else {
      pcVar1 = s_Access_Denied____file_already_op_80012468;
    }
  }
  else {
    pcVar1 = s_Access_Denied____system_busy_80012510;
  }
  FUN_8008fa78(pcVar1);
  return 0;
}

