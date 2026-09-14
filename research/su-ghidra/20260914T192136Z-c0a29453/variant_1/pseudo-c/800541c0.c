/* Analysis pseudo-C, not buildable source. */

void FUN_800541c0(int param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  bool bVar5;
  short sVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  uint uVar12;
  uint uVar13;
  undefined1 auStack_78 [80];
  undefined1 uStack_28;
  undefined1 auStack_27 [7];
  
  iVar7 = param_1 * 0xe20;
  if ((&DAT_800f4f97)[iVar7] == '\0') {
    return;
  }
  if ((1 < *(byte *)((int)&DAT_800f4f38 + iVar7 + 3)) &&
     (((&DAT_800f4f38)[param_1 * 0x388] & 0xffffff) == 0)) {
    return;
  }
  if ((&DAT_800f4f96)[iVar7] == '\0') {
    return;
  }
  uVar12 = (uint)(byte)(&DAT_800f4d6d)[iVar7];
  uVar8 = (uint)*(ushort *)(&DAT_800f4178 + uVar12 * 0x76 + iVar7 + 0x7c4);
  iVar9 = FUN_8005bf24();
  bVar1 = *(byte *)((int)&DAT_800f4f84 + iVar7 + 1);
  pbVar11 = &DAT_800f4d70 + iVar7;
  if (uVar8 == 0) {
    uVar13 = 0;
  }
  else {
    uVar13 = (uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710] % (uVar8 << 4);
    if (uVar8 == 0) {
      trap(0x1c00);
    }
    if ((uVar8 << 4 == 0xffffffff) && ((ushort)(&DAT_800f4f7e)[param_1 * 0x710] == 0x80000000)) {
      trap(0x1800);
    }
  }
  bVar5 = false;
  if (*(int *)(&DAT_800f4178 + (uint)(byte)(&DAT_800f4f76)[iVar7] * 4 + iVar7 + 0xd08) < 0) {
LAB_800543bc:
    if (bVar5) goto LAB_800543d8;
  }
  else {
    cVar2 = *(char *)((int)&DAT_800f4f84 + iVar7 + 2);
    if ((cVar2 != '\b') && ((cVar2 != '\x02' || ((byte)(&DAT_800f4f76)[iVar7] + 3 == uVar12)))) {
      bVar5 = true;
    }
    if (bVar5) {
      sVar6 = FUN_8005bf24();
      uVar13 = (uint)*(ushort *)(&DAT_800f4f80 + iVar7);
      *(ushort *)(&DAT_800f4f80 + iVar7) =
           *(ushort *)(&DAT_800f4f80 + iVar7) +
           (ushort)*(byte *)((int)&DAT_800f4f84 + iVar7 + 1) * sVar6;
      iVar10 = *(int *)(&DAT_800f4178 + (uint)(byte)(&DAT_800f4f76)[iVar7] * 4 + iVar7 + 0xd08);
      uVar12 = (byte)(&DAT_800f4f76)[iVar7] + 3;
      FUN_80090408(auStack_78,s_e_03ld__ld___d_80011434,iVar10 / 1000,iVar10 % 1000,
                   *(ushort *)(&DAT_800f4f80 + iVar7) >> 4);
      FUN_8007f520(auStack_78);
      bVar5 = true;
      goto LAB_800543bc;
    }
  }
  if ((&DAT_800f4f8e)[iVar7] == '#') {
    return;
  }
LAB_800543d8:
  iVar7 = 0;
  FUN_8005d7b0((int)(short)(&DAT_800f4f48)[param_1 * 0x710],
               (int)(short)(&DAT_800f4f4c)[param_1 * 0x710],&uStack_28,auStack_27);
  do {
    uVar4 = *(ushort *)(pbVar11 + 2);
    bVar3 = pbVar11[1];
    uVar8 = uVar4 & 0x8000;
    if ((uVar4 & 0x8000) == 0) {
      uVar8 = param_1 * 0x100 + 0x4000U & 0xffff;
    }
    if (*pbVar11 == 0) {
      return;
    }
    if (*pbVar11 == uVar12) {
      if (((uVar4 & 0x8000) != 0) && (uVar13 == 0)) {
        FUN_800457f0(uVar8 | bVar3);
      }
      if ((uVar13 <= (*(ushort *)(pbVar11 + 2) & 0x7fff)) &&
         ((int)(*(ushort *)(pbVar11 + 2) & 0x7fff) < (int)(uVar13 + (uint)bVar1 * iVar9))) {
        FUN_80048ae8(uVar8 | bVar3,0xff,0);
      }
    }
    iVar7 = iVar7 + 1;
    pbVar11 = pbVar11 + 4;
  } while (iVar7 < 0x40);
  return;
}

