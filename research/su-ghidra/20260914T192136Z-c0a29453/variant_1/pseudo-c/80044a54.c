/* Analysis pseudo-C, not buildable source. */

int FUN_80044a54(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_3) {
    do {
      iVar1 = FUN_8008f7f8(param_2,param_1);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      param_2 = param_2 + 0x28;
    } while (iVar2 < param_3);
  }
  return -1;
}

