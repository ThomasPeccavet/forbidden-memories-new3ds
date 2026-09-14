/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8001f030(int param_1)

{
  short *psVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  undefined2 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar10 = 0;
  puVar5 = &DAT_8015c424;
  do {
    puVar5[0xde34] = 0;
    iVar10 = iVar10 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar10 < 6);
  iVar13 = 0;
  iVar11 = 0;
  uVar6 = (uint)DAT_8009c504;
  iVar10 = uVar6 * 0x14;
  do {
    uVar7 = (uint)(byte)(&DAT_800919e0)[iVar10];
    if ((((&DAT_801a7aee)[uVar7 * 0xe] & 0x8000) != 0) &&
       (uVar3 = *(ushort *)(&DAT_801a7ae4 + uVar7 * 0x1c), uVar3 - 0x2a9 < 6)) {
      iVar13 = iVar13 + 1;
      (&DAT_8017808c)[(short)uVar3 + -0x2a9] = uVar3;
      (&DAT_8017808c)[(short)uVar3 + -0x299] = (ushort)*(byte *)((&DAT_801a7ad8)[uVar7 * 7] + 0x6a);
    }
    iVar11 = iVar11 + 1;
    iVar10 = iVar11 + uVar6 * 0x14;
  } while (iVar11 < 5);
  if (iVar13 != 0) {
    uVar3 = FUN_80016fe4(&DAT_801a7ad8 + (uint)*(byte *)(param_1 + 0x6a) * 7);
    iVar9 = -1;
    iVar10 = -0x7fea3bd2;
    iVar11 = iVar9;
    iVar13 = 5;
    iVar12 = 5;
    bVar2 = DAT_8009c2b9;
    if (DAT_80178096 == 0) goto LAB_8001f198;
    while (iVar9 = iVar12, iVar13 = iVar9, uVar3 <= (ushort)((ushort)bVar2 * 100)) {
LAB_8001f198:
      do {
        iVar12 = iVar13 + -1;
        iVar8 = iVar10 + -2;
        iVar11 = iVar9;
        if (iVar12 < 0) goto LAB_8001f1e0;
        psVar1 = (short *)(iVar10 + 0x1bc66);
        pbVar4 = (byte *)(iVar13 + -0x7ff63d4d);
        iVar10 = iVar8;
        iVar13 = iVar12;
      } while (*psVar1 == 0);
      bVar2 = *pbVar4;
    }
LAB_8001f1e0:
    if (-1 < iVar11) {
      DAT_8009c558 = (short)iVar11 + 0x2a9;
      DAT_8009c5b4 = *(undefined1 *)(&DAT_8017808c + iVar11 + 0x10);
      return 1;
    }
  }
  iVar11 = 0;
  iVar10 = (uint)DAT_8009c504 * 0x14;
  while( true ) {
    uVar6 = (uint)(byte)(&DAT_800919e0)[iVar10];
    if ((((&DAT_801a7aee)[uVar6 * 0xe] & 0x8000) != 0) &&
       (*(short *)(&DAT_801a7ae4 + uVar6 * 0x1c) == 0x2b2)) break;
    iVar11 = iVar11 + 1;
    iVar10 = iVar11 + (uint)DAT_8009c504 * 0x14;
    if (4 < iVar11) {
      return 0;
    }
  }
  DAT_8009c558 = 0x2b2;
  DAT_8009c5b4 = *(undefined1 *)((&DAT_801a7ad8)[uVar6 * 7] + 0x6a);
  return 1;
}

