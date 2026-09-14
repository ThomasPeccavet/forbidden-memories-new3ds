/* Analysis pseudo-C, not buildable source. */

void FUN_80049db0(void)

{
  byte bVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar6 = 0;
  uVar5 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    iVar4 = 0;
    puVar3 = &DAT_80011360;
    do {
      if ((*(char *)(DAT_8009c7d8 + iVar4 + 0x18d) != '\0') &&
         (iVar2 = FUN_80077628(*puVar3), iVar2 == 3)) {
        bVar1 = *(byte *)(DAT_8009c7d8 + iVar4 + 0x18d);
        if (bVar1 < 2) {
          *(byte *)(DAT_8009c7d8 + iVar4 + 0x18d) = bVar1 + 1;
        }
        else {
          uVar5 = uVar5 | *puVar3;
          do {
            FUN_80077468(0,*puVar3);
            iVar2 = FUN_80077628(*puVar3);
            if (iVar2 == 2) break;
          } while (iVar2 != 0);
          *(undefined1 *)(DAT_8009c7d8 + iVar4 + 0x18d) = 0;
        }
      }
      iVar4 = iVar4 + 0x28;
      iVar6 = iVar6 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar6 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  if (uVar5 != 0) {
    FUN_80077468(0,uVar5);
  }
  return;
}

