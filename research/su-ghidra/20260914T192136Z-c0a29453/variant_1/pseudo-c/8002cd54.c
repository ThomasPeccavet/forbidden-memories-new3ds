/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8002cd54(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1 + -7;
  iVar2 = 6;
  if (iVar3 < 0) {
    param_2 = param_2 + -1;
    iVar3 = param_1 + -1;
    if (param_2 < 6) goto LAB_8002cd84;
  }
  else {
    param_2 = param_2 + -7;
    iVar2 = 4;
    if (-1 < param_2) {
LAB_8002cd84:
      iVar3 = iVar3 + 1;
      if (iVar2 <= iVar3) {
        iVar3 = 0;
      }
      iVar4 = iVar3 + -2;
      if (iVar3 == param_2) {
        return 500;
      }
      if (iVar4 < 0) {
        iVar4 = iVar4 + iVar2;
      }
      uVar1 = 0xfffffe0c;
      if (iVar4 != param_2) {
        uVar1 = 0;
      }
      return uVar1;
    }
  }
  return 0;
}

