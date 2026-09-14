/* Analysis pseudo-C, not buildable source. */

void FUN_8003f768(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((DAT_8009c74e & 0x800) != 0) {
    if (DAT_8009c764 == 0) {
      DAT_8009c74e = 0;
      return;
    }
    iVar1 = FUN_8003f5c4(DAT_8009c764,8,0x100,DAT_8009c73a);
    if (iVar1 != 0) {
      return;
    }
    FUN_800360d8(&DAT_800f0850 + (uint)DAT_8009c73a * 100);
    FUN_80040690(DAT_8009c764);
    DAT_8009c764 = 0;
    return;
  }
  if ((DAT_8009c74e & 0x4080) == 0x4080) {
    if ((DAT_8009c74e & 0x40) == 0) {
      DAT_8009c74e = DAT_8009c74e | 0x40;
      iVar1 = FUN_80036184(DAT_8009c73a,DAT_8009c757,8,0x50,0x130,0x30);
      FUN_8002e60c(iVar1);
      *(undefined1 *)(iVar1 + 0x59) = 0x10;
      if ((DAT_8009c74e & 0x20) != 0) {
        do {
          FUN_80039770();
        } while (*(int *)(iVar1 + 0x30) == 0);
        return;
      }
      if ((DAT_8009c74e & 0x10) != 0) {
        *(ushort *)(iVar1 + 0x34) = *(ushort *)(iVar1 + 0x34) | 0x1010;
        return;
      }
      FUN_800399f0(iVar1);
    }
    else {
      FUN_80039770(DAT_8009c74e,param_2,8);
      if ((*(uint *)(&DAT_800f0884 + (uint)DAT_8009c73a * 0x32) & 0x2010) != 0x2000) {
        return;
      }
    }
    if ((DAT_8009c74e & 8) == 0) {
      DAT_8009c74e = DAT_8009c74e & 0xff7f;
      return;
    }
    DAT_8009c74e = 0;
  }
  else {
    if ((DAT_8009c74e & 0x4000) == 0) {
      if ((DAT_8009c74e & 0x2000) == 0) {
        DAT_8009c74e = DAT_8009c74e | 0x2000;
        FUN_8008b7e4();
        FUN_8008ea18();
        DAT_8009c739 = 2;
        FUN_8003f69c();
        *(undefined2 *)(DAT_8009c764 + 0x60) = 0xfc00;
        return;
      }
      iVar1 = FUN_8003f5c4(DAT_8009c764,8,0x50,0xffffffff);
      if (iVar1 != 0) {
        return;
      }
      DAT_8009c74e = DAT_8009c74e | 0x4000;
      return;
    }
    if ((DAT_8009c74e & 0x1000) != 0) {
      DAT_8009c734 = FUN_8008cc70(1,&DAT_8009c740,&DAT_8009c748);
      if (DAT_8009c734 != 1) {
        return;
      }
      DAT_8009c74e = DAT_8009c74e & 0xefff;
      DAT_8009c734 = 1;
    }
    (*(code *)(&PTR_LAB_800923c8)[DAT_8009c770])();
    if (DAT_8009c74e != 0) {
      return;
    }
  }
  DAT_8009c74e = DAT_8009c74e | 0x800;
  *(undefined2 *)(DAT_8009c764 + 0x60) = 0x400;
  FUN_8008ea88();
  FUN_8008b854();
  return;
}

