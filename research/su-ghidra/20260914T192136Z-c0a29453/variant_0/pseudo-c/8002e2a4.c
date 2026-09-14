/* Analysis pseudo-C, not buildable source. */

void FUN_8002e2a4(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  *(undefined2 *)(param_1 + 0xf) = 0xffff;
  do {
    iVar1 = iVar1 + 1;
    FUN_80040690(*param_1);
    *param_1 = 0;
    *(undefined2 *)(param_1 + 1) = 0;
    param_1 = param_1 + 5;
  } while (iVar1 < 3);
  return;
}

