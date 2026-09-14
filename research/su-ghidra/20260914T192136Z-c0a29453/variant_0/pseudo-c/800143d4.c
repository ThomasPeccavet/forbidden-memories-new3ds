/* Analysis pseudo-C, not buildable source. */

void FUN_800143d4(void)

{
  if (((DAT_8009c460 & 0x20) == 0) || ((DAT_8009c460 & 0x40) != 0)) {
    DAT_8009c484 = 0;
    DAT_8009c460 = DAT_8009c460 & 0x60;
  }
  else {
    DAT_8009c460 = DAT_8009c460 & 0x60;
    FUN_800142f8();
    if (DAT_8009c484 != 0) {
      if (((DAT_8009c460 & 0x10) != 0) && ((DAT_8009c460 & 0x80000) != 0)) {
        FUN_80014f2c();
      }
      DAT_8009c484 = 0x80;
    }
  }
  return;
}

