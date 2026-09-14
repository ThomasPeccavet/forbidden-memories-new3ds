/* Analysis pseudo-C, not buildable source. */

bool FUN_8008bc18(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = 0 < DAT_800ff6d0;
  if (bVar1) {
    FUN_8008fa78(s_Access_Denied____event_multiple_o_8001236c);
  }
  else {
    DAT_800ff6d0 = 2;
    DAT_800ff6d4 = 0;
    DAT_800ff6d8 = 0;
    DAT_800ff6e0 = param_1;
    FUN_8008d068(FUN_8008bc80);
  }
  return !bVar1;
}

