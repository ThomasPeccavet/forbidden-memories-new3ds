/* Analysis pseudo-C, not buildable source. */

int FUN_80085d98(int param_1,int param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  
  puVar5 = *(uint **)(param_1 + 4);
  uVar3 = *puVar5;
  puVar4 = puVar5;
  puVar2 = puVar5;
  while (puVar1 = puVar4, puVar4 = puVar5, (uVar3 & 0xffffff) != 0xffffff) {
    puVar5 = (uint *)(*puVar4 & 0xffffff);
    uVar3 = *puVar5;
    puVar2 = puVar1;
  }
  puVar4 = (uint *)((*(int *)(param_1 + 0xc) - *(int *)(param_2 + 8)) * 4 + *(int *)(param_2 + 4));
  *puVar2 = *puVar2 & 0xff000000 | *puVar4 & 0xffffff;
  *puVar4 = *puVar4 & 0xff000000 | *(uint *)(param_1 + 0x10) & 0xffffff;
  return param_2;
}

