/* Analysis pseudo-C, not buildable source. */

void FUN_80047ef8(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0x100000;
  uVar3 = 0;
  iVar2 = 0;
  iVar1 = DAT_8009c7e0;
  do {
    if (*(ushort *)(DAT_8009c7e0 + 4) <= *(ushort *)(iVar1 + 0x404)) {
      uVar3 = uVar3 | uVar4;
    }
    uVar4 = uVar4 << 1;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 2;
  } while (iVar2 < 4);
  FUN_80077468(0,uVar3);
  return;
}

