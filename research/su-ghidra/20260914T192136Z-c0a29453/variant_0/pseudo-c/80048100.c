/* Analysis pseudo-C, not buildable source. */

void FUN_80048100(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    FUN_80077468(0,param_1);
    iVar1 = FUN_80077628(param_1);
    iVar2 = iVar2 + 1;
    if (iVar1 == 0) {
      return;
    }
  } while (iVar2 < 0x100);
  return;
}

