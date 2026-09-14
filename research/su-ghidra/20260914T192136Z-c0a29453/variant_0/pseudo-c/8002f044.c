/* Analysis pseudo-C, not buildable source. */

void FUN_8002f044(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = FUN_8002e650();
  if (iVar2 == 0) {
    bVar1 = *DAT_8009c624;
    DAT_8009c624 = DAT_8009c624 + 1;
    if ((bVar1 & 0x7f) == 0) {
      FUN_80040258();
    }
    else {
      FUN_8004027c();
    }
    if ((bVar1 & 0x80) != 0) {
      return;
    }
  }
  DAT_8009c610 = 0;
  return;
}

