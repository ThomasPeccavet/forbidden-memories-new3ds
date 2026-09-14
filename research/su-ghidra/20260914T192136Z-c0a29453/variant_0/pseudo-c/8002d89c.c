/* Analysis pseudo-C, not buildable source. */

void seed_8002d89c(void)

{
  int iVar1;
  int unaff_gp;
  
  if ((*(byte *)(unaff_gp + 0x372) & 0x40) == 0) {
    *(byte *)(unaff_gp + 0x372) = *(byte *)(unaff_gp + 0x372) | 0x40;
    FUN_8003c90c();
    FUN_801686ac(0);
  }
  iVar1 = FUN_80168e1c();
  if (-1 < iVar1) {
    *(undefined1 *)(unaff_gp + 0x372) = *(undefined1 *)(unaff_gp + 0x375);
  }
  return;
}

