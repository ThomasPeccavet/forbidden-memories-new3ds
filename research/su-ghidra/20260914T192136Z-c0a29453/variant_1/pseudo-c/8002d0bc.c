/* Analysis pseudo-C, not buildable source. */

void seed_8002d0bc(void)

{
  int iVar1;
  byte bVar2;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    DAT_8009c60b = 1;
    if ((DAT_8009c6fc == '\0') && (-1 < DAT_8009c6f3)) {
      DAT_8009c60b = 0;
    }
    DAT_8009c433 = 10;
  }
  else {
    bVar2 = DAT_8009c60b & 0xf;
    if (bVar2 == 1) {
      if ((DAT_8009c60b & 0x80) == 0) {
        DAT_8009c60b = DAT_8009c60b | 0x80;
        FUN_8001798c();
      }
      else {
        FUN_80024444();
        if ((DAT_8009c582 & 0x2000) != 0) {
          DAT_8009c60b = 2;
        }
      }
    }
    else if (bVar2 < 2) {
      if ((DAT_8009c60b & 0xf) == 0) {
        if ((DAT_8009c60b & 0x80) == 0) {
          DAT_8009c680 = 0x80;
          DAT_8009c60b = DAT_8009c60b | 0x80;
          FUN_80032824(PTR_FUN_80010000,&DAT_801d0200,0,0x80);
          FUN_8001591c();
        }
        else {
          iVar1 = FUN_800340e8();
          if (iVar1 == 0) {
            FUN_80040258();
            FUN_80015a1c();
            FUN_8002cf60();
            DAT_8009c60b = 1;
          }
        }
      }
    }
    else if (bVar2 == 2) {
      FUN_80015a1c();
      FUN_80040258();
      FUN_80047f60(2);
      FUN_800133d0();
      DAT_8009c433 = 6;
      FUN_80012c88(4);
      FUN_80013700();
      DAT_8009c60a = DAT_8009c6fa;
      if (DAT_8009c6fa == 2) {
        DAT_8009c638 = *(undefined1 *)(&DAT_8009c6ec + DAT_8009c6f4);
      }
    }
  }
  return;
}

