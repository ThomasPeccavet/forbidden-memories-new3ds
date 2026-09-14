/* Analysis pseudo-C, not buildable source. */

void FUN_8003a22c(void)

{
  undefined *puVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 2;
  puVar1 = &DAT_800ec340;
  do {
    iVar4 = 2;
    puVar3 = (undefined4 *)(puVar1 + 8);
    puVar1[0x30] = 0xff;
    puVar1[0x32] = 0;
    puVar1[0x3a] = 0;
    puVar1[0x3b] = 0;
    do {
      *puVar3 = 0;
      puVar3[3] = 0;
      puVar3[6] = 0;
      puVar3[9] = 0;
      iVar4 = iVar4 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar4);
    iVar5 = iVar5 + -1;
    puVar1 = puVar1 + -0x4c;
  } while (-1 < iVar5);
  iVar5 = 4;
  puVar2 = &DAT_8015c414;
  do {
    *puVar2 = 0xff;
    iVar5 = iVar5 + -1;
    puVar2 = puVar2 + -1;
  } while (-1 < iVar5);
  return;
}

