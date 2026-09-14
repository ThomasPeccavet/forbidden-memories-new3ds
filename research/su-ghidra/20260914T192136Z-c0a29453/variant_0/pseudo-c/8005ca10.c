/* Analysis pseudo-C, not buildable source. */

int FUN_8005ca10(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1 == 0) || (iVar1 = FUN_80073c4c(param_1,0,0), iVar1 < 0)) {
    param_4 = 0;
  }
  else {
    if (param_4 == 0) {
      param_4 = FUN_80073c7c(iVar1,0,2);
      param_4 = param_4 - param_3;
    }
    FUN_80073c7c(iVar1,param_3,0);
    iVar4 = param_4;
    while (0 < iVar4) {
      iVar3 = 0x1000;
      if (iVar4 < 0x1001) {
        iVar3 = iVar4;
      }
      iVar2 = FUN_80073ca0(iVar1,param_2,iVar3);
      iVar4 = iVar4 - iVar3;
      if (iVar2 != iVar3) {
        param_4 = 0;
        break;
      }
      param_2 = param_2 + iVar3;
    }
    FUN_80073c6c(iVar1);
  }
  return param_4;
}

