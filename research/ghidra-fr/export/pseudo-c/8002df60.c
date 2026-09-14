/* Analysis pseudo-C, not buildable source. */

void FUN_8002df60(void)

{
  FUN_8002cfbc();
  do {
    do {
      while( true ) {
        FUN_80012c50();
        if ((DAT_8009c60a & 0x80) != 0) break;
        DAT_8009c60a = DAT_8009c60a | 0x80;
        FUN_8002cf60();
      }
      (*(code *)(&PTR_LAB_80091f7c)[DAT_8009c60a & 0x1f])();
    } while ((DAT_8009c60a & 0x40) != 0);
    FUN_80015a1c();
  } while( true );
}

