/* Analysis pseudo-C, not buildable source. */

void FUN_80068bb0(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = &DAT_800f6c88;
  iVar3 = 0;
  piVar1 = &DAT_800f6c8c;
  while( true ) {
    if (*piVar1 == param_1) {
      return;
    }
    if ((*piVar1 == 0) && (*piVar2 == 0)) break;
    iVar3 = iVar3 + 1;
    piVar1 = piVar1 + 2;
    piVar2 = piVar2 + 2;
    if (0x4f < iVar3) {
      return;
    }
  }
  *piVar1 = param_1;
  *piVar2 = param_2;
  return;
}

