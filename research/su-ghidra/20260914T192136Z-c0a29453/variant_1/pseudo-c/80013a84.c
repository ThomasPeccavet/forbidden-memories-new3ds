/* Analysis pseudo-C, not buildable source. */

undefined4 *
FUN_80013a84(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  uint uVar1;
  
  uVar1 = DAT_8009c460 & 0xffffffdf;
  if (((DAT_8009c460 & 0x10) != 0) && ((DAT_8009c460 & 0x80000) != 0)) {
    DAT_8009c460 = uVar1;
    FUN_80014f2c();
    uVar1 = DAT_8009c460;
  }
  DAT_8009c460 = uVar1;
  DAT_800eb238 = param_3;
  DAT_800eb239 = param_4;
  DAT_800eb246 = 4;
  DAT_800eb224 = param_1;
  DAT_800eb234 = param_2;
  DAT_800eb22c = 0x80000;
  DAT_8009c460 = DAT_8009c460 | 0x20;
  return &DAT_800eb200;
}

