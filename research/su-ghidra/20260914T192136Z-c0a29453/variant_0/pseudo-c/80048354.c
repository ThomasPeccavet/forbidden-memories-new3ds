/* Analysis pseudo-C, not buildable source. */

void FUN_80048354(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    FUN_80077468(0,0xf00000);
    FUN_8007795c(DAT_8009c7e0 + 0x15d8);
    iVar1 = iVar1 + 1;
    if ((uint)*(byte *)(DAT_8009c7e0 + 0x15ef) * 2 + (uint)*(byte *)(DAT_8009c7e0 + 0x15ed) +
        (uint)*(byte *)(DAT_8009c7e0 + 0x15ee) == 0) {
      return;
    }
  } while (iVar1 < 0x18);
  return;
}

