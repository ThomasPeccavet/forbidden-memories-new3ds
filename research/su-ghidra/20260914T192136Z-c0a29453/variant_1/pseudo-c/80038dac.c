/* Analysis pseudo-C, not buildable source. */

void FUN_80038dac(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_80036dfc();
  *(uint *)(param_1 + (*(char *)(param_1 + 0x58) + 1) * 4) =
       *(uint *)(param_1 + *(char *)(param_1 + 0x58) * 4) & 0xffff0000 | uVar1 & 0xffff;
  *(char *)(param_1 + 0x58) = *(char *)(param_1 + 0x58) + '\x01';
  return;
}

