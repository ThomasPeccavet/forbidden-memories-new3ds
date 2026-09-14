/* Analysis pseudo-C, not buildable source. */

void FUN_8007abcc(void)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = *DAT_80094bd4;
  while( true ) {
    uVar2 = FUN_80079728();
    if (uVar2 == 0) break;
    if (((uVar2 & 4) != 0) && (DAT_80094914 != (code *)0x0)) {
      (*DAT_80094914)(DAT_80094bed,&DAT_800f7138);
    }
    if (((uVar2 & 2) != 0) && (DAT_80094910 != (code *)0x0)) {
      (*DAT_80094910)(DAT_80094bec,&DAT_800f7130);
    }
  }
  *DAT_80094bd4 = bVar1 & 3;
  return;
}

