/* Analysis pseudo-C, not buildable source. */

void FUN_8003cd78(void)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  
  iVar3 = 1;
  puVar6 = &DAT_8009c712;
  puVar5 = &DAT_8009c72e;
  puVar4 = &DAT_8009c72a;
  do {
    *puVar4 = 0;
    uVar1 = *puVar4;
    puVar4 = puVar4 + -1;
    iVar3 = iVar3 + -1;
    *puVar5 = uVar1;
    uVar1 = *puVar5;
    puVar5 = puVar5 + -1;
    *puVar6 = uVar1;
    puVar6 = puVar6 + -1;
  } while (-1 < iVar3);
  iVar3 = 0x1f;
  do {
    puVar2 = (undefined1 *)(iVar3 + -0x7ff0f610);
    iVar3 = iVar3 + -1;
    *puVar2 = 0;
  } while (-1 < iVar3);
  DAT_8009c720 = 0;
  DAT_8009c714 = 0;
  DAT_8009c718 = 0;
  DAT_8009c70c = 0;
  return;
}

