/* Analysis pseudo-C, not buildable source. */

void seed_8002d858(void)

{
  int unaff_gp;
  
  if ((*(byte *)(unaff_gp + 0x372) & 0x40) == 0) {
    *(byte *)(unaff_gp + 0x372) = *(byte *)(unaff_gp + 0x372) | 0x40;
    FUN_8003c1b8();
    FUN_80169e64();
  }
  FUN_8016a160();
  return;
}

