/* Analysis pseudo-C, not buildable source. */

int FUN_80024a38(int param_1)

{
  if ((DAT_8009c6f9 != 0) && (param_1 < 0x14)) {
    return *(char *)((int)&PTR_LAB_80091de8 + (uint)DAT_8009c6f9 + param_1 * 6 + 3) * 10;
  }
  return 0;
}

