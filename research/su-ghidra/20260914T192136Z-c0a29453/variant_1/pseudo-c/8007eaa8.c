/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007eaa8(undefined4 param_1,uint param_2)

{
  byte bVar1;
  
  *DAT_80094e98 = 0;
  *DAT_80094e9c = 0x80;
  *DAT_80094ea4 = 0x21020843;
  *DAT_80094ea0 = 0x1325;
  *DAT_80094ea8 = *DAT_80094ea8 | 0x8000;
  *DAT_80094eb0 = param_1;
  *DAT_80094eb4 = param_2 | 0x10000;
  bVar1 = *DAT_80094e98;
  while ((bVar1 & 0x40) == 0) {
    bVar1 = *DAT_80094e98;
  }
  *DAT_80094eac = 0x11400100;
  return 0;
}

