/* Analysis pseudo-C, not buildable source. */

void FUN_800463f8(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  
  FUN_8007795c(DAT_8009c7e0 + 0x15d8);
  bVar2 = *(char *)(DAT_8009c7e0 + 0x15ec) == '\x03';
  if (*(char *)(DAT_8009c7e0 + 0x15ed) == '\x03') {
    bVar2 = bVar2 | 2;
  }
  if (*(char *)(DAT_8009c7e0 + 0x15ee) == '\x03') {
    bVar2 = bVar2 | 4;
  }
  if (*(char *)(DAT_8009c7e0 + 0x15ef) == '\x03') {
    bVar2 = bVar2 | 8;
  }
  if (bVar2 != 0) {
    FUN_80077468(0);
  }
  if ((((*(ushort *)(DAT_8009c7e0 + 0x40) & 0x80) != 0) && (*(short *)(DAT_8009c7e0 + 0x157e) != -1)
      ) && (sVar3 = FUN_8004a3e0(), sVar3 != 1)) {
    FUN_8004a0d0((int)*(short *)(DAT_8009c7e0 + 0x157e));
    iVar7 = DAT_8009c7e0;
    uVar1 = *(ushort *)(DAT_8009c7e0 + 0x40);
    *(undefined2 *)(DAT_8009c7e0 + 0x1588) = 0xff80;
    *(undefined1 *)(iVar7 + 0x158a) = 0;
    *(ushort *)(iVar7 + 0x40) = uVar1 & 0xff7f;
  }
  FUN_80046154();
  iVar7 = DAT_8009c7e0;
  if (*(char *)(DAT_8009c7e0 + 0x7c) != '\0') {
    FUN_800459d0();
    return;
  }
  if (*(short *)(DAT_8009c7e0 + 0x4c) == 0) {
    return;
  }
  bVar2 = *(byte *)(DAT_8009c7e0 + 0x80);
  puVar11 = (undefined1 *)(DAT_8009c7e0 + 0x80);
  if (bVar2 != 0x44) {
    if (bVar2 < 0x45) {
      if (((bVar2 == 0x29) || (bVar2 == 0x2a)) && (*(short *)(DAT_8009c7e0 + 0x512) == 0)) {
        *(undefined2 *)(DAT_8009c7e0 + 0x512) = *(undefined2 *)(DAT_8009c7e0 + 0x88);
        *(undefined1 *)(iVar7 + 0x49) = *(undefined1 *)(iVar7 + 0x82);
      }
      goto LAB_800465dc;
    }
    if (bVar2 != 0x45) goto LAB_800465dc;
  }
  if (*(short *)(DAT_8009c7e0 + 0x1588) == 0) {
    *(undefined2 *)(DAT_8009c7e0 + 0x1588) = *(undefined2 *)(DAT_8009c7e0 + 0x88);
    *(undefined1 *)(iVar7 + 0x1584) = *(undefined1 *)(iVar7 + 0x82);
  }
LAB_800465dc:
  *(undefined1 *)(DAT_8009c7e0 + 0x7c) = *puVar11;
  *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
  iVar6 = DAT_8009c7e0;
  *(undefined2 *)(DAT_8009c7e0 + 0x4e) = *(undefined2 *)(iVar7 + 0x82);
  *(undefined4 *)(iVar6 + 0x50) = *(undefined4 *)(iVar7 + 0x84);
  *(undefined4 *)(iVar6 + 0x54) = *(undefined4 *)(iVar7 + 0x88);
  *(undefined4 *)(iVar6 + 0x58) = *(undefined4 *)(iVar7 + 0x8c);
  *(undefined1 *)(iVar6 + 0x7e) = *(undefined1 *)(iVar7 + 0x81);
  iVar6 = DAT_8009c7e0;
  uVar8 = *(undefined4 *)(iVar7 + 0x94);
  uVar9 = *(undefined4 *)(iVar7 + 0x98);
  uVar10 = *(undefined4 *)(iVar7 + 0x9c);
  *(undefined4 *)(DAT_8009c7e0 + 0x5c) = *(undefined4 *)(iVar7 + 0x90);
  *(undefined4 *)(iVar6 + 0x60) = uVar8;
  *(undefined4 *)(iVar6 + 100) = uVar9;
  *(undefined4 *)(iVar6 + 0x68) = uVar10;
  uVar8 = *(undefined4 *)(iVar7 + 0xa4);
  uVar9 = *(undefined4 *)(iVar7 + 0xa8);
  uVar10 = *(undefined4 *)(iVar7 + 0xac);
  *(undefined4 *)(iVar6 + 0x6c) = *(undefined4 *)(iVar7 + 0xa0);
  *(undefined4 *)(iVar6 + 0x70) = uVar8;
  *(undefined4 *)(iVar6 + 0x74) = uVar9;
  *(undefined4 *)(iVar6 + 0x78) = uVar10;
  *(undefined2 *)(iVar6 + 0x15f4) = 8;
  *(short *)(iVar6 + 0x4c) = *(short *)(iVar6 + 0x4c) + -1;
  FUN_800459d0();
  puVar12 = (undefined4 *)(iVar7 + 0xb0);
  iVar7 = 0;
  if (0 < *(short *)(DAT_8009c7e0 + 0x4c)) {
    iVar6 = 0;
    do {
      *(undefined1 *)(DAT_8009c7e0 + iVar6 + 0x80) = *(undefined1 *)puVar12;
      puVar4 = (undefined4 *)(DAT_8009c7e0 + iVar6 + 0x80);
      puVar5 = puVar12;
      do {
        uVar8 = puVar5[1];
        uVar9 = puVar5[2];
        uVar10 = puVar5[3];
        *puVar4 = *puVar5;
        puVar4[1] = uVar8;
        puVar4[2] = uVar9;
        puVar4[3] = uVar10;
        puVar5 = puVar5 + 4;
        puVar4 = puVar4 + 4;
      } while (puVar5 != puVar12 + 0xc);
      iVar6 = iVar6 + 0x30;
      iVar7 = iVar7 + 1;
      puVar12 = puVar12 + 0xc;
    } while (iVar7 < *(short *)(DAT_8009c7e0 + 0x4c));
  }
  return;
}

