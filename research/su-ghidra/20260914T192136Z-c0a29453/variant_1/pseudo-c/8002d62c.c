/* Analysis pseudo-C, not buildable source. */

void FUN_8002d62c(undefined4 param_1)

{
  DAT_8009c60c = 1;
  DAT_8009c60e = (undefined1)param_1;
  switch(param_1) {
  case 0:
    FUN_8003bef4();
    FUN_8016a850();
    DAT_801d07dc = 0x30;
    DAT_8009c638 = 0x30;
    DAT_8009c750 = 1;
    DAT_8009c435 = 0;
    DAT_8009c60a = 2;
    break;
  default:
    DAT_8009c60a = 0;
    break;
  case 2:
    DAT_8009c60a = 0x10;
    break;
  case 3:
    DAT_8009c60a = 0xe;
    break;
  case 4:
    DAT_8009c60a = 0xb;
    goto LAB_8002d738;
  case 5:
    DAT_8009c60a = 2;
    DAT_8009c638 = (undefined1)DAT_801d07dc;
    break;
  case 6:
    DAT_8009c6fb = 0;
    DAT_8009c60a = 6;
    break;
  case 7:
    FUN_80034190();
    DAT_8009c60c = 0;
    break;
  case 8:
    DAT_8009c60a = 4;
    break;
  case 9:
    DAT_8009c60a = 10;
LAB_8002d738:
    DAT_8009c60c = 0;
  }
  return;
}

