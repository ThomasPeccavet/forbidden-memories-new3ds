/* Analysis pseudo-C, not buildable source. */

void FUN_80028398(void)

{
  int iVar1;
  
  iVar1 = FUN_80028370();
  if (iVar1 == 0) {
    FUN_80036184(0,DAT_8009c5da,0x10,0xb0,0x120,0x30);
    return;
  }
  FUN_80039770(0);
  if ((DAT_8009c5de & 0x40) == 0) {
    if ((DAT_800f0884 & 0x2000) == 0) {
      return;
    }
    if ((DAT_800f0884 & 0x20) == 0) {
      DAT_800f0880 = FUN_8003748c(&DAT_800f0850);
      DAT_8009c5de = DAT_8009c5de | 0x40;
      return;
    }
  }
  else {
    iVar1 = FUN_8003ba24();
    if (iVar1 == 0) {
      return;
    }
    FUN_80040204(0xb);
  }
  FUN_800360d8(&DAT_800f0850);
  DAT_8009c5dc = DAT_8009c5dc | 0x40;
  return;
}

