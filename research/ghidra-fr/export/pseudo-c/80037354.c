/* Analysis pseudo-C, not buildable source. */

void FUN_80037354(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined *puVar1;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(param_1 + 0x5e);
  if (uVar2 != 0) {
    puVar1 = &DAT_800ec3a3 + (uint)*(ushort *)(param_1 + 0x5c) * 0x16;
    do {
      uVar2 = uVar2 - 1;
      if ((puVar1[-4] & 0x80) == 0) {
        return;
      }
      puVar1[-2] = param_2;
      *puVar1 = param_3;
      puVar1 = puVar1 + 0x16;
    } while (uVar2 != 0);
  }
  return;
}

