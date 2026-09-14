/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8002f0f0(void)

{
  int iVar1;
  short *psVar2;
  
  psVar2 = &DAT_801d0200;
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    if (*psVar2 == 0) {
      return 0;
    }
    psVar2 = psVar2 + 1;
  } while (iVar1 < 0x28);
  return 1;
}

