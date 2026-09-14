/* Analysis pseudo-C, not buildable source. */

void FUN_8007af44(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  puVar3 = &DAT_800f71a8;
  DAT_800f7270 = 0;
  DAT_800f726c = 0;
  DAT_800f7268 = 0;
  do {
    iVar2 = 3;
    iVar1 = (int)puVar3 + 3;
    *puVar3 = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    do {
      *(undefined1 *)(iVar1 + 5) = 0;
      iVar2 = iVar2 + -1;
      iVar1 = iVar1 + -1;
    } while (-1 < iVar2);
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 6;
  } while (iVar4 < 8);
  return;
}

