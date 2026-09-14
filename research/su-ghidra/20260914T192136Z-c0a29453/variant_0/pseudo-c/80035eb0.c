/* Analysis pseudo-C, not buildable source. */

void FUN_80035eb0(void)

{
  int iVar1;
  
  iVar1 = FUN_8006aa2c();
  if (iVar1 == 0) {
    if (((DAT_8009c6a0 & 0x40) != 0) || ((DAT_8009c72c & 0x800) != 0)) {
      DAT_8009c6a0 = DAT_8009c6a0 | 0x40;
      DAT_8009c4bb = 1;
      DAT_8009c4ba = 1;
      DAT_8009c4b9 = 1;
      FUN_8006aac0();
    }
  }
  else {
    DAT_8009c460 = DAT_8009c460 & 0xfdffffff;
    DAT_8009c6a0 = DAT_8009c6a0 & 0x7f;
  }
  return;
}

