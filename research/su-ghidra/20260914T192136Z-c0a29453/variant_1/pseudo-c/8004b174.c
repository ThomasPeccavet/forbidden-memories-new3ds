/* Analysis pseudo-C, not buildable source. */

void FUN_8004b174(int param_1)

{
  int iVar1;
  undefined4 local_28;
  uint local_24;
  short local_20;
  short local_1e;
  
  if (*(char *)(param_1 + 0x11) == '\x0f') {
    iVar1 = FUN_80076358();
    if (iVar1 == 1) {
      FUN_80076158(0);
    }
    iVar1 = FUN_80076d78(0xffffffff);
    if (iVar1 != 0) {
      FUN_80076d28(0);
    }
    local_28 = 1;
    local_24 = (uint)*(byte *)(param_1 + 0x13);
    FUN_80076378(&local_28);
    iVar1 = FUN_80076d78(0xfffffffe);
    if (iVar1 != 0) {
      FUN_80076d28(1);
    }
    FUN_80076158(1);
    *(undefined1 *)(DAT_8009c7d8 + 0x844) = *(undefined1 *)(param_1 + 0x13);
  }
  else if (*(char *)(param_1 + 0x11) == '\x10') {
    local_28 = 6;
    local_20 = (ushort)*(byte *)(param_1 + 0x13) << 8;
    local_1e = (ushort)*(byte *)(param_1 + 0x13) << 8;
    FUN_80076378(&local_28);
    FUN_80076158(1);
    *(undefined1 *)(DAT_8009c7d8 + 0x845) = *(undefined1 *)(param_1 + 0x13);
  }
  return;
}

