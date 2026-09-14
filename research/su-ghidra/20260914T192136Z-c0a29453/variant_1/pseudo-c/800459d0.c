/* Analysis pseudo-C, not buildable source. */

void FUN_800459d0(void)

{
  ushort *puVar1;
  int *piVar2;
  ushort uVar3;
  byte bVar4;
  byte bVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  char cVar8;
  short sVar9;
  int iVar10;
  uint *puVar11;
  undefined4 uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  
  iVar14 = DAT_8009c7e0;
  switch(*(undefined1 *)(DAT_8009c7e0 + 0x7c)) {
  case 0x11:
    if (*(char *)(DAT_8009c7e0 + 0x7d) == '\0') {
      if (*(short *)(DAT_8009c7e0 + 0x510) == 0) {
        *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 1;
        return;
      }
      if (*(short *)(DAT_8009c7e0 + 0x512) < 0) {
        return;
      }
      *(undefined2 *)(DAT_8009c7e0 + 0x512) = 0xffe0;
      *(undefined1 *)(iVar14 + 0x49) = 0;
      return;
    }
    if (*(char *)(DAT_8009c7e0 + 0x7d) != '\x01') {
      return;
    }
    *(undefined2 *)(DAT_8009c7e0 + 0x534) = 0xffff;
    cVar8 = FUN_80045940();
    iVar14 = DAT_8009c7e0;
    if (cVar8 == '\0') {
      puVar1 = (ushort *)(DAT_8009c7e0 + 0x40);
      *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
      iVar10 = DAT_8009c7e0;
      *(ushort *)(iVar14 + 0x40) = *puVar1 & 0xfff8;
      *(undefined1 *)(iVar10 + 0x7c) = 0;
      return;
    }
    break;
  case 0x20:
    if (*(char *)(DAT_8009c7e0 + 0x7d) != '\0') {
      if (*(char *)(DAT_8009c7e0 + 0x7d) != '\x01') {
        return;
      }
      if (*(char *)(DAT_8009c7e0 + 0x1618) != '\0') {
        return;
      }
      *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
      *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
      cVar8 = FUN_80045940();
      if (cVar8 != '\0') {
        return;
      }
      *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) & 0xfffc;
      return;
    }
    iVar10 = FUN_80014b5c(0,0);
    iVar14 = DAT_8009c7e0;
    puVar6 = DAT_8009c7dc;
    if (iVar10 != 0) {
      return;
    }
    if (*(int *)(DAT_8009c7e0 + 0x4cc) != 0) {
      return;
    }
    DAT_8009c7dc[4] = *(undefined4 *)(DAT_8009c7e0 + 0x6c);
    puVar6[3] = *(undefined4 *)(iVar14 + 0x68);
    puVar6[1] = *(undefined4 *)(iVar14 + 0x60);
    puVar6[6] = *(undefined4 *)(iVar14 + 0x74);
    uVar12 = *(undefined4 *)(iVar14 + 0x70);
    *(undefined1 *)((int)puVar6 + 0x1f) = 0;
    puVar7 = DAT_8009c7dc;
    *(undefined2 *)(puVar6 + 7) = 0;
    puVar6[5] = uVar12;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    iVar14 = DAT_8009c7e0;
    puVar6 = DAT_8009c7dc;
    piVar2 = DAT_8009c7dc + 6;
    *DAT_8009c7dc = *(undefined4 *)(DAT_8009c7e0 + 0x5c);
    puVar7 = DAT_8009c7dc;
    if ((*piVar2 != 0) || (puVar6[5] != 0)) {
      uVar13 = *(uint *)(DAT_8009c7e0 + 0x5c) & 0xf0;
      if (uVar13 == 0x20) {
        iVar14 = DAT_8009c7e0 + 0x1619;
        uVar12 = 5;
      }
      else if (uVar13 < 0x21) {
        iVar14 = DAT_8009c7e0 + 0x1629;
        if (uVar13 != 0x10) goto LAB_80045ba8;
        uVar12 = 4;
      }
      else {
        iVar14 = DAT_8009c7e0 + 0x1639;
        if (uVar13 != 0x40) goto LAB_80045ba8;
        uVar12 = 6;
      }
      *DAT_8009c7dc = uVar12;
      FUN_80014b5c(puVar7,iVar14);
LAB_80045ba8:
      FUN_80045918();
      *(char *)(DAT_8009c7e0 + 0x7d) = *(char *)(DAT_8009c7e0 + 0x7d) + '\x01';
      return;
    }
    *(undefined1 *)(iVar14 + 0x7d) = 0;
    goto LAB_80046084;
  case 0x21:
    iVar10 = FUN_80014b5c(0,0);
    iVar14 = DAT_8009c7e0;
    puVar6 = DAT_8009c7dc;
    if (iVar10 == 0) {
      uVar13 = *(uint *)((uint)*(ushort *)(DAT_8009c7e0 + 0x4e) * 8 + *(int *)(DAT_8009c7e0 + 0x58))
      ;
      DAT_8009c7dc[4] = 0;
      puVar6[6] = 0;
      puVar6[3] = 0;
      puVar6[5] = 0;
      *(undefined2 *)(puVar6 + 7) = 0;
      *(undefined1 *)((int)puVar6 + 0x1f) = *(undefined1 *)(iVar14 + 0x530);
      *(undefined1 *)((int)DAT_8009c7dc + 0x1e) = *(undefined1 *)(DAT_8009c7e0 + 0x531);
      puVar6 = DAT_8009c7dc;
      iVar14 = *(int *)(DAT_8009c7e0 + 0x50);
      *DAT_8009c7dc = 6;
      puVar6[1] = (uVar13 & 0xffffff) + iVar14;
      FUN_80014b5c(puVar6,0);
    }
    break;
  case 0x24:
    iVar10 = FUN_80014b5c(0,0);
    iVar14 = DAT_8009c7e0;
    if (iVar10 == 0) {
      puVar11 = (uint *)((uint)*(ushort *)(DAT_8009c7e0 + 0x4e) * 8 + *(int *)(DAT_8009c7e0 + 0x58))
      ;
      uVar15 = *puVar11;
      uVar13 = puVar11[1];
      *(uint *)(DAT_8009c7e0 + 0x528) = uVar15 & 0xffffff;
      bVar4 = (byte)(uVar15 >> 0x18);
      bVar5 = (byte)(uVar13 >> 0x18);
      *(byte *)(iVar14 + 0x531) = bVar4 & 0x1f;
      iVar10 = DAT_8009c7e0;
      *(uint *)(iVar14 + 0x52c) = uVar13 & 0xffffff;
      *(byte *)(iVar10 + 0x530) = bVar5 & 0x1f;
      *(byte *)(DAT_8009c7e0 + 0x532) = bVar5 >> 7;
      *(byte *)(DAT_8009c7e0 + 0x533) = bVar4 >> 5;
      iVar14 = DAT_8009c7e0;
      piVar2 = (int *)(DAT_8009c7e0 + 0x50);
      *(int *)(DAT_8009c7e0 + 0x528) = *(int *)(DAT_8009c7e0 + 0x528) + *piVar2;
      puVar6 = DAT_8009c7dc;
      *(int *)(iVar14 + 0x52c) = *(int *)(iVar14 + 0x52c) + *piVar2;
      puVar6[4] = 0;
      puVar6[6] = 0;
      puVar6[3] = 0;
      puVar6[5] = 0;
      *(short *)(puVar6 + 7) = (*(short *)(iVar14 + 0x52c) - *(short *)(iVar14 + 0x528)) + 0x10;
      *(undefined1 *)((int)puVar6 + 0x1f) = *(undefined1 *)(iVar14 + 0x530);
      *(undefined1 *)((int)DAT_8009c7dc + 0x1e) = *(undefined1 *)(DAT_8009c7e0 + 0x531);
      puVar6 = DAT_8009c7dc;
      uVar12 = *(undefined4 *)(DAT_8009c7e0 + 0x528);
      *DAT_8009c7dc = 6;
      puVar6[1] = uVar12;
      FUN_80014b5c(puVar6,0);
    }
    break;
  case 0x29:
  case 0x2a:
    if ((*(char *)(DAT_8009c7e0 + 0x7e) != '\0') && (*(short *)(DAT_8009c7e0 + 0x512) != 0)) {
      return;
    }
    *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
    goto LAB_80046064;
  case 0x48:
    if (*(short *)(DAT_8009c7e0 + 0x157a) != 0) {
      sVar9 = FUN_80049b54(*(int *)(DAT_8009c7e0 + 0x1564) + 0x50,0,
                           *(undefined4 *)(*(int *)(DAT_8009c7e0 + 0x1564) + 0xc));
      iVar14 = DAT_8009c7e0;
      *(short *)(DAT_8009c7e0 + 0x157a) = sVar9;
      if (sVar9 != 0) {
        *(undefined1 *)(iVar14 + 0x7c) = 0;
        return;
      }
    }
    if (*(short *)(DAT_8009c7e0 + 0x157e) == 0) {
      if ((*(ushort *)(DAT_8009c7e0 + 0x40) & 0x80) != 0) {
        FUN_8004a0d0(0);
        FUN_8004a3a0(0,0);
        iVar14 = DAT_8009c7e0;
        uVar3 = *(ushort *)(DAT_8009c7e0 + 0x40);
        *(undefined2 *)(DAT_8009c7e0 + 0x1586) = 0;
        *(undefined2 *)(iVar14 + 0x1588) = 0;
        *(ushort *)(iVar14 + 0x40) = uVar3 & 0xff7f;
      }
      FUN_8004a140((int)*(short *)(DAT_8009c7e0 + 0x157e));
      *(undefined2 *)(DAT_8009c7e0 + 0x157e) = 0xffff;
    }
    iVar14 = *(int *)(DAT_8009c7e0 + 0x1564);
    uVar13 = *(ushort *)(DAT_8009c7e0 + 0x4e) & 0xf;
    if (*(ushort *)(iVar14 + 2) <= uVar13) {
      *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
      return;
    }
    sVar9 = FUN_80049ef4((uint)*(ushort *)(iVar14 + uVar13 * 4 + 0x10) * 0x10 + iVar14,
                         (int)*(short *)(DAT_8009c7e0 + 0x157a));
    iVar14 = DAT_8009c7e0;
    *(short *)(DAT_8009c7e0 + 0x157e) = sVar9;
    if (sVar9 == 0) {
      *(undefined2 *)(iVar14 + 0x157c) = *(undefined2 *)(iVar14 + 0x4e);
      FUN_80049f84(1,1);
      iVar14 = DAT_8009c7e0;
      *(undefined1 *)(DAT_8009c7e0 + 0x158a) = 0xff;
      *(ushort *)(iVar14 + 0x40) = *(ushort *)(iVar14 + 0x40) | 0x80;
      *(undefined2 *)(iVar14 + 0x1588) = *(undefined2 *)(iVar14 + 0x54);
    }
    *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
LAB_80046064:
    *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
    return;
  case 0x51:
    FUN_80047b44(*(undefined4 *)(DAT_8009c7e0 + 0x58),*(undefined4 *)(DAT_8009c7e0 + 0x50));
  }
  *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
LAB_80046084:
  *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
  return;
}

