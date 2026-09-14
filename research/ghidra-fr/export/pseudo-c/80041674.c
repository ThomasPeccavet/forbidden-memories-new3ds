/* Analysis pseudo-C, not buildable source. */

void FUN_80041674(void)

{
  short *psVar1;
  undefined **ppuVar2;
  int iVar3;
  
  FUN_800877f8(0x60,0x60,0x60);
  FUN_80087818(0,0,0);
  FUN_80085768(0,&DAT_800923f8);
  FUN_80085768(1,&DAT_80092408);
  FUN_80085768(2,&DAT_80092408);
  iVar3 = 6;
  ppuVar2 = &PTR_FUN_800923f4;
  psVar1 = &DAT_800f11cc;
  do {
    if (-1 < *psVar1) {
      FUN_80087858(0x96);
      FUN_80087838(0,0);
      (*(code *)*ppuVar2)();
    }
    ppuVar2 = ppuVar2 + -1;
    iVar3 = iVar3 + -1;
    psVar1 = psVar1 + -1;
  } while (-1 < iVar3);
  return;
}

