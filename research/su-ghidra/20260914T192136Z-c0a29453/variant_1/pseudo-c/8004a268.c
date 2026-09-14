/* Analysis pseudo-C, not buildable source. */

void FUN_8004a268(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  
  *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
  iVar2 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    puVar4 = &DAT_80011360;
    iVar3 = 0;
    do {
      iVar1 = DAT_8009c7d8 + iVar3;
      if ((*(byte *)(iVar1 + 0x183) >> 4 == 0) && (*(char *)(iVar1 + 0x18d) != '\0')) {
        local_4c = 3;
        local_50 = *puVar4;
        local_48 = *(undefined2 *)(iVar1 + 0x194);
        local_46 = *(undefined2 *)(iVar1 + 0x196);
        FUN_800779e8(&local_50);
      }
      puVar4 = puVar4 + 1;
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar2 = DAT_8009c7d8;
  *(undefined2 *)(DAT_8009c7d8 + 0x7e2) = 1;
  *(undefined1 *)(iVar2 + 0x500) = 0;
  return;
}

