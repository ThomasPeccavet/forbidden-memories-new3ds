/* Analysis pseudo-C, not buildable source. */

void FUN_8007e6c0(char param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((DAT_80094e64 != 0) && (DAT_80094e68 != 0)) {
    if (param_1 == '\x02') {
      iVar1 = FUN_8007c058();
      if (iVar1 == 0) {
        FUN_8007e778();
      }
    }
    else {
      FUN_8007edf8(DAT_80094e5c);
      FUN_8007ee18(DAT_80094e60);
      DAT_80094e68 = 0;
      if (DAT_80094e50 != (code *)0x0) {
        (*DAT_80094e50)(param_1,param_2,0);
      }
    }
  }
  return;
}

