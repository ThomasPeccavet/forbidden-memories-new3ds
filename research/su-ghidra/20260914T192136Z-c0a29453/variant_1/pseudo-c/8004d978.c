/* Analysis pseudo-C, not buildable source. */

void FUN_8004d978(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_3 + -1;
  if (param_3 != 0) {
    do {
      uVar1 = *param_2;
      param_2 = param_2 + 1;
      iVar2 = iVar2 + -1;
      *param_1 = uVar1;
      param_1 = param_1 + 1;
    } while (iVar2 != -1);
  }
  return;
}

