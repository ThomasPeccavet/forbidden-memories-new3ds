/* Analysis pseudo-C, not buildable source. */

void FUN_800247f0(void)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  
  puVar5 = &DAT_8017808c;
  FUN_80035ba0(&DAT_8017808c,&DAT_80177fe8,0xa0);
  FUN_8008f578(&DAT_8017808c,0x50,2,&LAB_800247c0);
  puVar3 = &DAT_80178130;
  uVar4 = 0;
  iVar2 = 0;
  do {
    uVar1 = *puVar5;
    if (uVar1 != uVar4) {
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
      uVar4 = (uint)uVar1;
    }
    iVar2 = iVar2 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar2 < 0x50);
  *puVar3 = 0xffff;
  iVar2 = FUN_80014e08(0,0,DAT_80178130 - 1,(uVar4 - DAT_80178130) + 1,&LAB_800246a8,0,0);
  *(ushort **)(iVar2 + 0x38) = &DAT_80178130;
  *(undefined2 **)(iVar2 + 0x3c) = &DAT_8015c424;
  DAT_8009c460 = *(uint *)(iVar2 + 0x2c) | 0x10;
  return;
}

