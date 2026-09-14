/* Analysis pseudo-C, not buildable source. */

void FUN_80017674(void)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = &DAT_800eb2b8;
  iVar3 = 0;
  puVar1 = &DAT_800eb2c1;
  do {
    *(undefined4 *)(puVar1 + -5) = 0;
    *puVar2 = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 0xc;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 3;
  } while (iVar3 < 5);
  return;
}

