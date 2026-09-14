/* Analysis pseudo-C, not buildable source. */

void FUN_8007a668(void)

{
  byte bVar1;
  
  *DAT_80094bd4 = 1;
  bVar1 = *DAT_80094bd8;
  while ((bVar1 & 7) != 0) {
    *DAT_80094bd4 = 1;
    *DAT_80094bd8 = 7;
    *DAT_80094be4 = 7;
    bVar1 = *DAT_80094bd8;
  }
  DAT_80094bee = 0;
  DAT_80094bed = 0;
  DAT_80094bec = 2;
  *DAT_80094bd4 = 0;
  *DAT_80094bd8 = 0;
  *DAT_80094bdc = 0x1325;
  return;
}

