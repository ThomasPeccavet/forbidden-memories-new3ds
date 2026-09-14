/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800417d0(int param_1,byte *param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_8008f708();
  uVar3 = (uint)*param_2;
  if (uVar3 == 0) {
    trap(0x1c00);
  }
  if ((uVar3 == 0xffffffff) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  uVar1 = *(ushort *)(param_2 + (iVar2 % (int)uVar3) * 2 + 1);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(uint *)(param_1 + 0x50) = *(int *)(param_1 + 0x54) + (uint)uVar1;
  return 1;
}

