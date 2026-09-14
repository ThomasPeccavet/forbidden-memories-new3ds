/* Analysis pseudo-C, not buildable source. */

void FUN_80038ba8(int param_1)

{
  uint uVar1;
  uint *puVar2;
  
  uVar1 = FUN_80036dfc();
  puVar2 = (uint *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  *puVar2 = *puVar2 & 0xffff0000 | uVar1 & 0xffff;
  return;
}

