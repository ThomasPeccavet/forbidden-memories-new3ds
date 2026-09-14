/* Analysis pseudo-C, not buildable source. */

uint FUN_80089d60(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = param_2 + 8;
  uVar2 = (uint)*(ushort *)(param_2 + 6);
  iVar1 = 0;
  if (uVar2 != 0) {
    do {
      *param_1 = iVar3;
      iVar1 = iVar1 + 1;
      iVar3 = iVar3 + (uint)*(ushort *)(iVar3 + 4) * 4;
      param_1 = param_1 + 1;
    } while (iVar1 < (int)uVar2);
  }
  return uVar2;
}

