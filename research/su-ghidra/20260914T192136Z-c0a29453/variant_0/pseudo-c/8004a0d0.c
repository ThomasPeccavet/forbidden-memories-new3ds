/* Analysis pseudo-C, not buildable source. */

void FUN_8004a0d0(void)

{
  int iVar1;
  int iVar2;
  
  if (*(short *)(DAT_8009c7d8 + 0x7e0) != -1) {
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
    FUN_8004cef0();
    FUN_8004a9a8();
    iVar1 = DAT_8009c7d8;
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 0;
    iVar2 = DAT_8009c7d8;
    *(undefined2 *)(iVar1 + 0x7e6) = 0x7f;
    *(undefined2 *)(iVar1 + 0x7e4) = 0x7f;
    *(undefined2 *)(iVar1 + 0x7e2) = 2;
    *(undefined1 *)(iVar2 + 0x502) = 0;
  }
  return;
}

