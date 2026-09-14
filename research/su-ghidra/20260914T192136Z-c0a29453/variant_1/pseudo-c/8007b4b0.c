/* Analysis pseudo-C, not buildable source. */

void FUN_8007b4b0(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  (&DAT_800f7278)[DAT_800f72f8 * 4] = param_1;
  (&DAT_800f727c)[DAT_800f72f8 * 0x10] = param_2;
  FUN_8007d304(DAT_800f72f8 * 0x10 + -0x7ff08d83,param_3);
  DAT_800f72f8 = DAT_800f72f8 + 1;
  if (7 < DAT_800f72f8) {
    DAT_800f72f8 = 0;
  }
  return;
}

