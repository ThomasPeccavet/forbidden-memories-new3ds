/* Analysis pseudo-C, not buildable source. */

void FUN_80089898(uint *param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int in_t0;
  int in_t1;
  int in_t2;
  int in_t3;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = *(ushort *)(param_2 + 0xe);
  uVar2 = *(ushort *)(in_t1 + 8);
  uVar3 = *(ushort *)(in_t2 + 8);
  uVar4 = *(ushort *)(in_t3 + 8);
  uVar5 = *(uint *)(param_2 + 0x10);
  param_1[3] = (uint)*(ushort *)(in_t0 + 8) + (uint)*(ushort *)(param_2 + 0xc) * 0x10000;
  param_1[5] = (uint)uVar2 + (uint)uVar1 * 0x10000;
  param_1[7] = (uint)uVar3;
  param_1[9] = (uint)uVar4;
  param_1[1] = uVar5;
  uVar5 = *(uint *)(in_t1 + 0x10);
  uVar6 = *(uint *)(in_t2 + 0x10);
  uVar7 = *(uint *)(in_t3 + 0x10);
  param_1[2] = *(uint *)(in_t0 + 0x10);
  param_1[4] = uVar5;
  param_1[6] = uVar6;
  param_1[8] = uVar7;
  uVar5 = **(uint **)(param_2 + 0x14);
  **(uint **)(param_2 + 0x14) = (uint)param_1 & 0xffffff;
  *param_1 = uVar5 | 0x9000000;
  return;
}

