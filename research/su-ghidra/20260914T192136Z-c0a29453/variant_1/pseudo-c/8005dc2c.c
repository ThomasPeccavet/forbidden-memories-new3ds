/* Analysis pseudo-C, not buildable source. */

code * FUN_8005dc2c(uint param_1)

{
  if ((param_1 & 0xffff0000) == 0x3000000) {
    if ((param_1 & 0xffff) == 0x2019) {
      return FUN_8005e3d8;
    }
    if ((param_1 & 0xffff) == 0x2119) {
      return FUN_8005e860;
    }
  }
  FUN_8008fa78(s_unsupported_ANIMATION_interpolat_80011720);
  return (code *)&LAB_80089da8;
}

