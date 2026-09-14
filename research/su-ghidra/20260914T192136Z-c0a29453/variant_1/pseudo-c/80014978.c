/* Analysis pseudo-C, not buildable source. */

void FUN_80014978(void)

{
  if (DAT_8009c490 == 0) {
    DAT_8009c490 = 1;
    if (DAT_8009c494 == 0) {
      DAT_8009c494 = 1;
      if (((DAT_8009c460 & 0x10) == 0) && ((DAT_8009c460 & 0x20) != 0)) {
        FUN_800142f8();
      }
      if ((DAT_8009c460 & 0x10) == 0) {
        DAT_8009c484 = 0;
      }
      else {
        if ((DAT_8009c484 != 0) && ((DAT_8009c484 & 0x40) == 0)) {
          DAT_800eb1fe = 5;
          DAT_800eb1ff = 0;
          DAT_8009c484 = DAT_8009c484 | 0x40;
        }
        FUN_80014478();
      }
      DAT_8009c494 = 0;
    }
  }
  else {
    DAT_8009c490 = 0;
  }
  return;
}

