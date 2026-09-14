/* Analysis pseudo-C, not buildable source. */

void FUN_8007d0e0(undefined1 param_1,undefined4 param_2)

{
  FUN_8007d174(param_1);
  if ((DAT_80094cc8 & 0x10) != 0) {
    DAT_80094cd0 = 2;
    DAT_80094cd4 = 0xc;
  }
  if ((DAT_800f7310 != (code *)0x0) && (DAT_80094cb0 != 0)) {
    (*DAT_800f7310)(param_1,param_2);
  }
  return;
}

