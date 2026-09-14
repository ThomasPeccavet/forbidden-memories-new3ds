/* Analysis pseudo-C, not buildable source. */

void FUN_80049f84(char param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
  iVar2 = DAT_8009c7d8;
  if (*(short *)(DAT_8009c7d8 + 0x7e0) == -1) {
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 0;
  }
  else {
    puVar1 = (undefined4 *)(DAT_8009c7d8 + 0x7e8);
    *(undefined4 *)(DAT_8009c7d8 + 0x7ec) = 0x10000;
    *(undefined4 *)(iVar2 + 0x7dc) = *puVar1;
    FUN_8004cc0c();
    if (param_1 == '\0') {
      *(undefined2 *)(DAT_8009c7d8 + 0x7e2) = 4;
    }
    else {
      *(undefined1 *)(DAT_8009c7d8 + 0x502) = 1;
      *(undefined2 *)(DAT_8009c7d8 + 0x7e2) = 1;
    }
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 0;
  }
  return;
}

