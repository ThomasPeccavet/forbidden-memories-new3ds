/* Analysis pseudo-C, not buildable source. */

void FUN_8002c76c(void)

{
  undefined2 *puVar1;
  int iVar2;
  
  DAT_8009c5f8 = 0;
  iVar2 = 8;
  puVar1 = &DAT_800ec128;
  do {
    *(undefined1 *)(puVar1 + 2) = 0;
    *puVar1 = 0xffff;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x10;
  } while (iVar2 != 0);
  return;
}

