/* Analysis pseudo-C, not buildable source. */

undefined4 *
FUN_80014e08(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  if (DAT_8009c4a8 == (code *)0x0) {
    if ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0) {
      return (undefined4 *)0x0;
    }
  }
  else {
    (*DAT_8009c4a8)();
  }
  FUN_800138b4(&DAT_800eb1b8,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return &DAT_800eb1b8;
}

