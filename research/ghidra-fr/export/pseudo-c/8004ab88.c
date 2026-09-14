/* Analysis pseudo-C, not buildable source. */

void FUN_8004ab88(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_8009c7d8;
  uVar2 = (&DAT_80011360)[param_1];
  *(undefined4 *)(DAT_8009c7d8 + 0x4c4) = 0x60100;
  *(undefined4 *)(iVar1 + 0x4c0) = uVar2;
  *(undefined2 *)(iVar1 + 0x4fa) = *(undefined2 *)(param_2 + 0x20);
  *(undefined2 *)(iVar1 + 0x4fc) = *(undefined2 *)(param_2 + 0x22);
  *(uint *)(iVar1 + 0x4e4) = (uint)*(ushort *)(param_2 + 0x24);
  FUN_800779e8(iVar1 + 0x4c0);
  return;
}

