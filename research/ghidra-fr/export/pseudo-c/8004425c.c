/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004425c(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  while( true ) {
    iVar1 = FUN_80073dc8(*param_1);
    if (iVar1 == 1) {
      return 0;
    }
    iVar1 = FUN_80073dc8(param_1[1]);
    if (iVar1 == 1) {
      return 1;
    }
    iVar1 = FUN_80073dc8(param_1[2]);
    if (iVar1 == 1) {
      return 2;
    }
    iVar1 = FUN_80073dc8(param_1[3]);
    if (iVar1 == 1) break;
    if (param_2 != 0) {
      return 0xffffffff;
    }
  }
  return 3;
}

