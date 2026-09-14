/* Analysis pseudo-C, not buildable source. */

void FUN_800176ac(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = 0;
  do {
    puVar3 = (undefined4 *)((int)&DAT_800eb390 + iVar4);
    iVar2 = 0;
    puVar1 = &DAT_800eb3a4 + iVar4;
    do {
      *puVar3 = 0;
      *(undefined4 *)(puVar1 + -0x10) = 0;
      *(undefined4 *)(puVar1 + -0xc) = 0;
      puVar1[4] = 0;
      puVar1[-1] = 1;
      puVar1[3] = (char)iVar2;
      if (iVar2 == 3) {
        *puVar1 = 1;
      }
      else {
        *puVar1 = (char)iVar2;
      }
      puVar1 = puVar1 + 0x1c;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 7;
    } while (iVar2 < 4);
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + 0x70;
  } while (iVar5 < 2);
  DAT_800eb3a3 = 0;
  DAT_800eb413 = 0;
  return;
}

