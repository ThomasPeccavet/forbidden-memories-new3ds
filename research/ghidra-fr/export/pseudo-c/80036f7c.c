/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80036f7c(undefined4 param_1)

{
  byte bVar1;
  
  if ((DAT_8009c728 & 0x5008) == 0) {
    return 0;
  }
  DAT_8009c720 = DAT_8009c720 & 0xfffffff7;
  if ((DAT_8009c728 & 8) == 0) {
    if ((DAT_8009c728 & 0x4000) == 0) {
      bVar1 = DAT_8009c6d0 - 1;
      if ((int)((uint)(byte)(DAT_8009c6d0 - 1) << 0x18) < 0) {
        return 1;
      }
    }
    else {
      bVar1 = DAT_8009c6d0 + 1;
      if (DAT_8009c6c1 <= (char)(DAT_8009c6d0 + 1)) {
        return 1;
      }
    }
  }
  else {
    bVar1 = DAT_8009c6d0 + 1;
    if (DAT_8009c6c1 <= (char)(DAT_8009c6d0 + 1)) {
      DAT_8009c6d0 = 0;
      bVar1 = DAT_8009c6d0;
    }
  }
  DAT_8009c6d0 = bVar1;
  FUN_80040204(6);
  FUN_80036ef0(param_1);
  return 1;
}

