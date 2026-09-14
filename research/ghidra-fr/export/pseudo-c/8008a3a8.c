/* Analysis pseudo-C, not buildable source. */

int * FUN_8008a3a8(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = (int *)FUN_8008a0c0();
  iVar3 = 0;
  piVar2 = (int *)piVar1[*piVar1];
  *piVar1 = *piVar1 + -1;
  iVar4 = *piVar2;
  piVar1 = piVar2 + 1;
  if (0 < iVar4) {
    do {
      piVar2 = piVar2 + 0x14;
      if (*piVar2 != 0) {
        *piVar2 = param_1 + *piVar2 * 4;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar4);
  }
  return piVar1;
}

