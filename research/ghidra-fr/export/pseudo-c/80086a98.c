/* Analysis pseudo-C, not buildable source. */

int FUN_80086a98(uint param_1)

{
  int local_10;
  undefined1 auStack_c [4];
  
  if (0x3ff < param_1) {
    if (0x3ff < param_1 - 0x400) {
      if (param_1 - 0x800 < 0x400) {
        FUN_80086978(param_1 - 0x800,&local_10,auStack_c);
        return -local_10;
      }
      if (0x3ff < param_1 - 0xc00) {
        return 0;
      }
      FUN_80086978(0xfff - param_1,&local_10,auStack_c);
      return -local_10;
    }
    param_1 = 0x7ff - param_1;
  }
  FUN_80086978(param_1,&local_10,auStack_c);
  return local_10;
}

