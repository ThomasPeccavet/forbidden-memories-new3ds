/* Analysis pseudo-C, not buildable source. */

void FUN_8003a320(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 2;
  puVar1 = (undefined4 *)(param_1 + 8);
  do {
    iVar2 = iVar2 + -1;
    FUN_80040690(*puVar1);
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (-1 < iVar2);
  return;
}

