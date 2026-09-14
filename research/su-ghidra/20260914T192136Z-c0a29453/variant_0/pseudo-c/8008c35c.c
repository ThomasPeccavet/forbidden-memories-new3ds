/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008c35c(undefined4 param_1,uint param_2,uint param_3)

{
  char *pcVar1;
  
  if (DAT_800ff6e4 < 0) {
    pcVar1 = s_Access_Denied____file_not_open__80012490;
  }
  else if (DAT_800ff6d0 < 1) {
    if ((param_3 & 0x7f) == 0) {
      if ((param_2 & 0x7f) == 0) {
        DAT_800ff6d0 = 6;
        DAT_800ff6d4 = 0;
        DAT_800ff6d8 = 0;
        DAT_800ff6e8 = param_2;
        DAT_800ff6ec = param_3;
        DAT_800ff6f0 = param_1;
        FUN_8008d068(FUN_8008c414);
        return 1;
      }
      pcVar1 = s_Access_Denied____invalid_offset_v_800124e0;
    }
    else {
      pcVar1 = s_Access_Denied____invalid_data_si_800124b4;
    }
  }
  else {
    pcVar1 = s_Access_Denied____event_multiple_o_8001236c;
  }
  FUN_8008fa78(pcVar1);
  return 0;
}

