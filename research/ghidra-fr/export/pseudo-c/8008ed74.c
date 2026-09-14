/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte FUN_8008ed74(void)

{
  bool bVar1;
  uint uVar2;
  
  if ((_DAT_1f801124 & 0x1000) == 0) {
    if ((_DAT_1f801124 & 0x808) != 0x808) goto LAB_8008ede4;
    uVar2 = (uint)_DAT_1f801128;
  }
  else {
    uVar2 = DAT_800ffbfc;
    DAT_800ffbfc = 0x10000;
  }
  DAT_800ffbfc = uVar2 + DAT_800ffbfc;
LAB_8008ede4:
  if ((_DAT_1f801124 & 0x200) == 0) {
    bVar1 = (int)((_DAT_1f801120 + DAT_800ffbfc) - DAT_800ffbf4) < DAT_800ffbf8 << 3;
  }
  else {
    bVar1 = (int)((_DAT_1f801120 + DAT_800ffbfc) - DAT_800ffbf4) < DAT_800ffbf8;
  }
  return bVar1 ^ 1;
}

