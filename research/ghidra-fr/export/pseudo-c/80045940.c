/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80045940(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 1;
  if (1 < *(short *)(DAT_8009c7e0 + 0x4c)) {
    iVar3 = 0x30;
    do {
      bVar1 = *(byte *)(DAT_8009c7e0 + iVar3 + 0x80);
      if (bVar1 == 0x20) {
        return 1;
      }
      if (bVar1 < 0x21) {
        if (bVar1 == 0x11) {
          return 1;
        }
      }
      else if (bVar1 == 0x24) {
        return 1;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x30;
    } while (iVar2 < *(short *)(DAT_8009c7e0 + 0x4c));
  }
  return 0;
}

