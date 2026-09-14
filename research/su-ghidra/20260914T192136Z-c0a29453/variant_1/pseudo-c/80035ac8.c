/* Analysis pseudo-C, not buildable source. */

void FUN_80035ac8(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = DAT_8009c698;
  DAT_8009c68c = DAT_8009c68c & 0xfffffffb;
  DAT_8009c69c = DAT_8009c694;
  if (1 < DAT_8009c694) {
    FUN_8008f578(DAT_8009c698,DAT_8009c694,8,&LAB_80035a98);
  }
  uVar2 = DAT_8009c69c;
  uVar3 = 0;
  iVar4 = iVar1;
  if (DAT_8009c69c != 0) {
    do {
      *(short *)(*(short *)(iVar4 + 4) * 8 + iVar1 + 6) = (short)uVar3;
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 8;
    } while (uVar3 < uVar2);
  }
  DAT_8009c694 = 0;
  DAT_8009c690 = DAT_8009c698;
  return;
}

