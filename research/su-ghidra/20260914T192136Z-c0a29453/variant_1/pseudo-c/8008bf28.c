/* Analysis pseudo-C, not buildable source. */

int FUN_8008bf28(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int local_28 [2];
  
  iVar2 = 0;
  if (DAT_800ff6e4 < 0) {
    FUN_8008cffc(param_1,&DAT_800ff6f4);
    FUN_8008f748(&DAT_800ff6f4,param_2);
    DAT_800ff6e0 = param_1;
    do {
      iVar1 = FUN_80073e18(&DAT_800ff6f4,1);
      if (-1 < iVar1) {
        FUN_80073e58(iVar1);
        FUN_8008d4e8();
        DAT_800ff6e4 = FUN_80073e18(&DAT_800ff6f4,param_3 | 0x8000);
        return 0;
      }
      DAT_800ff728 = FUN_8008cc5c(0);
      if (DAT_800ff6d0 < 1) {
        DAT_800ff6d0 = 2;
        DAT_800ff6d4 = 0;
        DAT_800ff6d8 = 0;
        DAT_800ff6e0 = param_1;
        FUN_8008d068(FUN_8008bc80);
      }
      else {
        FUN_8008fa78(s_Access_Denied____event_multiple_o_8001236c);
      }
      FUN_8008cc70(0,0,local_28);
      FUN_8008cc5c(DAT_800ff728);
    } while ((local_28[0] == 3) || ((local_28[0] == 2 && (iVar2 = iVar2 + 1, iVar2 < 5))));
    if (local_28[0] == 0) {
      local_28[0] = 5;
    }
  }
  else {
    FUN_8008fa78(s_Access_Denied____file_already_op_80012468);
    local_28[0] = -1;
  }
  return local_28[0];
}

