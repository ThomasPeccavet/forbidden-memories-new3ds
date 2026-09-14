/* Analysis pseudo-C, not buildable source. */

int FUN_80073ca0(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_3 != 0) {
    while( true ) {
      uVar2 = param_3;
      if (0x8000 < param_3) {
        uVar2 = 0x8000;
      }
      iVar1 = FUN_80073d60(0,param_1,uVar2,param_2);
      iVar3 = iVar3 + iVar1;
      if (iVar1 == -1) break;
      param_2 = param_2 + iVar1;
      param_3 = param_3 - iVar1;
      if (iVar1 < (int)uVar2) {
        return iVar3;
      }
      if (param_3 == 0) {
        return iVar3;
      }
    }
    iVar3 = -1;
  }
  return iVar3;
}

