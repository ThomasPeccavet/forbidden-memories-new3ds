/* Analysis pseudo-C, not buildable source. */

void FUN_8004ccdc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    iVar3 = 0x180;
    do {
      iVar1 = DAT_8009c7d8 + iVar3;
      if ((*(short *)(iVar1 + 0x1e) == 0) || (0xf < *(byte *)(iVar1 + 3))) {
        *(undefined2 *)(iVar1 + 0x1e) = 0;
      }
      else {
        *(short *)(iVar1 + 0x1e) = *(short *)(iVar1 + 0x1e) + -1;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  return;
}

