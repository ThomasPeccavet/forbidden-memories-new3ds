/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80024ee0(void)

{
  if ((DAT_8009c550 & 0x80) != 0) {
    return 1;
  }
  DAT_8009c550 = DAT_8009c550 | 0x80;
  return 0;
}

