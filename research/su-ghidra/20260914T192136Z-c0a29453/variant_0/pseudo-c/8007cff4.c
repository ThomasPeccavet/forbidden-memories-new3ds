/* Analysis pseudo-C, not buildable source. */

void FUN_8007cff4(char param_1)

{
  if ((param_1 == '\x02') && (DAT_80094cb4 == '\x0e')) {
    if (((DAT_80094cdd ^ DAT_80094cb5) & 0x80) != 0) {
      DAT_80094cd4 = 0xf;
      DAT_80094cf0 = 3;
      DAT_80094cd0 = 2;
    }
    DAT_80094cdd = DAT_80094cb5;
  }
  if (param_1 == '\x05') {
    if ((DAT_80094cc8 & 0x10) == 0) {
      DAT_80094cd0 = 1;
      DAT_80094cd4 = 0xb;
    }
    else {
      DAT_80094cd0 = 2;
      DAT_80094cd4 = 0xc;
      if ((DAT_800f730c != (code *)0x0) && (DAT_80094cb0 != 0)) {
        (*DAT_800f730c)(5);
      }
    }
  }
  return;
}

