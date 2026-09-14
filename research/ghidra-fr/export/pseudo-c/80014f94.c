/* Analysis pseudo-C, not buildable source. */

undefined4 *
FUN_80014f94(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  uint uVar1;
  
  uVar1 = DAT_8009c460 & 0xffffffdf;
  if (((DAT_8009c460 & 0x10) != 0) && ((DAT_8009c460 & 0x80000) != 0)) {
    DAT_8009c460 = uVar1;
    FUN_80014f2c();
    uVar1 = DAT_8009c460;
  }
  DAT_8009c460 = uVar1;
  FUN_800138b4(&DAT_800eb200,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  DAT_8009c460 = DAT_8009c460 | 0x20;
  return &DAT_800eb200;
}

