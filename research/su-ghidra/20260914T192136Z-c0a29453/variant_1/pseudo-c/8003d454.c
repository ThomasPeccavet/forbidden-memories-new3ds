/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003d454(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x334) == *(int *)(param_2 + 0x334)) {
    iVar2 = 4;
    do {
      bVar1 = -1 < iVar2;
      iVar2 = iVar2 + -1;
    } while (bVar1);
    return 1;
  }
  return 0;
}

