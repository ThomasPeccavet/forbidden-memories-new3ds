/* Analysis pseudo-C, not buildable source. */

void FUN_80022174(void)

{
  short sVar1;
  int iVar2;
  
  if ((DAT_8009c72c & 0x100) != 0) {
    DAT_8009c68c = DAT_8009c68c ^ 1;
  }
  if ((DAT_8009c728 & 0xc) != 0) {
    sVar1 = 2;
    if ((DAT_8009c710 & 0x40) != 0) {
      sVar1 = 0x10;
    }
    DAT_800f11e0 = DAT_800f11e0 + sVar1;
    if ((DAT_8009c728 & 4) != 0) {
      DAT_800f11e0 = DAT_800f11e0 + sVar1 * -2;
    }
    FUN_80013448();
  }
  if ((DAT_8009c728 & 0xf000) != 0) {
    if ((DAT_8009c710 & 0x10) == 0) {
      sVar1 = 0x20;
      if ((DAT_8009c710 & 0x20) != 0) {
        sVar1 = 0x80;
      }
      if ((DAT_8009c728 & 0x1000) != 0) {
        DAT_800f11e4 = DAT_800f11e4 + sVar1;
      }
      if ((DAT_8009c728 & 0x4000) != 0) {
        DAT_800f11e4 = DAT_800f11e4 - sVar1;
      }
      if ((DAT_8009c728 & 0x2000) != 0) {
        DAT_800f11e2 = DAT_800f11e2 - sVar1;
      }
      if ((DAT_8009c728 & 0x8000) != 0) {
        DAT_800f11e2 = DAT_800f11e2 + sVar1;
      }
    }
    else {
      iVar2 = 2;
      if ((DAT_8009c710 & 0x40) != 0) {
        iVar2 = 0x10;
      }
      if ((DAT_8009c728 & 0x2000) != 0) {
        DAT_800f11fc = DAT_800f11fc + iVar2;
      }
      if ((DAT_8009c728 & 0x4000) != 0) {
        DAT_800f1204 = DAT_800f1204 - iVar2;
      }
      if ((DAT_8009c728 & 0x8000) != 0) {
        DAT_800f11fc = DAT_800f11fc - iVar2;
      }
      if ((DAT_8009c728 & 0x1000) != 0) {
        DAT_800f1204 = DAT_800f1204 + iVar2;
      }
    }
    FUN_80013448();
  }
  return;
}

