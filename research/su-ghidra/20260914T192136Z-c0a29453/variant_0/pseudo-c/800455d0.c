/* Analysis pseudo-C, not buildable source. */

void FUN_800455d0(void)

{
  int iVar1;
  undefined1 local_38 [48];
  
  if ((((*(byte *)(DAT_8009c7e0 + 0x4a) & 0x80) != 0) &&
      (iVar1 = (int)*(short *)(DAT_8009c7e0 + 0x4c),
      *(char *)(DAT_8009c7e0 + iVar1 * 0x30 + 0x80) != '\x11')) &&
     ((iVar1 < 1 ||
      ((*(char *)(DAT_8009c7e0 + (iVar1 + -1) * 0x30 + 0x80) != '\x11' &&
       ((iVar1 < 2 || (*(char *)(DAT_8009c7e0 + (iVar1 + -2) * 0x30 + 0x80) != '\x11')))))))) {
    FUN_800454f8(0xffffffe0,0,1);
    local_38[0] = 0x11;
    FUN_800460a4(local_38);
  }
  return;
}

