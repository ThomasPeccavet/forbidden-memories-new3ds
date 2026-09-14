/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008bc80(int *param_1)

{
  int iVar1;
  
  switch(*param_1) {
  case 0:
    DAT_800ff6ac = 0;
    DAT_800ff6b0 = 0;
    DAT_800ff6a8 = 0;
    DAT_800ff6b8 = 0;
    DAT_800ff6b4 = 0;
    *param_1 = *param_1 + 1;
  case 1:
    FUN_8008d068(FUN_8008b8fc);
    iVar1 = 10;
    break;
  default:
    goto switchD_8008bcb8_caseD_2;
  case 10:
    if (DAT_800ff6d4 == 1) {
      return 1;
    }
    if (DAT_800ff6d4 < 2) {
      if (DAT_800ff6d4 != 0) {
        return 1;
      }
      iVar1 = 0x1e;
    }
    else {
      if (DAT_800ff6d4 != 3) {
        return 1;
      }
      DAT_800ff6b8 = 1;
      DAT_800ff6dc = DAT_800ff6dc | 1 << (DAT_800ff6e0 & 0x1f);
      FUN_8008d4e8();
      FUN_8008b328(DAT_800ff6e0);
      iVar1 = 0x15;
    }
    break;
  case 0x15:
    iVar1 = FUN_8008d7dc();
    if (iVar1 == 0) {
      return 0;
    }
    FUN_8008d6c8();
    *param_1 = 0x1e;
  case 0x1e:
    FUN_8008d4e8();
    FUN_8008b2c8(DAT_800ff6e0);
    iVar1 = *param_1 + 1;
    break;
  case 0x1f:
    iVar1 = FUN_8008d7a0();
    if (iVar1 == 0) {
      return 0;
    }
    DAT_800ff6b4 = FUN_8008d5f0();
    if (DAT_800ff6b4 == 1) {
      DAT_800ff6ac = DAT_800ff6ac + 1;
      iVar1 = 0x1e;
      if (0x10 < DAT_800ff6ac) goto LAB_8008bea0;
    }
    else {
      if (DAT_800ff6b4 < 2) {
        if (DAT_800ff6b4 == 0) {
          if (DAT_800ff6b8 == 0) {
            DAT_800ff6b4 = 0;
            DAT_800ff6d4 = 0;
            return 1;
          }
          DAT_800ff6b4 = 0;
          DAT_800ff6d4 = 3;
          return 1;
        }
LAB_8008bea0:
        DAT_800ff6d4 = FUN_8008cefc(DAT_800ff6b4);
        return 1;
      }
      if (DAT_800ff6b4 == 2) {
        *param_1 = 1;
        return 0;
      }
      if (DAT_800ff6b4 != 4) goto LAB_8008bea0;
      FUN_8008d4e8();
      FUN_8008b2b8(DAT_800ff6e0);
      iVar1 = 0x32;
    }
    break;
  case 0x32:
    iVar1 = FUN_8008d7a0();
    if (iVar1 == 0) {
      return 0;
    }
    DAT_800ff6b4 = FUN_8008d5f0();
    iVar1 = 1;
    if (DAT_800ff6b4 == 0) {
      DAT_800ff6d4 = 4;
      return 1;
    }
  }
  *param_1 = iVar1;
switchD_8008bcb8_caseD_2:
  return 0;
}

