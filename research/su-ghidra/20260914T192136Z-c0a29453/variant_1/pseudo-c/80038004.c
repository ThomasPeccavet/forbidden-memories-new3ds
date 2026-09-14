/* Analysis pseudo-C, not buildable source. */

void FUN_80038004(int param_1)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  puVar2 = (undefined1 *)*puVar3;
  uVar1 = *puVar2;
  *puVar3 = puVar2 + 1;
  FUN_80037f94(param_1,uVar1);
  return;
}

