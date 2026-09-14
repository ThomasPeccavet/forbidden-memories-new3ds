/* Analysis pseudo-C, not buildable source. */

void FUN_80074648(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 unaff_retaddr;
  
  DAT_800f7098 = unaff_retaddr;
  FUN_80073df8();
  iVar1 = (*(code *)&SUB_000000b0)();
  iVar3 = 9;
  puVar2 = (undefined4 *)(*(int *)(iVar1 + 0x16c) + 0x62c);
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_80074638();
  FUN_80073e08();
  return;
}

