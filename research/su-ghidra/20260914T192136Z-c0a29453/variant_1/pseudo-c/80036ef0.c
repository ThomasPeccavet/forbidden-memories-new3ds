/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80036f38) */

void FUN_80036ef0(int param_1)

{
  int iVar1;
  
  iVar1 = 0xc0c0;
  if (((int)(uint)DAT_8009c6a8 >> ((int)DAT_8009c6d0 & 0x1fU) & 1U) == 0) {
    iVar1 = 0xc0;
  }
  *(int *)(*(int *)(param_1 + 0x30) + 0xc) = iVar1;
  *(int *)(*(int *)(param_1 + 0x30) + 0x3c) = iVar1;
  *(int *)(*(int *)(param_1 + 0x30) + 0x44) = iVar1;
  iVar1 = iVar1 >> 2;
  *(int *)(*(int *)(param_1 + 0x30) + 0x2c) = iVar1;
  *(int *)(*(int *)(param_1 + 0x30) + 0x34) = iVar1;
  *(int *)(*(int *)(param_1 + 0x30) + 0x4c) = iVar1;
  *(int *)(*(int *)(param_1 + 0x30) + 0x54) = iVar1;
  FUN_80036e7c();
  return;
}

