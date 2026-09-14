/* Analysis pseudo-C, not buildable source. */

void FUN_80013600(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined **ppuVar4;
  int iVar5;
  
  FUN_800137b4(&DAT_801dc000);
  iVar5 = 0;
  puVar3 = &DAT_800eb198;
  ppuVar4 = &PTR_s__DATA_WA_MRG_MRG_1_80091994;
  DAT_8009c4a8 = FUN_80013700;
  DAT_800eb174 = 0x120;
  DAT_800eb176 = 0xe0;
  DAT_800eb17c = 0xb;
  DAT_800eb170 = 0x8000000;
  DAT_8009c458 = 0;
  DAT_800eb184 = 0x808080;
  DAT_800eb17e = 0xa000;
  DAT_800eb178 = 0x180018;
  DAT_800eb180 = 0xfc0230;
  do {
    puVar2 = *ppuVar4;
    if (puVar2 == (undefined *)0x0) {
      return;
    }
    FUN_80013810(puVar3,puVar2);
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    ppuVar4 = ppuVar4 + 1;
    iVar5 = iVar5 + 1;
    FUN_8008fa78(s__s___>__x_80010038,puVar2,uVar1);
  } while (iVar5 < 7);
  return;
}

