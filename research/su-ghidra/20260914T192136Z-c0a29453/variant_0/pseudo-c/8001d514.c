/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8001d514(int param_1)

{
  int iVar1;
  
  if (DAT_8009c57e == 0) {
    iVar1 = FUN_80024144(param_1,(int)DAT_8009c590);
    if (iVar1 != 0) {
      return 1;
    }
    if (DAT_8009c510 != *(char *)(param_1 + 0x10)) {
      if (*(char *)(param_1 + 0x10) <= DAT_8009c510) {
        DAT_8009c590 = 1;
        return 1;
      }
      DAT_8009c590 = 3;
      return 1;
    }
    if (DAT_8009c50f == *(char *)(param_1 + 0xf)) {
      DAT_8009c590 = 0xff;
      return 0;
    }
    DAT_8009c590 = 2;
    if (*(char *)(param_1 + 0xf) <= DAT_8009c50f) {
      DAT_8009c590 = 0;
      return 1;
    }
  }
  else {
    DAT_8009c590 = 0xff;
  }
  return 1;
}

