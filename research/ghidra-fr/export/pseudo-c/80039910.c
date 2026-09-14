/* Analysis pseudo-C, not buildable source. */

void FUN_80039910(int param_1,short param_2,short param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x28);
  *(short *)(param_1 + 0x3c) = param_2;
  *(short *)(param_1 + 0x40) = param_3;
  if (iVar1 != 0) {
    *(short *)(iVar1 + 0x30) = param_2;
    *(short *)(iVar1 + 0x32) = param_3;
  }
  iVar1 = *(int *)(param_1 + 0x2c);
  if (iVar1 != 0) {
    if (*(short *)(iVar1 + 0x1e) == 4) {
      FUN_80039148(param_1);
    }
    else {
      *(short *)(iVar1 + 0x30) = param_2;
      *(short *)(iVar1 + 0x32) = param_3;
    }
  }
  iVar1 = *(int *)(param_1 + 0x30);
  if (iVar1 != 0) {
    if (*(short *)(iVar1 + 0x1e) == 4) {
      FUN_80036e7c(param_1);
    }
    else {
      *(short *)(iVar1 + 0x30) = *(short *)(param_1 + 0x3e) + param_2 + -0x10;
      *(short *)(iVar1 + 0x32) = *(short *)(param_1 + 0x42) + param_3 + -0x10;
    }
  }
  return;
}

