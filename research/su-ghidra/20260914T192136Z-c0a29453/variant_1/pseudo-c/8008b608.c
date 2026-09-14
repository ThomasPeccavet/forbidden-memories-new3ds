/* Analysis pseudo-C, not buildable source. */

void FUN_8008b608(void)

{
  int iVar1;
  code *pcVar2;
  undefined4 unaff_retaddr;
  
  DAT_800ff680 = unaff_retaddr;
  FUN_80073df8();
  iVar1 = (*(code *)&SUB_000000b0)();
  iVar1 = *(int *)(iVar1 + 0x16c);
  pcVar2 = (code *)&DAT_8008b560;
  do {
    *(undefined4 *)(iVar1 + 0x9c8) = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    iVar1 = iVar1 + 4;
  } while (pcVar2 != FUN_8008b574);
  FUN_80074638();
  return;
}

