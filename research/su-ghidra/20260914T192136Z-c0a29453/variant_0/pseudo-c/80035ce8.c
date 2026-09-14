/* Analysis pseudo-C, not buildable source. */

void FUN_80035ce8(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(&DAT_80092248 + param_2 * 4);
  iVar2 = param_2 + -1;
  do {
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (param_1 == -0x80000000)) {
      trap(0x1800);
    }
    *(char *)(param_3 + iVar2) = (char)(param_1 / iVar3);
    iVar1 = (param_1 / iVar3 & 0xffU) * iVar3;
    iVar2 = iVar2 + -1;
    iVar3 = iVar3 / 10;
    param_1 = param_1 - iVar1;
  } while (-1 < iVar2);
  while ((param_2 = param_2 + -1, 0 < param_2 && (*(char *)(param_3 + param_2) == '\0'))) {
    *(char *)(param_3 + param_2) = '\n';
  }
  return;
}

