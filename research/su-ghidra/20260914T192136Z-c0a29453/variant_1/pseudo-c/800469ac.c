/* Analysis pseudo-C, not buildable source. */

void FUN_800469ac(void)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  iVar6 = 0;
  if (0 < *(short *)(DAT_8009c7e0 + 0x4c)) {
    iVar7 = 0x30;
    iVar5 = 0;
    while (*(short *)(DAT_8009c7e0 + 0x4c) != 0) {
      bVar1 = *(byte *)(DAT_8009c7e0 + iVar5 + 0x80);
      if (bVar1 == 0x29) {
LAB_80046a20:
        puVar2 = (undefined4 *)(DAT_8009c7e0 + iVar5 + 0x80);
        iVar3 = DAT_8009c7e0 + iVar7;
        puVar4 = (undefined4 *)(iVar3 + 0x80);
        do {
          uVar8 = puVar4[1];
          uVar9 = puVar4[2];
          uVar10 = puVar4[3];
          *puVar2 = *puVar4;
          puVar2[1] = uVar8;
          puVar2[2] = uVar9;
          puVar2[3] = uVar10;
          puVar4 = puVar4 + 4;
          puVar2 = puVar2 + 4;
        } while (puVar4 != (undefined4 *)(iVar3 + 0xb0));
        *(short *)(DAT_8009c7e0 + 0x4c) = *(short *)(DAT_8009c7e0 + 0x4c) + -1;
      }
      else {
        if (bVar1 < 0x2a) {
          if (bVar1 == 0x24) goto LAB_80046a20;
        }
        else if (bVar1 == 0x2b) goto LAB_80046a20;
        iVar7 = iVar7 + 0x30;
        iVar5 = iVar5 + 0x30;
        iVar6 = iVar6 + 1;
      }
      if ((*(short *)(DAT_8009c7e0 + 0x4c) <= iVar6) || (iVar6 < 0)) break;
    }
  }
  bVar1 = *(byte *)(DAT_8009c7e0 + 0x7c);
  if (bVar1 != 0x29) {
    if (bVar1 < 0x2a) {
      if (bVar1 != 0x24) {
        return;
      }
    }
    else if (bVar1 != 0x2b) {
      return;
    }
  }
  *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
  *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
  return;
}

