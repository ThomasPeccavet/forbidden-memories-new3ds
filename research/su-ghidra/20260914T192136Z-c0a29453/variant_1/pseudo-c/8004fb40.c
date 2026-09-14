/* Analysis pseudo-C, not buildable source. */

void FUN_8004fb40(short *param_1)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 != (short *)0x0) || (param_1 = DAT_8009c30c, DAT_8009c30c != (short *)0x0)) {
    iVar3 = 0;
    iVar2 = 0x10;
    psVar1 = param_1;
    do {
      if ((psVar1[3] < 4) && (1 < psVar1[3])) {
        FUN_8005c0b8((int)*psVar1,(int)param_1 + iVar2);
      }
      iVar2 = iVar2 + 8;
      iVar3 = iVar3 + 1;
      psVar1 = psVar1 + 4;
    } while (iVar3 < 2);
  }
  return;
}

