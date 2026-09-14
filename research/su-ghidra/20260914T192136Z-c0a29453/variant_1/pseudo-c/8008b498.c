/* Analysis pseudo-C, not buildable source. */

void FUN_8008b498(void)

{
  int iVar1;
  undefined4 unaff_retaddr;
  
  DAT_800ff680 = unaff_retaddr;
  iVar1 = (*(code *)&SUB_000000b0)();
  *(undefined4 *)(*(int *)(iVar1 + 0x16c) + 0x1988) = 0;
  FUN_80074638();
  return;
}

