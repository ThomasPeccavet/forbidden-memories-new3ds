/* Analysis pseudo-C, not buildable source. */

void FUN_80084978(uint *param_1,int param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar8 = *param_1;
  if (((-1 < (int)uVar8) && ((short)param_1[2] != 0)) && (*(short *)((int)param_1 + 10) != 0)) {
    uVar3 = *(ushort *)((int)param_1 + 6);
    uVar4 = param_1[1];
    uVar7 = (uint)DAT_800ff5c4 & 0xffffff;
    DAT_800ff5c4[1] =
         (ushort)param_1[3] & 0x1f | uVar8 >> 0x11 & 0x180 | 0xe1000200 | uVar8 >> 0x17 & 0x60;
    bVar1 = *(byte *)((int)param_1 + 0x16);
    bVar2 = *(byte *)((int)param_1 + 0x15);
    uVar5 = param_1[5];
    DAT_800ff5c4[3] =
         (uint)(ushort)uVar4 + (uint)DAT_800ff444 & 0xffff |
         ((uint)uVar3 + (uint)DAT_800ff446) * 0x10000;
    DAT_800ff5c4[2] =
         uVar8 >> 5 & 0x2000000 | (uVar8 & 0x40) << 0x12 | 0x64000000 | (uint)bVar1 << 0x10 |
         (uint)bVar2 << 8 | (uint)(byte)uVar5;
    DAT_800ff5c4[4] =
         (uint)*(ushort *)((int)param_1 + 0xe) | (int)*(short *)((int)param_1 + 0x12) << 0x16 |
         ((int)(short)param_1[4] & 0x3f0U) << 0xc;
    DAT_800ff5c4[5] = param_1[2];
    puVar6 = (uint *)(*(int *)(param_2 + 4) + (param_3 & 0xffff) * 4 + *(int *)(param_2 + 8) * -4);
    *DAT_800ff5c4 = *puVar6 + 0x5000000;
    DAT_800ff5c4 = DAT_800ff5c4 + 6;
    *puVar6 = uVar7;
  }
  return;
}

