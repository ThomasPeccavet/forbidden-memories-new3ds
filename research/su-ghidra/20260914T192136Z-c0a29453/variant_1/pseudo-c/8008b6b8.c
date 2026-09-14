/* Analysis pseudo-C, not buildable source. */

void FUN_8008b6b8(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 unaff_retaddr;
  
  DAT_800ff690 = unaff_retaddr;
  FUN_80073df8();
  iVar1 = (*(code *)&SUB_000000b0)();
  iVar1 = *(int *)(iVar1 + 0x18);
  puVar2 = &DAT_8008b728;
  do {
    *(undefined4 *)(iVar1 + 0x70) = *puVar2;
    puVar2 = puVar2 + 1;
    iVar1 = iVar1 + 4;
  } while (puVar2 != (undefined4 *)0x8008b734);
  FUN_80074638();
  FUN_80073e08();
  return;
}

