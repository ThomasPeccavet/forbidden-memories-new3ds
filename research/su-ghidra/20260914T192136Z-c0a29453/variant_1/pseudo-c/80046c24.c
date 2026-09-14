/* Analysis pseudo-C, not buildable source. */

void FUN_80046c24(char param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  char cVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  
  puVar8 = (undefined4 *)&DAT_801e0000;
  DAT_8009c7e0 = &DAT_801e0000;
  DAT_8009c7dc = 0x801e1650;
  do {
    *puVar8 = 0;
    puVar6 = DAT_8009c7e0;
    uVar4 = DAT_80010718;
    uVar3 = DAT_80010714;
    puVar8 = puVar8 + 1;
  } while (puVar8 < &DAT_801ea800);
  DAT_8009c49c = &LAB_80046b28;
  DAT_8009c488 = &LAB_80046b84;
  *(undefined4 *)(DAT_8009c7e0 + 0x1619) = DAT_80010710;
  *(undefined4 *)(puVar6 + 0x161d) = uVar3;
  puVar6[0x1621] = uVar4;
  uVar4 = DAT_8001071a;
  puVar6[0x1622] = DAT_80010719;
  puVar6[0x1623] = uVar4;
  puVar6 = DAT_8009c7e0;
  cVar5 = s_SD_se_dat_8001071c[8];
  uVar3 = s_SD_se_dat_8001071c._4_4_;
  *(undefined4 *)(DAT_8009c7e0 + 0x1629) = s_SD_se_dat_8001071c._0_4_;
  *(undefined4 *)(puVar6 + 0x162d) = uVar3;
  puVar6[0x1631] = cVar5;
  puVar6[0x1632] = s_SD_se_dat_8001071c[9];
  puVar6 = DAT_8009c7e0;
  cVar5 = s_MASTER_XA_80010728[8];
  uVar3 = s_MASTER_XA_80010728._4_4_;
  *(undefined4 *)(DAT_8009c7e0 + 0x1639) = s_MASTER_XA_80010728._0_4_;
  *(undefined4 *)(puVar6 + 0x163d) = uVar3;
  puVar6[0x1641] = cVar5;
  puVar6[0x1642] = s_MASTER_XA_80010728[9];
  DAT_8009c7e0[0x4a] = 3;
  if (param_1 != '\0') {
    DAT_8009c7e0[0x4a] = DAT_8009c7e0[0x4a] | 0xf0;
  }
  DAT_8009c7e0[0x1649] = 0xff;
  DAT_8009c7e0[0x164a] = 0xd2;
  DAT_8009c7e0[0x164b] = 0xff;
  puVar6 = DAT_8009c7e0;
  pbVar1 = DAT_8009c7e0 + 0x1649;
  bVar2 = DAT_8009c7e0[0x164a];
  DAT_8009c7e0[0x49] = 0xff;
  puVar7 = DAT_8009c7e0;
  *(ushort *)(puVar6 + 0x42) = (ushort)*pbVar1;
  *(ushort *)(puVar6 + 0x44) = (ushort)bVar2;
  puVar7[0x1584] = 0xff;
  FUN_80049984(0x801e1670);
  FUN_80046bd8();
  FUN_80045204();
  FUN_800493a4();
  FUN_80047430(0);
  *(undefined1 *)(DAT_8009c7d8 + 0x509) = 0;
  puVar6 = DAT_8009c7e0;
  *(code **)(DAT_8009c7d8 + 0x50c) = FUN_80047d7c;
  *(undefined2 *)(puVar6 + 0x40) = 0;
  return;
}

