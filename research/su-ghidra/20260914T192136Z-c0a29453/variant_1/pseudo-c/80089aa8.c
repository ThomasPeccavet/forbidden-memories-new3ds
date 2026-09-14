/* Analysis pseudo-C, not buildable source. */

void FUN_80089aa8(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined4 unaff_retaddr;
  
  DAT_800ff5e0 = unaff_retaddr;
  FUN_80073df8();
  iVar1 = (*(code *)&SUB_000000b0)();
  piVar2 = (int *)(*(int *)(iVar1 + 0x18) + 0x28);
  piVar3 = &DAT_80089b54;
  piVar4 = piVar2;
  do {
    iVar1 = *piVar3;
    iVar5 = *piVar4;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
    if (iVar1 != iVar5) goto LAB_80089b30;
  } while (piVar3 != &DAT_80089b6c);
  piVar4 = &DAT_80089b6c;
  do {
    *piVar2 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar2 = piVar2 + 1;
  } while (piVar4 != (int *)0x80089b84);
LAB_80089b30:
  FUN_80074638();
  FUN_80073e08();
  return;
}

