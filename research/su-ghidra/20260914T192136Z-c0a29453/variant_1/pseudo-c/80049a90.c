/* Analysis pseudo-C, not buildable source. */

byte FUN_80049a90(byte param_1)

{
  if (0x14 < param_1) {
    return 0xff;
  }
  if (param_1 != 0) {
    *(ushort *)(DAT_8009c7d8 + 0x510) = (ushort)param_1;
    return param_1;
  }
  return 0xff;
}

