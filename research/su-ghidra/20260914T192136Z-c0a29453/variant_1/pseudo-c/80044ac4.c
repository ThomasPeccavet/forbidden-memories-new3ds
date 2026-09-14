/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_80044ac4(void)

{
  if (DAT_8009c7b8 == 1) {
    if (DAT_8009c7bc == 0) {
      DAT_8009c7b1 = 10;
      DAT_8009c7b8 = 2;
      goto LAB_80044c3c;
    }
    if (DAT_8009c7bc != 2) {
      return DAT_8009c7bc;
    }
    DAT_8009c7b1 = DAT_8009c7b1 - 1;
    if ((int)((uint)DAT_8009c7b1 << 0x18) < 1) {
      return 2;
    }
  }
  else {
    if (1 < DAT_8009c7b8) {
      if (DAT_8009c7b8 != 2) {
        return DAT_8009c7bc;
      }
      if ((DAT_8009c7bc != 2) ||
         (DAT_8009c7b1 = DAT_8009c7b1 - 1, (int)((uint)DAT_8009c7b1 << 0x18) < 1)) {
        DAT_8009c7cb = DAT_8009c7cb | 0x80;
        if (DAT_8009c7bc == 0) {
          DAT_8009c7c0 = &DAT_800f3c50;
          FUN_8004492c(DAT_8009c7b0,&DAT_8009c300,&DAT_800f3c50,&DAT_8009c7b4);
          _DAT_8009c7d4 = FUN_80044a00(DAT_8009c7c0,DAT_8009c7b4);
        }
        if (DAT_8009c7bc != 3) {
          return DAT_8009c7bc;
        }
        DAT_8009c7bc = 4;
        return 4;
      }
LAB_80044c3c:
      FUN_80044204(&DAT_800f3c10);
      FUN_8008b2c8(DAT_8009c7b0);
      return -1;
    }
    if (DAT_8009c7b8 != 0) {
      return DAT_8009c7bc;
    }
    if (DAT_8009c7bc == 1) {
      if (DAT_8009c7b1 == 1) {
        DAT_8009c7b1 = DAT_8009c7b1 - 1;
        return 1;
      }
      DAT_8009c7b1 = DAT_8009c7b1 - 1;
      FUN_80044204(&DAT_800f3c10);
      FUN_8008b2b8(DAT_8009c7b0);
      return -1;
    }
    if (DAT_8009c7bc < 2) {
      if (DAT_8009c7bc != 0) {
        return DAT_8009c7bc;
      }
      if (((DAT_8009c7cb & 0x80) != 0) && (DAT_8009c7ca != '\b')) {
        return 0;
      }
      DAT_8009c7bc = 3;
    }
    else {
      if (DAT_8009c7bc == 2) {
        return 2;
      }
      if (DAT_8009c7bc != 3) {
        return DAT_8009c7bc;
      }
    }
    if (DAT_8009c7ca == '\x01') {
      return DAT_8009c7bc;
    }
    DAT_8009c7b1 = 10;
    DAT_8009c7b8 = 1;
  }
  FUN_80044204(&DAT_800f3c20);
  FUN_8008b328(DAT_8009c7b0);
  return -1;
}

