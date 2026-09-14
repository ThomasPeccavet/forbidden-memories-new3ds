/* Analysis pseudo-C, not buildable source. */

void seed_8002dbe0(void)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  FUN_80087838(0xa0,0x80);
  FUN_80087858(300);
  if ((DAT_8009c60a & 0x40) != 0) goto LAB_8002dc60;
  DAT_8009c60a = DAT_8009c60a | 0x40;
  FUN_8001569c();
  while( true ) {
    DAT_801d07dc = 0x30;
    uVar3 = 0x20;
    do {
      FUN_8002ceb8(uVar3 | 0x8000);
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 0x120);
    DAT_8009c60b = 0;
    DAT_801d05de = DAT_801d05de | 3;
LAB_8002dc60:
    bVar2 = DAT_8009c60b & 0xf;
    if (bVar2 == 1) {
      if ((DAT_8009c60b & 0x80) == 0) {
        DAT_8009c60b = DAT_8009c60b | 0x80;
        iVar1 = (DAT_801d0534 % 5) * 4;
        DAT_801bf88c = (uint)*(ushort *)(&DAT_80091f68 + iVar1);
        DAT_801bf890 = (uint)*(ushort *)(&DAT_80091f6a + iVar1);
        FUN_800361d8(0,0x23,0x10,0x70,0x120,0x10,0x12);
      }
      FUN_80039770();
      if ((DAT_800f0884 & 0x10) != 0) {
        return;
      }
      FUN_800360d8();
      DAT_8009c60b = 2;
      return;
    }
    if (1 < bVar2) break;
    if ((DAT_8009c60b & 0xf) != 0) {
      return;
    }
    if ((DAT_8009c60b & 0x80) == 0) {
      DAT_8009c60b = DAT_8009c60b | 0x80;
      FUN_8003fba0();
    }
    iVar1 = FUN_8003fa30();
    if (iVar1 == 0) {
      return;
    }
    if (iVar1 != 2) {
      DAT_8009c60b = 1;
      return;
    }
  }
  if (bVar2 != 2) {
    return;
  }
  if ((DAT_8009c60b & 0x80) == 0) {
    DAT_8009c60b = DAT_8009c60b | 0x80;
    FUN_80035f64();
    FUN_8003a22c();
    DAT_8009c424 = 1;
    FUN_8005622c();
    FUN_80056540();
    FUN_8005cda4();
    return;
  }
  FUN_8005cdd8();
  FUN_80039770();
  FUN_8005cdec();
  return;
}

