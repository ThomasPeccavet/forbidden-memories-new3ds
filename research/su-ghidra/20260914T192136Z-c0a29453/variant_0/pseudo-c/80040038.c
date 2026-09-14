/* Analysis pseudo-C, not buildable source. */

int FUN_80040038(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  short *psVar4;
  
  if ((DAT_8009c738 & 0x80) == 0) {
    DAT_8009c738 = DAT_8009c738 | 0x80;
    DAT_8009c77b = 0x28;
  }
  iVar1 = FUN_8003fffc();
  if (iVar1 == 1) {
    psVar2 = (short *)&DAT_801d1200;
    psVar4 = (short *)&DAT_801d2200;
    iVar3 = 0;
    DAT_8009c77a = 10;
    DAT_8009c77b = 0x24;
    do {
      if (*psVar2 == 0) {
        DAT_8009c77a = 10;
        DAT_8009c77b = 0x24;
        DAT_801bf8cc = 1;
        return 0;
      }
      iVar3 = iVar3 + 1;
      if (*psVar4 == 0) {
        DAT_8009c77a = 10;
        DAT_8009c77b = 0x24;
        DAT_801bf8cc = 2;
        return 0;
      }
      psVar2 = psVar2 + 1;
      psVar4 = psVar4 + 1;
    } while (iVar3 < 0x28);
    FUN_8003bf3c(&DAT_801bf800,&DAT_801d160c,6);
    FUN_8003bf3c(&DAT_801bf814,&DAT_801d260c,6);
  }
  return iVar1;
}

