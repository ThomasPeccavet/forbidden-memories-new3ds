/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008ce88(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_800ff6d0 == 0) {
    iVar2 = FUN_8008d818();
    if (iVar2 == 0) {
      uVar1 = 0;
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

