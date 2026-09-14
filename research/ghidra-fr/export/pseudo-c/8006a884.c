/* Analysis pseudo-C, not buildable source. */

void FUN_8006a884(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  undefined1 auStack_20 [8];
  
  puVar2 = &DAT_800929d4;
  if (*(ushort *)(&DAT_800929d6 + param_1 * 4) != 0) {
    param_3 = (uint)*(ushort *)(&DAT_800929d6 + param_1 * 4);
  }
  iVar1 = 0;
  iVar3 = 0;
  if (0 < param_1) {
    do {
      iVar1 = iVar1 + 1;
      iVar3 = iVar3 + (uint)*puVar2;
      puVar2 = puVar2 + 2;
    } while (iVar1 < param_1);
  }
  FUN_8007eb98(DAT_800eb1a4 + iVar3,auStack_20);
  iVar1 = FUN_8007eca8(auStack_20);
  FUN_80069d90(auStack_20,param_2,param_3,iVar1 + (uint)(ushort)(&DAT_800929d4)[param_1 * 2],param_4
               ,param_5);
  return;
}

