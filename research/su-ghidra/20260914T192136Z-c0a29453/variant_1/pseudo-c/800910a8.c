/* Analysis pseudo-C, not buildable source. */

void FUN_800910a8(int param_1)

{
  if (param_1 == 0) {
    *DAT_8009b44c = 0x80000000;
    *DAT_8009b420 = 0;
    *DAT_8009b42c = 0;
    *DAT_8009b44c = 0x60000000;
    FUN_80091198(&DAT_8009b308,0x20);
    FUN_80091198(&DAT_8009b38c,0x20);
  }
  else if (param_1 == 1) {
    *DAT_8009b44c = 0x80000000;
    *DAT_8009b420 = 0;
    *DAT_8009b42c = 0;
    *DAT_8009b44c = 0x60000000;
  }
  else {
    FUN_8008fa78(s_MDEC_rest_bad_option__d__8001287c);
  }
  return;
}

