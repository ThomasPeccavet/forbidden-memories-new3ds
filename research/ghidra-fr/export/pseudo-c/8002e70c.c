/* Analysis pseudo-C, not buildable source. */

void FUN_8002e70c(void)

{
  ushort *puVar1;
  int iVar2;
  
  iVar2 = FUN_8002e650();
  if (iVar2 == 0) {
    DAT_8009c4c2 = 0;
    DAT_8009c4c0 = 0;
    FUN_8002e2a4(&DAT_800ec220);
    DAT_8009c630 = *DAT_8009c624;
    puVar1 = DAT_8009c624 + 1;
    if ((DAT_8009c630 & 0x8000) != 0) {
      DAT_8009c4c0 = DAT_8009c624[1];
      DAT_8009c4c2 = DAT_8009c624[2];
      puVar1 = DAT_8009c624 + 3;
      DAT_8009c630 = DAT_8009c630 & 0xfff;
    }
    DAT_8009c624 = puVar1;
    FUN_8002e11c(&DAT_800ec220,DAT_8009c630);
  }
  if ((DAT_8009c610 & 0x800) == 0) {
    if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
      DAT_8009c610 = DAT_8009c610 | 0x800;
      FUN_8002e3c0(&DAT_800ec220,0xffffffff);
      FUN_800156f8();
    }
  }
  else if ((DAT_800eb24e & 0x80) == 0) {
    DAT_8009c610 = 0;
  }
  return;
}

