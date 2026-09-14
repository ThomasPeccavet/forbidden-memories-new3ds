/* Analysis pseudo-C, not buildable source. */

uint FUN_800199f0(uint param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  
  uVar2 = param_1;
  if ((int)param_2 < (int)param_1) {
    uVar2 = param_2;
    param_2 = param_1;
  }
  uVar2 = (uint)*(ushort *)(&DAT_8017c2d8 + uVar2 * 2);
  pbVar3 = &DAT_8017c2d8 + uVar2;
  if (uVar2 == 0) {
    return 0;
  }
  uVar5 = (uint)*pbVar3;
  if (uVar5 == 0) {
    pbVar3 = &DAT_8017c2d9 + uVar2;
    uVar5 = 0x1ff - (byte)(&DAT_8017c2d9)[uVar2];
  }
  pbVar4 = pbVar3 + 1;
  pbVar3 = pbVar3 + 4;
  while( true ) {
    uVar2 = (uint)*pbVar4;
    if (((uVar2 & 3) << 8 | (uint)pbVar3[-2]) == param_2) {
      return (uVar2 & 0xc) << 6 | (uint)pbVar4[2];
    }
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 5;
    if (((uVar2 & 0x30) << 4 | (uint)bVar1) == param_2) break;
    uVar5 = uVar5 - 2;
    pbVar4 = pbVar4 + 5;
    if ((int)uVar5 < 1) {
      return 0;
    }
  }
  return (uVar2 & 0xc0) << 2 | (uint)pbVar4[4];
}

