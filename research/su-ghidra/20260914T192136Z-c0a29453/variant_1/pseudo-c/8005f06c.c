/* Analysis pseudo-C, not buildable source. */

code * FUN_8005f06c(int param_1)

{
  code *pcVar1;
  
  if (param_1 == 0x2000000) {
    pcVar1 = FUN_80089dc8;
  }
  else if (param_1 == 0x2000001) {
    pcVar1 = FUN_80089e58;
  }
  else {
    FUN_8008fa78(s_unsupported_IMAGE_primitive_0x_0_80011784);
    pcVar1 = (code *)&LAB_80089da8;
  }
  return pcVar1;
}

