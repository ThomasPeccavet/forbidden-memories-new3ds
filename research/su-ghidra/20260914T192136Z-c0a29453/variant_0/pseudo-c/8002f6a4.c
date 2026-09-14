/* Analysis pseudo-C, not buildable source. */

void FUN_8002f6a4(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = FUN_8002e650();
  bVar1 = DAT_800eb24e;
  if (iVar2 == 0) {
    bVar1 = *DAT_8009c624;
    DAT_8009c624 = DAT_8009c624 + 1;
    FUN_800157d4();
    if ((bVar1 & 0x3f) != 0) {
      DAT_800eb24f = bVar1 & 0x3f;
    }
  }
  if ((bVar1 & 0x80) == 0) {
    DAT_8009c610 = 0;
  }
  return;
}

