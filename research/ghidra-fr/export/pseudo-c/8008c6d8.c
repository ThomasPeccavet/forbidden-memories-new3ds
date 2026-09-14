/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008c6d8(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 10) {
    if (DAT_800ff6d4 != 0) {
      return 1;
    }
    DAT_800ff6e4 = FUN_80073e18(&DAT_800ff6f4,0x8001);
    if (DAT_800ff6e4 < 0) {
      DAT_800ff6d4 = 5;
      return 1;
    }
  }
  else {
    if (iVar1 < 0xb) {
      if (iVar1 != 0) {
        return 0;
      }
      DAT_8009b198 = 0;
      FUN_8008d068(FUN_8008b8fc);
      *param_1 = 10;
      return 0;
    }
    if (iVar1 != 0xb) {
      if (iVar1 != 0x14) {
        return 0;
      }
      FUN_80073e58(DAT_800ff6e4);
      DAT_800ff6e4 = 0xffffffff;
      return 1;
    }
  }
  *param_1 = 0x14;
  FUN_8008d068(FUN_8008c1ac);
  return 0;
}

