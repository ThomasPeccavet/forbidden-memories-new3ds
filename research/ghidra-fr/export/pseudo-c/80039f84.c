/* Analysis pseudo-C, not buildable source. */

void FUN_80039f84(int param_1,undefined4 param_2)

{
  byte bVar1;
  
  bVar1 = FUN_8008f708();
  *(byte *)(param_1 + 0x12) = (bVar1 & 0x1f) + 8 | 0x80;
  bVar1 = FUN_8008f708();
  *(byte *)(param_1 + 0x12) = (bVar1 & 0x1f) + 0x20 | 0x80;
  *(undefined1 *)(param_1 + 0x11) = 4;
  FUN_80039d3c(param_1,param_2);
  return;
}

