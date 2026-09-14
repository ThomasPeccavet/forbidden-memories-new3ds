/* Analysis pseudo-C, not buildable source. */

void FUN_8004a03c(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
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
    iVar2 = DAT_8009c7d8;
    *(undefined1 *)(DAT_8009c7d8 + 0x502) = 1;
    iVar3 = DAT_8009c7d8;
    *(undefined4 *)(iVar2 + 0x80c) = param_1;
    *(undefined2 *)(iVar3 + 0x7e2) = 1;
    *(undefined1 *)(iVar3 + 0x500) = 0;
  }
  return;
}

