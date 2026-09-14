/* Analysis pseudo-C, not buildable source. */

void seed_8002d2b4(void)

{
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_8002c1ac();
    FUN_8001591c();
  }
  else {
    FUN_8002bc38();
    if ((DAT_8009c60a & 0x40) == 0) {
      DAT_8009c424 = 0;
      FUN_80040258();
      FUN_80015a1c();
      FUN_800133d0();
      FUN_80047acc();
      FUN_80047f60(2);
      FUN_80012c88(4);
      FUN_80013700();
    }
  }
  return;
}

