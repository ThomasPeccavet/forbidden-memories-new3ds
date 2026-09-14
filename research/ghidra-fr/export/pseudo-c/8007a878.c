/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007a878(void)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_80090cf8(s_CD_init__80011cbc);
  FUN_8008fa78(s_addr__08x_80011cc8,&PTR_DAT_80094bf0);
  DAT_8009492d = 0;
  DAT_8009492c = 0;
  DAT_80094914 = 0;
  DAT_80094910 = 0;
  DAT_80094920 = 0;
  DAT_8009491c = 0;
  FUN_800748d8();
  FUN_80074908(2,FUN_8007abcc);
  *DAT_80094bd4 = 1;
  bVar1 = *DAT_80094bd8;
  while ((bVar1 & 7) != 0) {
    *DAT_80094bd4 = 1;
    *DAT_80094bd8 = 7;
    *DAT_80094be4 = 7;
    bVar1 = *DAT_80094bd8;
  }
  DAT_80094bee = 0;
  DAT_80094bed = 0;
  DAT_80094bec = 2;
  *DAT_80094bd4 = 0;
  *DAT_80094bd8 = 0;
  *DAT_80094bdc = 0x1325;
  FUN_8007a1d4(1,0,0,0);
  if ((DAT_8009491c & 0x10) != 0) {
    FUN_8007a1d4(1,0,0,0);
  }
  iVar2 = FUN_8007a1d4(10,0,0,0);
  uVar3 = 0xffffffff;
  if (iVar2 == 0) {
    iVar2 = FUN_8007a1d4(0xc,0,0,0);
    if (iVar2 == 0) {
      iVar2 = FUN_80079c8c(0,0);
      uVar3 = 0xffffffff;
      if (iVar2 == 2) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

