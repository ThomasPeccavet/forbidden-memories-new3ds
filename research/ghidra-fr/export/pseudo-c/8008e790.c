/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_8008e790(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = (DAT_8009b1e8 & 1) != 0;
  if (bVar1) {
    DAT_8009b1fc = 0;
    DAT_8009b200 = 0;
    DAT_800ffbec = 0;
    DAT_8009b1ec = 0;
    _DAT_8009b1f0 = param_1;
  }
  return bVar1;
}

