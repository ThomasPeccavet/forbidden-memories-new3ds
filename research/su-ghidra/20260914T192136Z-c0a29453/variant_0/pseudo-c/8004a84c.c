/* Analysis pseudo-C, not buildable source. */

int FUN_8004a84c(int param_1,byte param_2)

{
  short sVar1;
  
  if (param_2 < 0x40) {
    if (*(char *)(param_1 + 0x11) == '\0') {
      return 0;
    }
    sVar1 = -((ushort)*(byte *)(param_1 + 0x11) * 2 * (0x40 - (ushort)param_2));
  }
  else {
    if (param_2 == 0x40) {
      return 0;
    }
    if (*(char *)(param_1 + 0x10) == '\0') {
      return 0;
    }
    sVar1 = (ushort)*(byte *)(param_1 + 0x10) * 2 * (param_2 - 0x3f);
  }
  return (int)sVar1;
}

