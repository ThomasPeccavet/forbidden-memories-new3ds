/* Analysis pseudo-C, not buildable source. */

void FUN_8003e9a8(void)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auStack_20 [4];
  int local_1c;
  int local_18;
  undefined4 local_14;
  
  switch(DAT_8009c771 & 0xf) {
  case 0:
    if ((DAT_8009c771 & 0x80) != 0) {
      DAT_8009c771 = 1;
      if (DAT_8009c6d0 != '\0') {
        DAT_8009c771 = 0xc;
        return;
      }
      goto switchD_8003e9e4_caseD_1;
    }
    DAT_8009c771 = DAT_8009c771 | 0x80;
    uVar3 = 0xc9;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xca;
    }
    uVar4 = 0x20;
    goto LAB_8003f144;
  case 1:
switchD_8003e9e4_caseD_1:
    uVar3 = 0xd4;
    if ((DAT_8009c771 & 0x80) != 0) {
      switch(DAT_8009c748) {
      case 0:
      case 3:
        if ((DAT_8009c74e & 0x100) != 0) {
          DAT_8009c771 = 2;
          return;
        }
        DAT_8009c771 = 3;
        return;
      case 1:
        goto switchD_8003eac8_caseD_1;
      case 2:
switchD_8003eac8_default:
        DAT_8009c771 = 0xd;
        return;
      case 4:
        if ((DAT_8009c74e & 0x100) != 0) {
          DAT_8009c771 = 4;
          return;
        }
        if (DAT_8009c750 == '\0') {
          DAT_8009c771 = 0xe;
          return;
        }
        DAT_8009c771 = 4;
        return;
      default:
        return;
      }
    }
    DAT_8009c771 = DAT_8009c771 | 0x80;
    DAT_801bf8cc = (DAT_8009c74d >> 4) + 1;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xba;
    }
    FUN_8003e5c0(uVar3,0);
    do {
      iVar2 = FUN_8008bc18(0);
    } while (iVar2 == 0);
    goto LAB_8003f034;
  case 2:
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      DAT_8009c730 = 3;
      FUN_8008e408(0);
      return;
    }
    uVar3 = 0xb8;
    if ((DAT_8009c771 & 0x40) == 0) {
      iVar2 = FUN_8008f04c(1,auStack_20,&local_1c);
      if (iVar2 != 1) {
        return;
      }
      if (local_1c == 0) {
        FUN_8008e2a8(0,&local_18);
        iVar2 = FUN_8008f04c(0,auStack_20,&local_1c);
        uVar3 = 0xbb;
        if (iVar2 == 1) {
          uVar3 = 0xb9;
          if (local_18 == 0) {
            DAT_8009c771 = 3;
            return;
          }
          DAT_8009c771 = DAT_8009c771 | 0x40;
          uVar4 = 0x10;
          goto LAB_8003f144;
        }
      }
      else {
        DAT_8009c730 = DAT_8009c730 + -1;
        uVar3 = 0xbb;
        if (DAT_8009c730 != '\0') {
          FUN_8008e408(0);
          return;
        }
      }
    }
    break;
  case 3:
    iVar2 = FUN_8008ca00(0,s_UUUU__8009c2f0 + 4,&DAT_800f0a58,&local_14,0,0xf);
    if (iVar2 != 0) {
      DAT_8009c771 = 0xd;
      return;
    }
    iVar2 = FUN_80044a54(&DAT_800f0cb0,&DAT_800f0a58,local_14);
    if (-1 < iVar2) {
      DAT_8009c771 = 7;
      return;
    }
    if (((DAT_8009c74e & 0x100) == 0) && (DAT_8009c750 == '\0')) {
      DAT_8009c771 = 0xe;
      return;
    }
    iVar2 = FUN_80044a00(&DAT_800f0a58,local_14);
    uVar3 = 0xdb;
    if ((int)(uint)DAT_8009c768 <= iVar2) {
      DAT_8009c771 = 6;
      goto LAB_8003ee2c;
    }
    uVar4 = 0x18;
    DAT_801bf88c = 0xf - iVar2;
    DAT_801bf890 = (uint)DAT_8009c768;
    goto LAB_8003f144;
  case 4:
    bVar1 = DAT_8009c771 & 0x40;
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      uVar3 = 0xde;
      uVar4 = 0x10;
    }
    else {
      DAT_8009c771 = DAT_8009c771 | 0x40;
      if (bVar1 == 0) {
        uVar3 = 0xdf;
        uVar4 = 0x20;
      }
      else {
        if (DAT_8009c6d0 == '\0') {
          DAT_8009c771 = 0xc;
          return;
        }
        DAT_8009c771 = 5;
        uVar3 = 0xbe;
        uVar4 = 0;
      }
    }
    goto LAB_8003f144;
  case 5:
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      do {
        iVar2 = FUN_8008bc18(0);
      } while (iVar2 == 0);
      goto LAB_8003f034;
    }
    if (DAT_8009c740 != 2) {
      return;
    }
    switch(DAT_8009c748) {
    case 0:
      uVar3 = 0xc3;
      break;
    case 1:
      goto switchD_8003eac8_caseD_1;
    case 2:
      goto switchD_8003eac8_default;
    case 3:
      uVar3 = 0xc3;
      break;
    case 4:
      if ((DAT_8009c771 & 0x40) != 0) {
        DAT_8009c771 = 1;
        return;
      }
      DAT_8009c771 = DAT_8009c771 | 0x40;
      iVar2 = FUN_8008ce88(0);
      uVar3 = 0xdd;
      if (iVar2 == 0) {
        uVar3 = 0xbf;
        uVar4 = 0x10;
        goto LAB_8003f144;
      }
      break;
    default:
      goto switchD_8003eac8_default;
    }
    break;
  case 6:
