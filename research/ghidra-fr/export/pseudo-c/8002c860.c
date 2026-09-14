/* Analysis pseudo-C, not buildable source. */

int FUN_8002c860(void)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = FUN_8002c7d8();
  if (iVar1 != 0) {
    *(byte *)(unaff_gp + 0x360) = *(byte *)(unaff_gp + 0x360) | 0x80;
  }
  return iVar1;
}

