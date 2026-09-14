/* Analysis pseudo-C, not buildable source. */

void seed_8002d5cc(void)

{
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_8003bcb4();
    FUN_8001591c();
  }
  FUN_80169024();
  if ((DAT_8009c60a & 0x40) == 0) {
    FUN_80040258();
  }
  return;
}

