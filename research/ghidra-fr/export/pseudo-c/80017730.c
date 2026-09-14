/* Analysis pseudo-C, not buildable source. */

void FUN_80017730(void)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = &DAT_801a7ad8;
  iVar3 = 0;
  puVar1 = &DAT_801a7aee;
  do {
    *puVar2 = 0;
    *(undefined4 *)(puVar1 + -9) = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 0xe;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 7;
  } while (iVar3 < 0x1e);
  return;
}

