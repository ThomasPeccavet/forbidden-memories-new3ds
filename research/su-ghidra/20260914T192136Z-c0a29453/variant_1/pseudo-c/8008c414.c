/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008c414(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 10) {
    if (DAT_800ff6d4 != 0) {
      return 1;
    }
    do {
      iVar1 = FUN_80073e28(DAT_800ff6e4,DAT_800ff6e8,0);
    } while (iVar1 != DAT_800ff6e8);
    FUN_8008d4e8();
    do {
      iVar1 = FUN_80073e48(DAT_800ff6e4,DAT_800ff6f0,DAT_800ff6ec);
    } while (iVar1 != 0);
    *param_1 = 0x1e;
  }
  else if (iVar1 < 0xb) {
    if (iVar1 != 0) {
      return 0;
    }
    DAT_8009b194 = 0;
    FUN_8008d068(FUN_8008b8fc);
    *param_1 = 10;
  }
  else if (iVar1 == 0x1e) {
    iVar1 = FUN_8008d7a0();
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = FUN_8008d5f0();
    if (iVar1 == 0) {
LAB_8008c570:
      DAT_800ff6d4 = FUN_8008cefc();
      return 1;
    }
    DAT_8009b194 = DAT_8009b194 + 1;
    if (DAT_8009b194 < 4) {
      *param_1 = 10;
    }
    else {
      if (iVar1 != 4) goto LAB_8008c570;
      FUN_8008d4e8();
      FUN_8008b328(DAT_800ff6e0);
      *param_1 = 0x20;
    }
  }
  else {
    if (iVar1 != 0x20) {
      return 0;
    }
    iVar1 = FUN_8008d7dc();
    if (iVar1 == 0) {
      return 0;
    }
    FUN_8008d6c8();
    *param_1 = 0;
  }
  return 0;
}

