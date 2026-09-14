/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8002e650(void)

{
  if ((DAT_8009c610 & 0x8000) != 0) {
    return 1;
  }
  DAT_8009c610 = DAT_8009c610 | 0x8000;
  return 0;
}

