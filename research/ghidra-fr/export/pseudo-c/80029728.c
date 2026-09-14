/* Analysis pseudo-C, not buildable source. */

void FUN_80029728(void)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  
  uVar3 = 0;
  puVar4 = &DAT_800eb570;
  do {
    uVar1 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar1,2);
    FUN_80040800(iVar2,8,((int)uVar3 >> 1) * 0xb2 + 8,0,3,uVar3,0x19,0x106);
    if ((uVar3 & 1) != 0) {
      *(undefined2 *)(iVar2 + 0x30) = 0xa8;
    }
    uVar3 = uVar3 + 1;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x1000000;
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) & 0xfff7;
    FUN_80042c6c(iVar2);
    FUN_80042c1c(iVar2,0);
    *(int *)(puVar4 + 0x24) = iVar2;
    puVar4 = puVar4 + 4;
  } while ((int)uVar3 < 8);
  return;
}

