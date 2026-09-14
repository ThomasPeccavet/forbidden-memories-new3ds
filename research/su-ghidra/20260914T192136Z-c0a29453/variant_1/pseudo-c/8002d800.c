/* Analysis pseudo-C, not buildable source. */

void seed_8002d800(void)

{
  int iVar1;
  int unaff_gp;
  
  if ((*(byte *)(unaff_gp + 0x372) & 0x40) == 0) {
    *(byte *)(unaff_gp + 0x372) = *(byte *)(unaff_gp + 0x372) | 0x40;
    FUN_8003bef4();
    FUN_80168344();
  }
  iVar1 = FUN_80169a1c();
  if (iVar1 != 0) {
    *(undefined1 *)(unaff_gp + 0x372) = *(undefined1 *)(unaff_gp + 0x375);
  }
  return;
}

