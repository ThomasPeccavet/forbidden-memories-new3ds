/* Analysis pseudo-C, not buildable source. */

void FUN_800389ac(int param_1)

{
  uint uVar1;
  int *piVar2;
  uint *puVar3;
  
  piVar2 = (int *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  *piVar2 = *piVar2 + (uint)DAT_8009c6d1 * 2;
  uVar1 = FUN_80036dfc(param_1);
  puVar3 = (uint *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  *puVar3 = *puVar3 & 0xffff0000 | uVar1 & 0xffff;
  return;
}

