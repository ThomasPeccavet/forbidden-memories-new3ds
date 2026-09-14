/* Analysis pseudo-C, not buildable source. */

void FUN_8005d020(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (-1 < param_2) {
    iVar3 = param_2 + 1;
  }
  iVar2 = 0;
  if (-1 < param_3) {
    iVar2 = param_3 + 1;
  }
  iVar1 = FUN_8004f184();
  if ((iVar1 != 1) || (iVar1 = FUN_8004f19c(param_1), iVar1 != 1)) {
    FUN_80055e94(param_1,iVar3,iVar2,param_4);
  }
  return;
}

