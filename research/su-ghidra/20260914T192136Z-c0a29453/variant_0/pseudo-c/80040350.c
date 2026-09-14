/* Analysis pseudo-C, not buildable source. */

int FUN_80040350(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -0x7ff0e6f0;
  iVar1 = 0x10;
  do {
    if ((*(ushort *)(iVar2 + 8) & 0x80) == 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 0x70;
  } while (iVar1 < 0x60);
  return -1;
}

