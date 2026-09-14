/* Analysis pseudo-C, not buildable source. */

void seed_8002d038(void)

{
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_8002ff64(DAT_8009c638);
    DAT_8009c5dc = 0;
  }
  else {
    FUN_80030228(&DAT_800ec220);
    FUN_8002fca4();
    if ((DAT_8009c60a & 0x40) == 0) {
      FUN_80040258();
      FUN_80015a1c();
    }
  }
  return;
}

