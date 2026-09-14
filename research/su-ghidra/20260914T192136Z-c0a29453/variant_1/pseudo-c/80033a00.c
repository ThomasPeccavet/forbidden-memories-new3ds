/* Analysis pseudo-C, not buildable source. */

int FUN_80033a00(int param_1)

{
  param_1 = param_1 + ((int)*(short *)(param_1 + 0x2d3c) + (int)*(char *)(param_1 + 0x2d48)) * 0x10;
  if (*(char *)(param_1 + 0xd) != '\0') {
    return (int)*(short *)(param_1 + 4);
  }
  return 0;
}

