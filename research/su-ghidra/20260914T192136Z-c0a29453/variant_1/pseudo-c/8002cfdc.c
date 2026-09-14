/* Analysis pseudo-C, not buildable source. */

void seed_8002cfdc(void)

{
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_800303ec();
  }
  else {
    FUN_80031388();
    if ((DAT_8009c60a & 0x40) == 0) {
      DAT_8009c60d = 0;
    }
  }
  return;
}

