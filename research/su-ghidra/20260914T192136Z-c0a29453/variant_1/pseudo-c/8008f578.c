/* Analysis pseudo-C, not buildable source. */

void FUN_8008f578(int param_1,uint param_2,int param_3,code *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1 + param_3;
  iVar5 = 0;
  if (1 < param_2) {
    if (param_2 == 2) {
      iVar5 = (*param_4)(param_1,iVar4);
      if (0 < iVar5) {
        FUN_8008f6c8(param_1,iVar4,param_3);
      }
    }
    else {
      uVar2 = 1;
      FUN_8008f6c8(param_1,param_1 + (param_2 >> 1) * param_3,param_3);
      iVar3 = param_1;
      if (1 < param_2) {
        do {
          iVar1 = (*param_4)(iVar4,param_1);
          if (iVar1 < 0) {
            iVar3 = iVar3 + param_3;
            iVar5 = iVar5 + 1;
            if (iVar4 != iVar3) {
              FUN_8008f6c8(iVar4,iVar3,param_3);
            }
          }
          uVar2 = uVar2 + 1;
          iVar4 = iVar4 + param_3;
        } while (uVar2 < param_2);
      }
      if (iVar3 != param_1) {
        FUN_8008f6c8(param_1,iVar3,param_3);
      }
      FUN_8008f578(param_1,iVar5,param_3,param_4);
      FUN_8008f578(iVar3 + param_3,(param_2 - iVar5) + -1,param_3,param_4);
    }
  }
  return;
}

