/* Analysis pseudo-C, not buildable source. */

int FUN_8004843c(short param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  short local_18 [4];
  
  sVar4 = 0;
  iVar1 = 0x14;
  iVar2 = 0;
  do {
    FUN_800781e8(iVar1,local_18);
    if ((*(short *)(DAT_8009c7e0 + iVar2 * 2 + 0x404) == param_1) && (local_18[0] != 0)) {
      sVar4 = sVar4 + 1;
    }
    iVar3 = iVar2 + 1;
    iVar1 = iVar2 + 0x15;
    iVar2 = iVar3;
  } while (iVar3 < 4);
  return (int)sVar4;
}

