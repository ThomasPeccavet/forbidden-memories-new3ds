/* Analysis pseudo-C, not buildable source. */

void FUN_8004a788(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    iVar3 = 0x180;
    iVar1 = 0;
    do {
      if (*(byte *)(DAT_8009c7d8 + iVar1 + 0x183) < 0x10) {
        FUN_8004a58c(DAT_8009c7d8 + iVar3,
                     DAT_8009c7d8 + (uint)*(byte *)(DAT_8009c7d8 + iVar1 + 0x183) * 0x18);
        FUN_8004a70c(iVar2,*(undefined2 *)(DAT_8009c7d8 + iVar1 + 0x194),
                     *(undefined2 *)(DAT_8009c7d8 + iVar1 + 0x196));
      }
      iVar3 = iVar3 + 0x28;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  return;
}

