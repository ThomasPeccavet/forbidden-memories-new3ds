/* Analysis pseudo-C, not buildable source. */

void seed_8002d75c(void)

{
  int iVar1;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_8006b560();
    FUN_80013700();
    FUN_8003a22c();
    seed_8018001c(DAT_8009c60c,DAT_8009c60e);
    FUN_8001591c();
  }
  FUN_8008f708();
  iVar1 = seed_80180390();
  if (-1 < iVar1) {
    FUN_80040258();
    FUN_80015a1c();
    seed_80180e48();
    FUN_8002d62c(iVar1);
    DAT_8009c60d = 8;
  }
  return;
}

