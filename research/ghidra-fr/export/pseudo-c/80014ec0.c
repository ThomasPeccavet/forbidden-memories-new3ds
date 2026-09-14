/* Analysis pseudo-C, not buildable source. */

void FUN_80014ec0(void)

{
  if ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0) {
    if (((DAT_8009c460 & 0x10) != 0) && ((DAT_8009c460 & 0x80000) != 0)) {
      FUN_80014f2c();
    }
    DAT_8009c484 = 0x80;
  }
  return;
}

