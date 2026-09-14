/* Analysis pseudo-C, not buildable source. */

void seed_8002d544(void)

{
  int iVar1;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_80032824(PTR_FUN_80010000,&DAT_801d0200,0,DAT_8009c680);
    FUN_8001591c();
  }
  else {
    iVar1 = FUN_800340e8();
    if (iVar1 == 0) {
      FUN_80040258();
      FUN_80015a1c();
      DAT_8009c60a = DAT_8009c60d;
    }
  }
  return;
}

