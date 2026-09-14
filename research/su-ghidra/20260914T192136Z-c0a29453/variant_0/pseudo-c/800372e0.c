/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800372e0(int param_1)

{
  char *pcVar1;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(param_1 + 0x5e);
  if (uVar2 != 0) {
    pcVar1 = &DAT_800ec3a1 + (uint)*(ushort *)(param_1 + 0x5c) * 0x16;
    do {
      if ((pcVar1[-2] & 0x80U) == 0) {
        return 0;
      }
      uVar2 = uVar2 - 1;
      if (*pcVar1 != '\0') {
        return 1;
      }
      pcVar1 = pcVar1 + 0x16;
    } while (uVar2 != 0);
  }
  return 0;
}

