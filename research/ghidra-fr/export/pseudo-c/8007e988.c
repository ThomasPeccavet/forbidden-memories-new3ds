/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007e988(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  *DAT_80094e78 = 0;
  *DAT_80094e7c = 0x80;
  *DAT_80094e84 = 0x20943;
  *DAT_80094e80 = 0x1323;
  *DAT_80094e88 = *DAT_80094e88 | 0x8000;
  *DAT_80094e90 = param_1;
  *DAT_80094e94 = param_2 | 0x10000;
  do {
  } while ((*DAT_80094e78 & 0x40) == 0);
  *DAT_80094e8c = 0x11000000;
  uVar1 = *DAT_80094e8c;
  while ((uVar1 & 0x1000000) != 0) {
    uVar1 = *DAT_80094e8c;
  }
  *DAT_80094e80 = 0x1325;
  return 0;
}

