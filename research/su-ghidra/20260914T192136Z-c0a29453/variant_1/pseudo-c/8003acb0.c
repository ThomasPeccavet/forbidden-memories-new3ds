/* Analysis pseudo-C, not buildable source. */

void FUN_8003acb0(int param_1,undefined2 param_2,undefined2 param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 2;
  piVar2 = (int *)(param_1 + 8);
  do {
    if (*piVar2 != 0) {
      *(undefined2 *)(*piVar2 + 0x30) = param_2;
      *(undefined2 *)(*piVar2 + 0x32) = param_3;
    }
    iVar1 = iVar1 + -1;
    piVar2 = piVar2 + -1;
  } while (-1 < iVar1);
  return;
}

