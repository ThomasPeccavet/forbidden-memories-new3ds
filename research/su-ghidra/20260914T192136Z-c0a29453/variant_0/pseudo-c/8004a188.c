/* Analysis pseudo-C, not buildable source. */

void FUN_8004a188(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  
  *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
  iVar1 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    puVar3 = &DAT_80011360;
    iVar2 = 0;
    do {
      if ((*(byte *)(DAT_8009c7d8 + iVar2 + 0x183) >> 4 == 0) &&
         (*(char *)(DAT_8009c7d8 + iVar2 + 0x18d) != '\0')) {
        local_4c = 3;
        local_50 = *puVar3;
        local_48 = 0;
        local_46 = 0;
        FUN_800779e8(&local_50);
      }
      puVar3 = puVar3 + 1;
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x28;
    } while (iVar1 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar1 = DAT_8009c7d8;
  *(undefined2 *)(DAT_8009c7d8 + 0x7e2) = 4;
  *(undefined1 *)(iVar1 + 0x500) = 0;
  return;
}

