/* Analysis pseudo-C, not buildable source. */

void FUN_8004b804(byte param_1,char param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  iVar1 = 0;
  uVar2 = 0;
  uVar3 = uVar2;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    puVar5 = &DAT_80011360;
    iVar4 = 0;
    do {
      if ((*(byte *)(DAT_8009c7d8 + iVar4 + 0x183) == param_1) &&
         (*(char *)(DAT_8009c7d8 + iVar4 + 0x185) == param_2)) {
        FUN_8004ac50(iVar1);
        uVar2 = uVar2 | *puVar5;
      }
      puVar5 = puVar5 + 1;
      iVar1 = iVar1 + 1;
      iVar4 = iVar4 + 0x28;
      uVar3 = uVar2;
    } while (iVar1 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  do {
    if (uVar2 == 0) break;
    FUN_80077468(0,uVar3);
    uVar2 = FUN_80077628(uVar3);
  } while (uVar2 != 2);
  *(undefined1 *)(DAT_8009c7d8 + (uint)param_1 * 0x18 + 4) = 0;
  return;
}

