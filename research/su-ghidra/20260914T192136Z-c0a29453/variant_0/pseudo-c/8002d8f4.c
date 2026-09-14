/* Analysis pseudo-C, not buildable source. */

void seed_8002d8f4(void)

{
  int iVar1;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_8003cae0();
    FUN_8003cb44();
  }
  iVar1 = FUN_8003cc58();
  if (iVar1 == 0) {
    FUN_80040258();
    FUN_80015a1c();
    DAT_8009c60a = DAT_8009c60d;
    if (DAT_8009c60d != 0) {
      DAT_8009c60c = 1;
      DAT_8009c60e = 0;
      DAT_8009c60a = 8;
      FUN_80090d94(&DAT_8009c868,1);
    }
  }
  return;
}

