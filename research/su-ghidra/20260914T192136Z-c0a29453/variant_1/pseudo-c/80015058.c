/* Analysis pseudo-C, not buildable source. */

void FUN_80015058(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x28) + -0x800;
  *(int *)(param_1 + 0x28) = iVar1;
  if (iVar1 < 1) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
    if (*(int *)(param_1 + 0x20) != 0) {
      iVar1 = *(int *)(param_1 + 0x40);
      *(int *)(param_1 + 0x40) = iVar1 + 1;
      (**(code **)(param_1 + 0x20))(param_1,iVar1);
    }
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x1c);
  }
  return;
}