LAB_8003ee2c:
    iVar2 = FUN_8008cd8c(0,&DAT_800f0cb0,DAT_8009c768);
    if (iVar2 != 0) {
      DAT_8009c771 = 0xb;
      return;
    }
    if ((DAT_8009c74e & 0x100) == 0) {
      DAT_8009c754 = 0;
      DAT_8009c75c = DAT_8009c75c + -0x200;
      DAT_8009c752 = DAT_8009c752 + 0x200;
    }
    goto LAB_8003efd8;
  case 7:
    bVar1 = DAT_8009c771 & 0x40;
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      if ((DAT_8009c74e & 0x100) != 0) {
        DAT_8009c771 = 8;
        return;
      }
      DAT_8009c730 = '\0';
      FUN_8008c5c0(0,&DAT_800f0cb0,&DAT_801dc000,DAT_8009c754,0x480);
      goto LAB_8003f034;
    }
    DAT_8009c771 = DAT_8009c771 | 0x40;
    if (bVar1 == 0) {
      if (DAT_8009c748 != 0) {
        if (DAT_8009c748 == 1) {
          DAT_8009c771 = 9;
          return;
        }
        DAT_8009c771 = 0xd;
        return;
      }
      if ((DAT_8009c750 == '\0') && (iVar2 = FUN_8003d484(DAT_8009c75c,&DAT_801dc000), iVar2 == 0))
      {
        if (DAT_8009c730 != '\0') {
          DAT_8009c771 = 0xe;
          return;
        }
        DAT_8009c730 = '\x01';
        DAT_8009c771 = DAT_8009c771 & 0xbf;
        FUN_8008c5c0(0,&DAT_800f0cb0,&DAT_801dc000,DAT_8009c754 + 0x680,0x480);
        goto LAB_8003f034;
      }
      uVar3 = 0xcf;
      uVar4 = 0x20;
      goto LAB_8003f144;
    }
    if (DAT_8009c6d0 != '\0') {
      DAT_8009c771 = 0xc;
      return;
    }
LAB_8003efd8:
    DAT_8009c771 = 8;
switchD_8003e9e4_caseD_8:
    bVar1 = DAT_8009c771 & 0x80;
    DAT_8009c771 = DAT_8009c771 | 0x80;
    if (bVar1 != 0) {
      if (DAT_8009c748 == 0) {
        DAT_8009c771 = 10;
        return;
      }
      if (DAT_8009c748 != 1) {
        DAT_8009c771 = 0xb;
        return;
      }
switchD_8003eac8_caseD_1:
      DAT_8009c771 = 9;
      return;
    }
    uVar3 = 0xd6;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xd7;
    }
    FUN_8003e5c0(uVar3,0);
    FUN_8008c7e0(0,&DAT_800f0cb0,DAT_8009c75c,DAT_8009c754,DAT_8009c752);
LAB_8003f034:
    DAT_8009c74e = DAT_8009c74e | 0x1000;
    return;
  case 8:
    goto switchD_8003e9e4_caseD_8;
  case 9:
    uVar3 = 0xd2;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xbb;
    }
    break;
  case 10:
    DAT_8009c739 = 1;
    uVar3 = 0xcc;
    if ((DAT_8009c74e & 0x100) == 0) {
      uVar3 = 0xd1;
      DAT_8009c750 = '\0';
      DAT_8009c73c = DAT_8009c73c + 1;
    }
    break;
  case 0xb:
    uVar3 = 0xd9;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xdc;
    }
    break;
  case 0xc:
    uVar3 = 0xcd;
    if ((DAT_8009c74e & 0x100) != 0) {
      uVar3 = 0xcb;
    }
    FUN_8003e5c0(uVar3,0x18);
    DAT_8009c739 = 3;
    return;
  case 0xd:
    uVar3 = 0xda;
    break;
  case 0xe:
    uVar3 = 0xce;
    break;
  default:
    goto switchD_8003eac8_default;
  }
  uVar4 = 0x18;
LAB_8003f144:
  FUN_8003e5c0(uVar3,uVar4);
switchD_8003eac8_default:
  return;
}

