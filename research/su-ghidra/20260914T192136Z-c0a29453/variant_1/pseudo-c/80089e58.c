/* Analysis pseudo-C, not buildable source. */

int FUN_80089e58(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = 0;
  uVar4 = (uint)*(ushort *)(*param_1 + 2);
  *param_1 = *param_1 + 4;
  if (uVar4 != 0) {
    do {
      FUN_8007ff10(*param_1,param_1[5] + *(int *)(*param_1 + 8) * 4);
      iVar1 = *param_1;
      iVar2 = iVar1 + 0xc;
      *param_1 = iVar2;
      FUN_8007ff10(iVar2,param_1[6] + *(int *)(iVar1 + 0x14) * 4);
      iVar3 = iVar3 + 1;
      *param_1 = *param_1 + 0xc;
    } while (iVar3 < (int)uVar4);
  }
  return *param_1;
}

