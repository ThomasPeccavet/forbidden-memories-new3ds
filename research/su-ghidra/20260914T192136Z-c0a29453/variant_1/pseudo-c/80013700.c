/* Analysis pseudo-C, not buildable source. */

void FUN_80013700(void)

{
  if ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0) {
    do {
      if ((DAT_8009c460 & 0x20) == 0) {
        FUN_80014f54();
      }
      FUN_80012c50();
    } while ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0);
  }
  while (DAT_8009c484 != 0) {
    FUN_80012c50();
  }
  return;
}

