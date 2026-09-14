/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80033e98(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = DAT_8009c684 + 0x2d50;
  do {
    iVar2 = iVar2 + 1;
    if (*(char *)(iVar1 + 0xd) == '\0') {
      return 1;
    }
    iVar1 = iVar1 + 0x10;
  } while (iVar2 < 0x28);
  return 0;
}

