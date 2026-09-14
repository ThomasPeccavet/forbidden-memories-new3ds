/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8007ca78(char param_1,undefined4 param_2)

{
  FUN_8007d174(param_1);
  DAT_80094cf8 = 0;
  DAT_80094cf4 = 0;
  if (((param_1 == '\x02') && (DAT_80094cb4 != '\x01')) &&
     ((DAT_80094cb4 != '\t' || ((_DAT_80094ce4 & 0xff00ff) == 0)))) {
    DAT_80094d00 = 1;
  }
  if ((DAT_80094cc8 & 0x10) != 0) {
    param_1 = '\x05';
  }
  if (DAT_80094ccc == 0x1f) {
    FUN_8007cb88(param_1,param_2);
  }
  else if (DAT_80094ccc == 0x20) {
    FUN_8007cd6c(param_1,param_2);
  }
  else {
    FUN_8007cff4(param_1,param_2);
  }
  if (DAT_80094cf4 == 0) {
    DAT_80094ccc = 0x21;
  }
  return;
}

