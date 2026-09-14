/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008cd8c(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_38 [32];
  
  if (DAT_800ff6d0 == 0) {
    FUN_8008cffc(param_1,auStack_38);
    FUN_8008f748(auStack_38,param_2);
    DAT_800ff6dc = DAT_800ff6dc | 1 << (param_1 & 0x1f);
    iVar2 = FUN_8008dbe8(param_1,param_2,param_3);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else if (iVar2 == -1) {
      uVar1 = 7;
    }
    else if (iVar2 == -2) {
      uVar1 = 4;
    }
    else if (iVar2 == -3) {
      uVar1 = 6;
    }
    else {
      uVar1 = 2;
      if (iVar2 != 4) {
        uVar1 = FUN_8008cefc();
      }
    }
  }
  else {
    FUN_8008fa78(s_Access_Denied____system_busy_80012510);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

