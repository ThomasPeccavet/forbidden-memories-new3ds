/* Analysis pseudo-C, not buildable source. */

int FUN_80049c70(undefined4 param_1,uint param_2,short param_3)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_8009c7d8;
  sVar1 = *(short *)(DAT_8009c7d8 + 0x4a4);
  if ((int)sVar1 == (int)param_3) {
    FUN_80077748(*(int *)(DAT_8009c7d8 + 0x4b8) + *(int *)(DAT_8009c7d8 + 0x818));
    uVar3 = *(int *)(iVar2 + 0x4b4) - *(int *)(DAT_8009c7d8 + 0x818);
    if (uVar3 < param_2) {
      param_2 = uVar3;
    }
    uVar3 = FUN_800776e8(param_1,param_2);
    if (uVar3 == param_2) {
      param_2 = *(int *)(DAT_8009c7d8 + 0x818) + param_2;
      *(uint *)(DAT_8009c7d8 + 0x818) = param_2;
      if (*(uint *)(iVar2 + 0x4b4) <= param_2) {
        return (int)sVar1;
      }
      return -2;
    }
  }
  return -1;
}

