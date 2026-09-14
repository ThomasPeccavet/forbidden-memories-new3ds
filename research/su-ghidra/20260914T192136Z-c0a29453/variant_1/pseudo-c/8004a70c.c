/* Analysis pseudo-C, not buildable source. */

void FUN_8004a70c(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = DAT_8009c7d8;
  uVar1 = *(ushort *)(DAT_8009c7d8 + 0x514);
  uVar2 = *(ushort *)(DAT_8009c7d8 + 0x516);
  *(undefined2 *)(DAT_8009c7d8 + 0x4cc) = 0;
  *(undefined2 *)(iVar3 + 0x4ce) = 0;
  uVar4 = (&DAT_80011360)[param_1];
  *(undefined4 *)(iVar3 + 0x4c4) = 0xf;
  *(undefined4 *)(iVar3 + 0x4c0) = uVar4;
  *(short *)(iVar3 + 0x4c8) = (short)((int)(param_2 * (uint)uVar1) >> 7);
  *(short *)(iVar3 + 0x4ca) = (short)((int)(param_3 * (uint)uVar2) >> 7);
  FUN_800779e8(iVar3 + 0x4c0);
  return;
}

