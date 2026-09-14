/* Analysis pseudo-C, not buildable source. */

int FUN_80089dc8(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = 0;
  uVar2 = (uint)*(ushort *)(*param_1 + 2);
  *param_1 = *param_1 + 4;
  if (uVar2 != 0) {
    do {
      FUN_8007ff10(*param_1,param_1[5] + *(int *)(*param_1 + 8) * 4);
      iVar1 = iVar1 + 1;
      *param_1 = *param_1 + 0xc;
    } while (iVar1 < (int)uVar2);
  }
  return *param_1;
}

