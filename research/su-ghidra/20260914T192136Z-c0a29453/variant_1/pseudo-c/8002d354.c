/* Analysis pseudo-C, not buildable source. */

void seed_8002d354(void)

{
  int iVar1;
  
  FUN_80087838(0xa0,0x80);
  FUN_80087858(300);
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    DAT_8009c424 = 1;
    FUN_8005622c();
    FUN_80056540();
    if (DAT_800f09e0 == 0x309) {
      DAT_8009c60a = DAT_8009c60a | 0x20;
      FUN_8005cd2c();
    }
    else {
      FUN_800563b0(0,DAT_800f09e0 + -1,(int)DAT_800f09e2,(int)DAT_800f09e4,DAT_800f09e7,DAT_800f09e6
                  );
      FUN_800563b0(1,DAT_800f09e8 + -1,(int)DAT_800f09ea,(int)DAT_800f09ec,DAT_800f09ef,DAT_800f09ee
                  );
      FUN_800563b0(2,DAT_8009c6f9);
    }
    FUN_800158f4();
  }
  else {
    if ((DAT_8009c60a & 0x20) == 0) {
      iVar1 = FUN_80056620();
    }
    else {
      iVar1 = FUN_8005cd90();
    }
    if (iVar1 != 0) {
      FUN_80048354();
      FUN_80040258();
      DAT_8009c60a = DAT_8009c60d;
    }
    FUN_8005cdec();
  }
  return;
}

