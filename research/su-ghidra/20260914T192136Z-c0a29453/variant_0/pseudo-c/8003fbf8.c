/* Analysis pseudo-C, not buildable source. */

int FUN_8003fbf8(undefined4 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  switch(DAT_8009c77a & 0xf) {
  case 0:
    if ((DAT_8009c77a & 0x80) == 0) {
      DAT_8009c77a = DAT_8009c77a | 0x80;
      FUN_8003f69c(param_1,8);
      bVar1 = DAT_8009c73a;
      *(undefined2 *)(DAT_8009c764 + 0x60) = 0xfc00;
      iVar4 = FUN_80036184(bVar1,0xc2,8,0x50,0x130,0x30);
      *(undefined1 *)(iVar4 + 0x59) = 0x10;
      FUN_800399f0();
    }
    iVar3 = FUN_8003f5c4(DAT_8009c764,8,0x50,DAT_8009c73a);
    iVar4 = 0;
    if (iVar3 == 0) {
      DAT_8009c77a = 1;
      iVar4 = 0;
    }
    break;
  case 1:
    if ((DAT_8009c72c & 0x20) == 0) {
      if ((DAT_8009c72c & 0x40) == 0) {
        return 0;
      }
      FUN_80040204(7);
      DAT_8009c77a = 2;
    }
    else {
      FUN_80040204(8);
      DAT_8009c77a = 0x82;
    }
    *(undefined2 *)(DAT_8009c764 + 0x60) = 0x400;
  default:
switchD_8003fc2c_caseD_4:
    iVar4 = 0;
    break;
  case 2:
    iVar3 = FUN_8003f5c4(DAT_8009c764,8,0x100,DAT_8009c73a);
    iVar4 = 0;
    if (iVar3 == 0) {
      FUN_800360d8(&DAT_800f0850 + (uint)DAT_8009c73a * 100);
      FUN_80040690(DAT_8009c764);
      DAT_8009c764 = 0;
      iVar4 = 2;
      if ((DAT_8009c77a & 0x80) == 0) {
        DAT_8009c77a = 3;
        FUN_8003fa7c(&DAT_801d1200,0x680,s_BESLES_03948_YUGIOH_80010304,1);
        iVar4 = 0;
      }
    }
    break;
  case 3:
    iVar4 = FUN_8003fa30();
    if ((iVar4 != 0) && (iVar4 == 1)) {
      if ((DAT_8009c77a & 0x40) == 0) {
        DAT_8009c77a = DAT_8009c77a | 0x40;
        FUN_8003fa7c(&DAT_801d2200,0x680,s_BESLES_03948_YUGIOH_80010304,1);
        iVar4 = 0;
        DAT_8009c74d = 0x10;
      }
      else {
        iVar4 = FUN_8003d454(&DAT_801d1200,&DAT_801d2200);
        if (iVar4 == 0) {
          iVar4 = 1;
        }
        else {
          DAT_8009c77a = 10;
          iVar4 = 0;
        }
      }
    }
    break;
  case 10:
    if ((DAT_8009c77a & 0x80) == 0) {
      DAT_8009c77a = DAT_8009c77a | 0xc0;
      FUN_8003f69c();
      uVar2 = DAT_8009c77b;
      bVar1 = DAT_8009c73a;
      *(undefined2 *)(DAT_8009c764 + 0x60) = 0xfc00;
      iVar4 = FUN_800361d8(bVar1,uVar2,8,0x50,0x130,0x30,0x1010);
      *(undefined1 *)(iVar4 + 0x59) = 0x10;
      do {
        FUN_80039770();
      } while ((*(ushort *)(iVar4 + 0x34) & 0x2000) == 0);
    }
    if ((DAT_8009c77a & 0x40) == 0) {
      FUN_80039770();
      iVar4 = 0;
      if (((&DAT_800f0884)[(uint)DAT_8009c73a * 0x32] & 0x10) == 0) {
        DAT_8009c77a = 0xb;
        iVar4 = 0;
      }
    }
    else {
      iVar3 = FUN_8003f5c4(DAT_8009c764,8,0x50,DAT_8009c73a);
      iVar4 = 0;
      if (iVar3 == 0) {
        DAT_8009c77a = DAT_8009c77a & 0xbf;
        iVar4 = 0;
      }
    }
    break;
  case 0xb:
    if ((DAT_8009c77a & 0x80) == 0) {
      DAT_8009c77a = DAT_8009c77a | 0x80;
      *(undefined2 *)(DAT_8009c764 + 0x60) = 0x400;
    }
    iVar4 = FUN_8003f5c4(DAT_8009c764,8,0x100,DAT_8009c73a);
    if (iVar4 == 0) {
      FUN_800360d8(&DAT_800f0850 + (uint)DAT_8009c73a * 100);
      FUN_80040690(DAT_8009c764);
      DAT_8009c764 = 0;
      return 2;
    }
    goto switchD_8003fc2c_caseD_4;
  }
  return iVar4;
}

