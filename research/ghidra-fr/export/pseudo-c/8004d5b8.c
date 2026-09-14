/* Analysis pseudo-C, not buildable source. */

void FUN_8004d5b8(uint *param_1,int param_2,uint param_3,uint param_4)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  bVar1 = *(byte *)((int)param_1 + 3);
  uVar5 = (uint)bVar1;
  iVar4 = uVar5 - 1;
  *DAT_800ff5c4 = *param_1;
  puVar2 = DAT_800ff5c4 + 2;
  DAT_800ff5c4[1] = (param_4 & 3) << 5 | 0xe1000200;
  if (uVar5 != 0) {
    do {
      param_1 = param_1 + 1;
      iVar4 = iVar4 + -1;
      *puVar2 = *param_1;
      puVar2 = puVar2 + 1;
    } while (iVar4 != -1);
  }
  *(byte *)((int)DAT_800ff5c4 + 3) = bVar1 + 1;
  if (-1 < (int)param_4) {
    *(byte *)((int)DAT_800ff5c4 + 0xb) = *(byte *)((int)DAT_800ff5c4 + 0xb) | 2;
  }
  iVar4 = (param_3 & 0xffff) * 4;
  *DAT_800ff5c4 = *DAT_800ff5c4 & 0xff000000 | *(uint *)(iVar4 + *(int *)(param_2 + 4)) & 0xffffff;
  puVar2 = (uint *)(iVar4 + *(int *)(param_2 + 4));
  uVar3 = (uint)DAT_800ff5c4 & 0xffffff;
  DAT_800ff5c4 = DAT_800ff5c4 + uVar5 + 2;
  *puVar2 = *puVar2 & 0xff000000 | uVar3;
  return;
}

