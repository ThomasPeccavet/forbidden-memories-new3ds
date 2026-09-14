/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003a528(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = (uint)*(ushort *)(param_1 + param_2 * 2);
  if (((uVar1 == 0) || (uVar1 = (uint)*(ushort *)(param_1 + uVar1 + param_3 * 2), uVar1 == 0)) ||
     (uVar2 = 1, *(short *)(param_1 + uVar1 + param_4 * 2) == 0)) {
    uVar2 = 0;
  }
  return uVar2;
}

