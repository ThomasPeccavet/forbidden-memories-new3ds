/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8007cb88(char param_1,undefined4 param_2)

{
  if (param_1 == '\x02') {
    if (DAT_80094cb4 == '\x0e') {
      if (((DAT_80094cdd ^ DAT_80094cb5) & 0x80) == 0) {
        DAT_80094cd0 = 1;
        DAT_80094cd4 = 0xb;
      }
      else {
        DAT_80094cd4 = 0xf;
        DAT_80094cd0 = 2;
        DAT_80094cf0 = 3;
      }
      DAT_80094cdd = DAT_80094cb5;
    }
    else {
      if (DAT_80094cb4 == '\x03') {
        DAT_80094cd4 = 0x10;
      }
      else {
        if ((DAT_80094cb4 != '\x06') && (DAT_80094cb4 != '\x1b')) {
          switch(DAT_80094cb4) {
          case '\x02':
            DAT_80094cde = _DAT_80094cb5;
            break;
          case '\x03':
          case '\x06':
            DAT_80094ce3 = DAT_80094cb4;
            break;
          case '\x15':
          case '\x16':
            DAT_80094ce2 = DAT_80094cb4;
          }
          DAT_80094cd0 = 1;
          DAT_80094cd4 = 0xb;
          goto LAB_8007cd20;
        }
        DAT_80094cd4 = 0x11;
      }
      DAT_80094cd0 = 2;
      DAT_80094ce3 = DAT_80094cb4;
      DAT_80094cfc = 0x4b0;
    }
  }
  else {
    DAT_80094cd4 = 0xc;
    if ((DAT_80094cc8 & 0x10) == 0) {
      DAT_80094cd0 = 1;
      DAT_80094cd4 = 0xb;
    }
    else {
      DAT_80094cd0 = 2;
    }
  }
LAB_8007cd20:
  if ((DAT_800f730c != (code *)0x0) && (DAT_80094cb0 != 0)) {
    (*DAT_800f730c)(param_1,param_2);
  }
  return;
}

