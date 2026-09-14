/* Analysis pseudo-C, not buildable source. */

void FUN_8002e9c0(void)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_8002e650();
  if (iVar2 == 0) {
    DAT_8009c838 = 0;
    DAT_8009c83a = 0;
    DAT_8009c83c = 0x140;
    DAT_8009c83e = 0xa0;
    if (DAT_8009c455 == '\0') {
      DAT_8009c838 = 0x140;
    }
    FUN_8007ffd0(&DAT_8009c838,0x1c0,0x100);
  }
  else if (((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) && ((DAT_800eb24e & 0x80) == 0)) {
    uVar1 = DAT_8009c610 & 0x2000;
    if ((DAT_8009c610 & 0x4000) == 0) {
      DAT_8009c610 = DAT_8009c610 | 0x4000;
      uVar3 = FUN_80040390();
      iVar2 = FUN_800403d0(uVar3,3);
      FUN_80040844(iVar2,0,0,0x140,0xa0,0,0,0x17,0x280,0xd4);
      DAT_8009c63c = iVar2;
      *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x2000000;
      FUN_8002e2a4(&DAT_800ec220);
      DAT_8009c4c0 = DAT_8009c62a;
      DAT_8009c4c2 = DAT_8009c62c;
      if (DAT_8009c4c5 == '\0') {
        FUN_80015ba0();
      }
      FUN_8002e11c(&DAT_800ec220,DAT_8009c630 & 0xfff);
    }
    else {
      DAT_8009c610 = DAT_8009c610 | 0x2000;
      if (uVar1 == 0) {
        FUN_80040690(DAT_8009c63c);
        FUN_8002e3c0(&DAT_800ec220,0xffffffff);
        if ((DAT_8009c4c5 == '\0') && ((DAT_8009c630 & 0x4000) == 0)) {
          FUN_80015b28();
        }
      }
      else {
        DAT_8009c610 = 0;
      }
    }
  }
  return;
}

