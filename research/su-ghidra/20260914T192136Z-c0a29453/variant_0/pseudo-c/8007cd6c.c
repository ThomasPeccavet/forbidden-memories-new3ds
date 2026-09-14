/* Analysis pseudo-C, not buildable source. */

void FUN_8007cd6c(char param_1,undefined4 param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  
  if (DAT_80094cd4 == 0xc) {
    DAT_80094cd4 = 0xd;
  }
  if (param_1 != '\x02') {
    if ((DAT_80094cc8 & 0x10) != 0) {
      DAT_80094cd0 = 2;
      DAT_80094cd4 = 0xc;
      return;
    }
    if (DAT_80094cd4 - 0x10U < 2) {
      DAT_80094cd0 = 1;
      DAT_80094cd4 = 0xb;
      return;
    }
    return;
  }
  if (DAT_80094cd4 == 0xd) {
    if ((DAT_80094cc8 & 0x10) == 0) {
      DAT_80094cd0 = 2;
      DAT_80094cd4 = 0xe;
      DAT_80094cd8 = 0x15;
      DAT_80094cec = DAT_80094cec + 1;
      return;
    }
    return;
  }
  if (DAT_80094cd4 == 0xe) {
    if (DAT_80094cd8 == 0x15) {
      if ((DAT_80094cc8 & 0x10) == 0) {
        DAT_80094cd0 = 2;
        DAT_80094cd8 = 0x16;
        DAT_80094ce8 = 0;
        return;
      }
      return;
    }
    pcVar1 = DAT_800f7314;
    if (DAT_80094cd8 == 0x16) {
      if ((DAT_80094cc8 & 2) != 0) {
        DAT_80094cd0 = 2;
        DAT_80094cd8 = 0x17;
        return;
      }
      if (DAT_80094ce8 < 0x12d) {
        return;
      }
      DAT_80094cd0 = 3;
      if (DAT_800f7314 == (code *)0x0) {
        DAT_80094cd0 = 3;
        return;
      }
      uVar2 = 5;
    }
    else {
      if (DAT_80094cd8 == 0x17) {
        DAT_80094cd0 = 2;
        DAT_80094cd8 = 0x18;
        return;
      }
      if (DAT_80094cd8 != 0x18) {
        return;
      }
      if (DAT_80094cc8 != 2) {
        return;
      }
      DAT_80094cd0 = 1;
      DAT_80094cd4 = 0xb;
      DAT_80094cd8 = 0;
      if (DAT_800f7314 == (code *)0x0) {
        DAT_80094cd0 = 1;
        DAT_80094cd4 = 0xb;
        DAT_80094cd8 = 0;
        return;
      }
      uVar2 = 2;
    }
  }
  else {
    if (1 < DAT_80094cd4 - 0x10U) {
      return;
    }
    if (DAT_80094cfc != 0) {
      return;
    }
    if ((DAT_80094cc8 & 2) != 0) {
      return;
    }
    DAT_80094cd0 = 1;
    DAT_80094cd4 = 0xb;
    if ((DAT_800f7310 != (code *)0x0) && (DAT_80094cb0 != 0)) {
      (*DAT_800f7310)(5,param_2);
    }
    if (DAT_800f730c == (code *)0x0) {
      return;
    }
    uVar2 = 5;
    pcVar1 = DAT_800f730c;
    if (DAT_80094cb0 == 0) {
      return;
    }
  }
  (*pcVar1)(uVar2,param_2);
  return;
}

