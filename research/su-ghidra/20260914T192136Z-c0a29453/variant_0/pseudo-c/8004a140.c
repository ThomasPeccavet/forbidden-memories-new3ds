/* Analysis pseudo-C, not buildable source. */

void FUN_8004a140(void)

{
  int iVar1;
  
  if (*(short *)(DAT_8009c7d8 + 0x7e0) != -1) {
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
    iVar1 = DAT_8009c7d8;
    *(undefined2 *)(DAT_8009c7d8 + 0x7e0) = 0xffff;
    *(undefined2 *)(iVar1 + 0x7e2) = 0;
    *(undefined2 *)(iVar1 + 0x7e6) = 0x7f;
    *(undefined2 *)(iVar1 + 0x7e4) = 0x7f;
    *(undefined1 *)(iVar1 + 0x500) = 0;
  }
  return;
}

