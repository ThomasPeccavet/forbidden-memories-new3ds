/* Analysis pseudo-C, not buildable source. */

void FUN_800406b4(void)

{
  undefined *puVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  
  iVar2 = 0;
  puVar4 = &DAT_800f11d0;
  puVar3 = &DAT_800f11c0;
  DAT_8009c7a4 = 0;
  DAT_8009c7a6 = 0;
  do {
    *puVar3 = 0xffff;
    *puVar4 = 0xffff;
    puVar4 = puVar4 + 1;
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar2 < 7);
  puVar1 = &DAT_800f1210;
  iVar2 = 0x5f;
  do {
    *(undefined2 *)(puVar1 + 8) = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x70;
  } while (-1 < iVar2);
  return;
}

