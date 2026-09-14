/* Analysis pseudo-C, not buildable source. */

void FUN_80030228(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      (*(code *)(&PTR_LAB_800920c4)[*(byte *)(param_1 + 1)])(param_1);
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 5;
  } while (iVar1 < 3);
  return;
}

