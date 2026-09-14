/* Analysis pseudo-C, not buildable source. */

int FUN_8004492c(undefined4 param_1,undefined4 param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_38 [32];
  
  FUN_80090408(auStack_38,s_bu_02X__s_800104c4,param_1,param_2);
  iVar3 = 5;
  while( true ) {
    iVar1 = FUN_80074008(auStack_38,param_3);
    iVar3 = iVar3 + -1;
    if (iVar1 == param_3) break;
    if (iVar3 < 0) {
      return 0;
    }
  }
  iVar3 = 5;
  iVar1 = 1;
  param_3 = param_3 + 0x28;
  do {
    iVar2 = FUN_80073e68(param_3);
    iVar3 = iVar3 + -1;
    if (iVar2 == param_3) {
      iVar3 = 5;
      param_3 = param_3 + 0x28;
      iVar1 = iVar1 + 1;
    }
    else if (iVar3 < 0) break;
  } while (iVar1 < 0xf);
  if (param_4 != (int *)0x0) {
    *param_4 = iVar1;
  }
  return iVar1;
}

