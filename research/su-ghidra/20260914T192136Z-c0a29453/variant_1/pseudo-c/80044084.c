/* Analysis pseudo-C, not buildable source. */

int FUN_80044084(void)

{
  int iVar1;
  
  FUN_8002cf60();
  FUN_800158f4();
  do {
    DAT_8009c7a8 = 0;
    do {
      while( true ) {
        FUN_8008f708();
        FUN_80012c50();
        if ((DAT_8009c7a8 & 1) != 0) break;
        if ((DAT_8009c7a8 & 0x80) == 0) {
          DAT_8009c7a8 = DAT_8009c7a8 | 0x80;
          FUN_8002cf60();
          FUN_80035e4c(0);
          DAT_8009c4b9 = 0xff;
          DAT_8009c4ba = 0xff;
          DAT_8009c4bb = 0xff;
        }
        else if ((DAT_8009c7a8 & 0x40) == 0) {
          if ((DAT_8009c6a0 & 0x80) == 0) {
            DAT_8009c7a8 = 1;
            if ((DAT_8009c6a0 & 0x40) == 0) {
              FUN_800155f8();
            }
            FUN_800159f4();
          }
        }
        else if ((DAT_8009c72c & 0x8c0) != 0) {
          FUN_800360d8(&DAT_800f0850);
          DAT_8009c7a8 = 1;
        }
      }
      if ((DAT_8009c7a8 & 0x80) == 0) {
        DAT_8009c7a8 = DAT_8009c7a8 | 0x80;
        FUN_8002cf60();
        seed_8018001c(0,0);
        FUN_800156f8();
      }
      iVar1 = seed_80180390();
    } while (iVar1 == -1);
    FUN_80040258();
    FUN_80015a1c();
    seed_80180e48();
    FUN_8002cf60();
  } while (iVar1 == -2);
  return iVar1;
}

