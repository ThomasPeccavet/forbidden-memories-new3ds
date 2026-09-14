/* Analysis pseudo-C, not buildable source. */

void FUN_80032230(int param_1)

{
  int iVar1;
  
  DAT_801bf88c = *(undefined4 *)(param_1 + 0x5a9c);
  DAT_801bf890 = *(undefined4 *)(param_1 + 0x5aa0);
  iVar1 = FUN_800361d8(3,0xe,0x16,0x19,0x280,0x10,1);
  FUN_800399f0(iVar1);
  *(ushort *)(*(int *)(iVar1 + 0x28) + 8) = *(ushort *)(*(int *)(iVar1 + 0x28) + 8) & 0xfff7;
  return;
}

