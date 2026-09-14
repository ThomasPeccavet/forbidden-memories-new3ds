/* Analysis pseudo-C, not buildable source. */

void FUN_800248e0(void)

{
  undefined1 uVar1;
  short sVar2;
  ushort uVar3;
  ushort *puVar4;
  undefined2 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  short *psVar8;
  undefined2 *puVar9;
  undefined *puVar10;
  
  puVar10 = &DAT_8018c2d8;
  psVar8 = &DAT_801a7e20;
  iVar7 = 0;
  puVar6 = &DAT_801a7e23;
  puVar9 = &DAT_8015c424;
  do {
    puVar4 = &DAT_80178130;
    sVar2 = puVar9[0xdde2];
    *psVar8 = sVar2;
    uVar1 = (&DAT_80177f94)[iVar7];
    puVar6[-1] = (char)iVar7;
    *puVar6 = (char)iVar7;
    puVar6[1] = uVar1;
    puVar5 = &DAT_8015c424;
    while (uVar3 = *puVar4, puVar4 = puVar4 + 1, (uint)uVar3 != (int)sVar2) {
      puVar5 = puVar5 + 0x2c0;
    }
    FUN_80035ba0(puVar10,puVar5,0x580);
    puVar10 = puVar10 + 0x580;
    puVar6 = puVar6 + 6;
    psVar8 = psVar8 + 3;
    iVar7 = iVar7 + 1;
    puVar9 = puVar9 + 1;
  } while (iVar7 < 0x50);
  return;
}

