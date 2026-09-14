/* Analysis pseudo-C, not buildable source. */

void FUN_800242bc(void)

{
  byte bVar1;
  int iVar2;
  
  if (DAT_8009c57e != 0) {
    FUN_8002367c();
  }
  FUN_8002c89c();
  bVar1 = DAT_8009c5f8;
  if (((((DAT_8009c5f8 & 0x80) == 0) || (bVar1 = DAT_8009c5f8 & 0x7f, (DAT_8009c5f8 & 1) == 0)) &&
      (DAT_8009c5f8 = bVar1, iVar2 = FUN_80026bbc(), iVar2 == 0)) &&
     (iVar2 = FUN_800289a4(), iVar2 == 0)) {
    if (DAT_8009c580 == 0) {
      (*(code *)(&PTR_FUN_80091db0)[DAT_8009c564 & 0xf])();
      if ((DAT_8009c564 & 0x8000) == 0) {
        DAT_8009c585 = 0;
      }
    }
    else if ((DAT_8009c580 & 0x80) == 0) {
      DAT_8009c580 = DAT_8009c580 | 0x80;
      FUN_80040204(0x30);
      iVar2 = FUN_800361d8(3,0x22,0x78,0x58,0x50,0x30,0x40);
      do {
        FUN_80039770();
      } while (*(int *)(iVar2 + 0x30) == 0);
    }
    else {
      FUN_80039770();
      if ((DAT_800f09b0 & 0x2000) != 0) {
        FUN_800360d8();
        DAT_8009c580 = 0;
        if (DAT_8009c6d0 != '\0') {
          DAT_8009c582 = DAT_8009c582 | 0x2000;
        }
      }
    }
  }
  return;
}

