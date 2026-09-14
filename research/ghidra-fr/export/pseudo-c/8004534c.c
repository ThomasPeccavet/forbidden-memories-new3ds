/* Analysis pseudo-C, not buildable source. */

void FUN_8004534c(short param_1)

{
  if ((ushort)(param_1 - 1U) < 0x80) {
    *(char *)(DAT_8009c7e0 + 0x514) = -0x80 - (char)param_1;
    *(undefined1 *)(DAT_8009c7e0 + 0x515) = 0x80;
  }
  else if ((ushort)(param_1 + 0x80U) < 0x80) {
    *(undefined1 *)(DAT_8009c7e0 + 0x514) = 0x80;
    *(char *)(DAT_8009c7e0 + 0x515) = -0x80 - (char)param_1;
  }
  else {
    *(undefined1 *)(DAT_8009c7e0 + 0x514) = 0x80;
    *(undefined1 *)(DAT_8009c7e0 + 0x515) = 0x80;
  }
  FUN_8004527c((int)*(short *)(DAT_8009c7e0 + 0x510));
  return;
}

