/* Analysis pseudo-C, not buildable source. */

void FUN_80031388(void)

{
  bool bVar1;
  byte bVar2;
  undefined **ppuVar3;
  int iVar4;
  
  FUN_8008f708();
  iVar4 = 0;
  if (DAT_8009c673 != 0) {
    if (DAT_8009c678 == 0) {
      ppuVar3 = &PTR_LAB_800921c0;
    }
    else {
      ppuVar3 = &PTR_LAB_800921b0;
    }
    (*(code *)ppuVar3[DAT_8009c673 & 0x1f])();
    return;
  }
  do {
    FUN_8007f520(&DAT_8009c2e4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x16);
  if ((DAT_8009c728 & 0xf000) == 0) goto LAB_80031560;
  if ((DAT_8009c728 & 0xa000) != 0) {
    if ((DAT_8009c728 & 0x2000) == 0) {
      bVar2 = DAT_8009c679 - 10;
      if (-1 < (char)DAT_8009c679 + -10) goto LAB_80031488;
    }
    else {
      bVar2 = DAT_8009c679 + 10;
      if ((char)DAT_8009c679 + 10 < 0x14) {
LAB_80031488:
        DAT_8009c679 = bVar2;
      }
    }
  }
  if ((DAT_8009c728 & 0x1000) != 0) {
    bVar1 = (char)DAT_8009c679 < '\n';
    DAT_8009c679 = DAT_8009c679 - 1;
    if (bVar1) {
      bVar2 = 9;
      if ((int)((uint)DAT_8009c679 << 0x18) < 0) goto LAB_800314e8;
    }
    else {
      bVar2 = 0x13;
      if ((char)DAT_8009c679 < '\n') {
LAB_800314e8:
        DAT_8009c679 = bVar2;
      }
    }
  }
  if ((DAT_8009c728 & 0x4000) != 0) {
    bVar1 = (char)DAT_8009c679 < '\n';
    DAT_8009c679 = DAT_8009c679 + 1;
    if (bVar1) {
      if ('\t' < (char)DAT_8009c679) {
        DAT_8009c679 = 0;
      }
    }
    else if ('\x13' < (char)DAT_8009c679) {
      DAT_8009c679 = 10;
    }
  }
  FUN_8003031c();
LAB_80031560:
  if ((DAT_8009c72c & 0x20) == 0) {
    if ((DAT_8009c72c & 0x100) == 0) {
      bVar2 = DAT_8009c673;
      if ((DAT_8009c72c & 0xc0) != 0) {
        bVar2 = DAT_8009c679 + 1;
      }
    }
    else {
      DAT_8009c678 = DAT_8009c678 ^ 1;
      FUN_80036184(1,DAT_8009c678 + 0xf,0x10,0x10,0x120,0xa0);
      FUN_800399f0(&DAT_800f08b4);
      bVar2 = DAT_8009c673;
    }
  }
  else {
    bVar2 = 0x14;
    if (DAT_8009c679 != 0x13) {
      DAT_8009c679 = 0x13;
      FUN_8003031c();
      bVar2 = DAT_8009c673;
    }
  }
  DAT_8009c673 = bVar2;
  return;
}

