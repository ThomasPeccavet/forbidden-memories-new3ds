/* Analysis pseudo-C, not buildable source. */

void FUN_800745c0(void)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_retaddr;
  
  DAT_800f7088 = unaff_retaddr;
  FUN_80073df8();
  iVar1 = (*(code *)&SUB_000000b0)();
  iVar1 = *(int *)(iVar1 + 0x16c);
  iVar2 = 0xb;
  DAT_800f7090 = iVar1 + 0x884;
  DAT_800f7094 = iVar1 + 0x894;
  do {
    *(undefined4 *)(iVar1 + 0x594) = 0;
    iVar1 = iVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  FUN_80074638();
  return;
}

