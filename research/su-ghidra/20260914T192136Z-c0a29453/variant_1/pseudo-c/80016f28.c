/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80016f28(int param_1)

{
  undefined4 uVar1;
  
  if (((*(ushort *)(param_1 + 0x16) & 0x8000) == 0) ||
     (uVar1 = 1, (*(ushort *)(param_1 + 0x16) & 0x4000) != 0)) {
    uVar1 = 0;
  }
  return uVar1;
}

