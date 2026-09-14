/* Analysis pseudo-C, not buildable source. */

void FUN_8003e5e4(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_10 [2];
  
  switch(DAT_8009c771 & 0xf) {
  case 0:
    if ((DAT_8009c771 & 0x80) != 0) {
      DAT_8009c771 = 1;
      if (DAT_8009c6d0 != '\0') {
        DAT_8009c771 = 9;
        return;
      }
      goto switchD_8003e614_caseD_1;
    }
    DAT_8009c771 = DAT_8009c771 | 0x80;
    uVar2 = 200;
    uVar3 = 0x20;
    goto LAB_8003e910;
  case 1:
switchD_8003e614_caseD_1:
    uVar2 = 0xd4;
    if ((DAT_8009c771 & 0x80) != 0) {
      switch(DAT_8009c748) {
      case 0:
      case 3:
        DAT_8009c771 = 2;
        return;
      case 1:
        goto switchD_8003e6f4_caseD_1;
      case 2:
      case 4:
        goto switchD_8003e6f4_caseD_2;
      default:
        return;
      }
    }
    DAT_8009c771 = DAT_8009c771 | 0x80;
    DAT_801bf8cc = (DAT_8009c74d >> 4) + 1;
    if ((DAT_8009c74e & 0x200) != 0) {
      uVar2 = 0xc0;
    }
    FUN_8003e5c0(uVar2,0);
    do {
      iVar1 = FUN_8008bc18(DAT_8009c74d);
    } while (iVar1 == 0);
    goto LAB_8003e794;
  case 2:
    iVar1 = FUN_8008ca00(DAT_8009c74d,&DAT_800f0cb0,&DAT_800f0a58,local_10,0,0xf);
    if (iVar1 != 0) {
      DAT_8009c771 = 6;
      return;
    }
    if (local_10[0] == 0) {
      DAT_8009c771 = 6;
      return;
    }
    DAT_8009c771 = 3;
  case 3:
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      FUN_8003e5c0(0xd5,0);
      FUN_8008c5c0(DAT_8009c74d,&DAT_800f0cb0,DAT_8009c75c,DAT_8009c754,DAT_8009c752);
LAB_8003e794:
      DAT_8009c74e = DAT_8009c74e | 0x1000;
      return;
    }
    switch(DAT_8009c748) {
    case 0:
      DAT_8009c771 = 7;
      iVar1 = FUN_8003d340(DAT_8009c75c);
      if (iVar1 != 0) {
        return;
      }
      DAT_8009c771 = 4;
      uVar2 = 0xbd;
      if ((DAT_8009c74e & 0x400) == 0) {
        DAT_8009c74e = DAT_8009c74e | 0x400;
        DAT_8009c771 = 4;
        return;
      }
      break;
    case 1:
switchD_8003e6f4_caseD_1:
      DAT_8009c771 = 5;
      return;
    case 2:
    case 3:
      DAT_8009c771 = 8;
      return;
    default:
      return;
    case 5:
switchD_8003e6f4_caseD_2:
      DAT_8009c771 = 6;
      return;
    }
    break;
  case 4:
    if ((DAT_8009c771 & 0x80) == 0) {
      DAT_8009c771 = DAT_8009c771 | 0x80;
      uVar2 = 0xbd;
      uVar3 = 0x10;
    }
    else {
      if ((DAT_8009c771 & 0x40) != 0) {
        if (DAT_8009c6d0 != '\0') {
          DAT_8009c771 = 9;
          return;
        }
        DAT_8009c754 = DAT_8009c754 + 0x680;
        DAT_8009c771 = 3;
        return;
      }
      DAT_8009c771 = DAT_8009c771 | 0x40;
      uVar2 = 0xbc;
      uVar3 = 0x20;
    }
    goto LAB_8003e910;
  case 5:
    uVar2 = 0xc1;
    break;
  case 6:
    uVar2 = 0xd3;
    break;
  case 7:
    DAT_8009c739 = 1;
    uVar2 = 0xd0;
    if ((DAT_8009c74e & 0x200) == 0) {
      DAT_8009c750 = 0;
      uVar3 = 0x18;
    }
    else {
      uVar3 = 8;
    }
    goto LAB_8003e910;
  case 8:
    uVar2 = 0xd3;
    break;
  case 9:
    DAT_8009c739 = 3;
    uVar2 = 199;
    break;
  default:
    goto switchD_8003e6f4_default;
  }
  uVar3 = 0x18;
LAB_8003e910:
  FUN_8003e5c0(uVar2,uVar3);
switchD_8003e6f4_default:
  return;
}

