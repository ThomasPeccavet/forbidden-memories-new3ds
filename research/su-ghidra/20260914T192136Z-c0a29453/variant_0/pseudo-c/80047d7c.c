/* Analysis pseudo-C, not buildable source. */

void FUN_80047d7c(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  
  uVar4 = 0x100000;
  bVar7 = 1;
  uVar6 = 0;
  iVar5 = 0;
  do {
    iVar3 = DAT_8009c7e0 + iVar5;
    bVar1 = *(byte *)(iVar3 + 0x428);
    if (bVar1 != 0) {
      if (bVar1 < *(byte *)(iVar3 + 0x424)) {
        *(byte *)(iVar3 + 0x424) = *(byte *)(iVar3 + 0x424) - bVar1;
      }
      else {
        *(undefined1 *)(iVar3 + 0x424) = 0;
      }
      if (*(char *)(DAT_8009c7e0 + iVar5 + 0x424) == '\0') {
        *(byte *)(DAT_8009c7e0 + 0x434) = *(byte *)(DAT_8009c7e0 + 0x434) & ~bVar7;
        uVar6 = uVar6 | uVar4;
        *(undefined1 *)(DAT_8009c7e0 + iVar5 + 0x428) = 0;
        FUN_80077468(0,uVar4);
      }
      else {
        FUN_80047cf4(iVar5);
      }
    }
    iVar3 = DAT_8009c7e0 + iVar5 * 2;
    sVar2 = *(short *)(iVar3 + 0x42c);
    if (((sVar2 != 0) && (*(short *)(iVar3 + 0x42c) = sVar2 + -1, sVar2 == 1)) &&
       (iVar3 = FUN_80077628(uVar4), iVar3 != 0)) {
      FUN_80077468(0,uVar4);
      uVar6 = uVar6 | uVar4;
    }
    iVar3 = FUN_80077628(uVar4);
    if ((iVar3 == 3) && ((uVar6 & uVar4) == 0)) {
      FUN_80077468(0,uVar4);
      uVar6 = uVar6 | uVar4;
    }
    bVar7 = bVar7 << 1;
    iVar5 = iVar5 + 1;
    uVar4 = uVar4 << 1;
  } while (iVar5 < 4);
  if (uVar6 != 0) {
    FUN_80077468(0,uVar6);
  }
  return;
}

