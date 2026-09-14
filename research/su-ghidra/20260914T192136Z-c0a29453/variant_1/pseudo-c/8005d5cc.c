/* Analysis pseudo-C, not buildable source. */

void FUN_8005d5cc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined2 param_5)

{
  if (*(int *)(param_1 + 0xd18) != 0) {
    *(undefined2 *)(*(int *)(param_1 + 0xd18) + 0x44) = 0;
    *(undefined2 *)(*(int *)(param_1 + 0xd18) + 0x46) = param_5;
    *(undefined2 *)(*(int *)(param_1 + 0xd18) + 0x48) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0xd18) + 0x18) = param_2;
    *(undefined4 *)(*(int *)(param_1 + 0xd18) + 0x1c) = param_3;
    *(undefined4 *)(*(int *)(param_1 + 0xd18) + 0x20) = param_4;
  }
  FUN_8005c334(*(undefined4 *)(param_1 + 0xd18),0);
  return;
}

