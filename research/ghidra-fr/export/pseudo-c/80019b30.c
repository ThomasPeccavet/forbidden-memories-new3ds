/* Analysis pseudo-C, not buildable source. */

void FUN_80019b30(int param_1,undefined1 param_2,undefined2 param_3,undefined2 param_4)

{
  *(undefined1 *)(param_1 + 0x6c) = 1;
  *(undefined1 *)(param_1 + 0x21) = param_2;
  *(undefined2 *)(param_1 + 0x28) = param_3;
  *(undefined2 *)(param_1 + 0x2a) = param_4;
  *(undefined1 **)(param_1 + 0x24) = &LAB_80019abc;
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
  return;
}

