/* Analysis pseudo-C, not buildable source. */

void seed_80180e48(void)

{
  int *piVar1;
  int iVar2;
  
  FUN_80040690(DAT_80184784);
  DAT_80184784 = 0;
  FUN_80040690(DAT_80184788);
  iVar2 = 0;
  DAT_80184788 = 0;
  FUN_80040690(DAT_8018478c);
  piVar1 = &DAT_80184794;
  DAT_8018478c = 0;
  do {
    if (*piVar1 != 0) {
      FUN_80040690();
      *piVar1 = 0;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0xb);
  DAT_8009c898 = 0;
  return;
}

