/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007c9f0(void)

{
  FUN_8007a668();
  DAT_80094cf8 = DAT_80094cf8 + 1;
  if (*(int *)(&DAT_80094d04 + (uint)DAT_80094cb4 * 4) == 0) {
    DAT_80094cf4 = 0x1e;
  }
  else {
    DAT_80094cf4 = *(int *)(&DAT_80094d04 + (uint)DAT_80094cb4 * 4) * 0x3c;
  }
  FUN_8007a1d4(DAT_80094cb4,DAT_80094cbc,0,1);
  return 0;
}

