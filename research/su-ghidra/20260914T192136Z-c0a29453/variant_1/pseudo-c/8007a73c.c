/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007a73c(void)

{
  int iVar1;
  
  iVar1 = DAT_80094be8;
  if ((*(short *)(DAT_80094be8 + 0x1b8) == 0) && (*(short *)(DAT_80094be8 + 0x1ba) == 0)) {
    *(undefined2 *)(DAT_80094be8 + 0x180) = 0x3fff;
    *(undefined2 *)(iVar1 + 0x182) = 0x3fff;
  }
  iVar1 = DAT_80094be8;
  *(undefined2 *)(DAT_80094be8 + 0x1b0) = 0x3fff;
  *(undefined2 *)(iVar1 + 0x1b2) = 0x3fff;
  *(undefined2 *)(iVar1 + 0x1aa) = 0xc001;
  *DAT_80094bd4 = 2;
  *DAT_80094be4 = 0x80;
  *DAT_80094bd8 = 0;
  *DAT_80094bd4 = 3;
  *DAT_80094be0 = 0x80;
  *DAT_80094be4 = 0;
  *DAT_80094bd8 = 0x20;
  return 0;
}

