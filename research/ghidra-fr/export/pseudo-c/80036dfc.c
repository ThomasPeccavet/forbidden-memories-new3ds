/* Analysis pseudo-C, not buildable source. */

undefined2 FUN_80036dfc(int param_1)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  puVar1 = (undefined2 *)*puVar2;
  *puVar2 = puVar1 + 1;
  return *puVar1;
}

