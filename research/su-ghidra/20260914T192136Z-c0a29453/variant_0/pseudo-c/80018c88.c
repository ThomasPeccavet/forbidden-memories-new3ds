/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80018c88(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  short local_10 [8];
  
  psVar2 = local_10;
  iVar3 = 0;
  do {
    iVar1 = DAT_8009c500 + iVar3;
    iVar3 = iVar3 + 1;
    *psVar2 = (short)*(char *)(iVar1 + 0x1a);
    psVar2 = psVar2 + 1;
  } while (iVar3 < 5);
  iVar3 = 0x11;
  do {
    iVar1 = 0;
    psVar2 = local_10;
    while ((*psVar2 < 0 || ((short)(&DAT_801a7e20)[*psVar2 * 3] != iVar3))) {
      iVar1 = iVar1 + 1;
      psVar2 = psVar2 + 1;
      if (4 < iVar1) {
        return 0;
      }
    }
    *psVar2 = -1;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x16);
  return 1;
}

