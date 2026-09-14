/* Analysis pseudo-C, not buildable source. */

void FUN_800376b4(int param_1)

{
  *(undefined1 *)(param_1 + 0x51) = 0;
  DAT_8009c62a = FUN_80036dfc();
  DAT_8009c62c = FUN_80036dfc(param_1);
  DAT_8009c612 = FUN_80036dfc(param_1);
  if (0xfff < DAT_8009c62c) {
    DAT_8009c62c = DAT_8009c62c + -0x1000;
    *(undefined1 *)(param_1 + 0x51) = 10;
  }
  DAT_8009c6d2 = 7;
  DAT_8009c610 = 7;
  return;
}

