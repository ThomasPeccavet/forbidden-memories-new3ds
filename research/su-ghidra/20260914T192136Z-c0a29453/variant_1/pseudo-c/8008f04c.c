/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008f04c(int param_1,int *param_2,undefined4 *param_3)

{
  if ((DAT_800ffbe0 == 0) || (DAT_8009b1e8 == 1)) {
    if (param_2 != (int *)0x0) {
      *param_2 = 0;
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if (param_1 == 0) {
    do {
    } while (DAT_8009b1e8 < 5);
  }
  if (param_2 != (int *)0x0) {
    *param_2 = DAT_800ffbe0;
  }
  if (param_3 == (undefined4 *)0x0) {
    if (DAT_8009b1e8 == 2) {
      return 0;
    }
    if (DAT_8009b1e8 != 4) {
      DAT_800ffbe0 = 0;
      return 1;
    }
    return 0;
  }
  if (DAT_8009b1e8 == 4) {
LAB_8008f118:
    *param_3 = 0;
    return 0;
  }
  if (DAT_8009b1e8 < 5) {
    if (DAT_8009b1e8 == 2) goto LAB_8008f118;
LAB_8008f148:
    if (DAT_800ffab1 == '\b') {
      *param_3 = 3;
    }
    else {
      *param_3 = 0;
    }
  }
  else {
    if (DAT_8009b1e8 == 0x11) {
      if (DAT_8009b1fc == 1) {
        *param_3 = 1;
        DAT_800ffbe0 = 0;
        return 1;
      }
    }
    else if (DAT_8009b1e8 != 0x21) goto LAB_8008f148;
    *param_3 = 2;
  }
  DAT_800ffbe0 = 0;
  return 1;
}

