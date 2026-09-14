/* Analysis pseudo-C, not buildable source. */

void seed_8002d4ac(void)

{
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    DAT_8009c433 = 10;
    FUN_8003c3c4();
    FUN_8016866c(DAT_8009c6f8);
    FUN_800156f8();
  }
  else {
    FUN_80168fcc();
    if ((DAT_8009c60a & 0x40) == 0) {
      FUN_800133d0();
      DAT_8009c433 = 6;
      FUN_80012c50();
    }
  }
  return;
}

