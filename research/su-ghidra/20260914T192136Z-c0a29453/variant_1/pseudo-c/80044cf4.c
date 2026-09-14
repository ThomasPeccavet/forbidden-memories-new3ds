/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_80044cf4(int param_1,int *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  if ((char)DAT_8009c7ca < '\0') {
    return 0xffffffff;
  }
  if (param_1 == 0) {
    FUN_8008b318(DAT_8009c7b0 != '\0');
  }
  else {
    uVar1 = FUN_8008b308(DAT_8009c7b0 != '\0');
    if ((uVar1 & 0xe) != 0) {
      return 0;
    }
  }
  switch((int)((DAT_8009c7ca - 1) * 0x1000000) >> 0x18) {
  case 0:
  case 1:
    iVar2 = FUN_80044ac4();
    if (iVar2 < 0) {
      return 0;
    }
    break;
  case 2:
  case 3:
    if (DAT_8009c7cd != 1) {
      if (1 < DAT_8009c7cd) {
LAB_80044e98:
        if (((DAT_8009c7cd == 2) && (DAT_8009c7bc != 0)) &&
           (DAT_8009c7cc = DAT_8009c7cc - 1, -1 < (int)((uint)DAT_8009c7cc << 0x18))) {
          DAT_8009c7cd = 1;
          return 0;
        }
        break;
      }
      if (DAT_8009c7cd != 0) break;
      iVar2 = FUN_80044ac4();
      if (iVar2 < 0) {
        return 0;
      }
      if (iVar2 != 0) goto LAB_80045068;
      DAT_8009c7cc = 0x14;
      DAT_8009c7cd = DAT_8009c7cd + 1;
    }
    DAT_8009c7b1 = DAT_8009c7b1 - 1;
    if (-1 < (int)((uint)DAT_8009c7b1 << 0x18)) {
      uVar5 = 0x8001;
      if (DAT_8009c7ca == 4) {
        uVar5 = 0x8002;
      }
      iVar2 = 10;
      while( true ) {
        iVar4 = FUN_80073e18(&DAT_800f3c30,uVar5);
        iVar2 = iVar2 + -1;
        if (iVar4 != -1) break;
        if (iVar2 < 0) {
          return 0;
        }
      }
      iVar2 = 10;
      do {
        iVar3 = FUN_80073e28(iVar4,DAT_8009c7ba,0);
        iVar2 = iVar2 + -1;
        if (iVar3 != -1) {
          FUN_80044204(&DAT_800f3c10);
          iVar2 = 10;
          goto LAB_80044f7c;
        }
      } while (-1 < iVar2);
LAB_80044fe4:
      FUN_80073e58(iVar4);
      return 0;
    }
    goto LAB_80045068;
  case 7:
    if (DAT_8009c7cd == 0) {
      iVar2 = FUN_80044ac4();
      if (iVar2 < 0) {
        return 0;
      }
      if (iVar2 != 0) goto LAB_80045068;
      if (0xf < (int)(_DAT_8009c7d4 + (uint)DAT_8009c7c8)) {
        DAT_8009c7bc = 7;
        break;
      }
      iVar2 = FUN_8004492c(DAT_8009c7b0,&DAT_800f3c30,DAT_8009c7c0,0);
      if (iVar2 != 0) {
        DAT_8009c7bc = 6;
        break;
      }
      DAT_8009c7b1 = 10;
      DAT_8009c7cd = DAT_8009c7cd + 1;
    }
    else if (DAT_8009c7cd != 1) break;
    iVar2 = 10;
    do {
      iVar4 = FUN_80073e18(&DAT_800f3c30,(uint)DAT_8009c7c8 << 0x10 | 0x200);
      iVar2 = iVar2 + -1;
      if (iVar4 != -1) {
        FUN_80073e58(iVar4);
        DAT_8009c7bc = 0;
        goto switchD_80044d98_caseD_4;
      }
    } while (-1 < iVar2);
    DAT_8009c7b1 = DAT_8009c7b1 - 1;
    if (0 < (int)((uint)DAT_8009c7b1 << 0x18)) {
      return 0;
    }
    DAT_8009c7bc = 2;
    break;
  case 10:
  case 0xb:
    if (DAT_8009c7cd == 1) {
LAB_80044e04:
      FUN_80044204(&DAT_800f3c20);
      FUN_8008b2f8();
      if (DAT_8009c7ca == 0xb) {
        FUN_8008b2e8(DAT_8009c7b0,DAT_8009c7ba,DAT_8009c7c4);
      }
      else {
        FUN_8008b2d8(DAT_8009c7b0,DAT_8009c7ba,DAT_8009c7c4);
      }
      DAT_8009c7cd = DAT_8009c7cd + 1;
      return 0;
    }
    if (1 < DAT_8009c7cd) goto LAB_80044e98;
    if (DAT_8009c7cd != 0) break;
    iVar2 = FUN_80044ac4();
    if (iVar2 < 0) {
      return 0;
    }
    if (iVar2 == 0) {
      DAT_8009c7b1 = 10;
      DAT_8009c7cd = DAT_8009c7cd + 1;
      goto LAB_80044e04;
    }
LAB_80045068:
    DAT_8009c7bc = 2;
  }
switchD_80044d98_caseD_4:
  *param_3 = DAT_8009c7bc;
  *param_2 = (int)(char)DAT_8009c7ca;
  DAT_8009c7ca = 0xff;
  return 1;
  while (-1 < iVar2) {
LAB_80044f7c:
    if (DAT_8009c7ca == 4) {
      iVar3 = FUN_80073e48(iVar4,DAT_8009c7c4,DAT_8009c7c8);
    }
    else {
      iVar3 = FUN_80073e38(iVar4,DAT_8009c7c4,DAT_8009c7c8);
    }
    iVar2 = iVar2 + -1;
    if (iVar3 == 0) {
      DAT_8009c7b1 = 0x14;
      DAT_8009c7cd = DAT_8009c7cd + 1;
      break;
    }
  }
  goto LAB_80044fe4;
}

