/* Analysis pseudo-C, not buildable source. */

void FUN_8003279c(void)

{
  short *psVar1;
  int iVar2;
  short *psVar3;
  
  psVar3 = &DAT_801d07bc;
  iVar2 = 0xf;
  psVar1 = &DAT_801d07da;
  do {
    if ((*psVar1 != 0) && ((&DAT_801d024f)[*psVar1] == '\0')) {
      *psVar1 = 0;
    }
    iVar2 = iVar2 + -1;
    psVar1 = psVar1 + -1;
  } while (-1 < iVar2);
  iVar2 = 0;
  psVar1 = psVar3;
  do {
    if (*psVar1 != 0) {
      if (psVar1 != psVar3) {
        *psVar3 = *psVar1;
        *psVar1 = 0;
      }
      psVar3 = psVar3 + 1;
    }
    iVar2 = iVar2 + 1;
    psVar1 = psVar1 + 1;
  } while (iVar2 < 0x10);
  return;
}

