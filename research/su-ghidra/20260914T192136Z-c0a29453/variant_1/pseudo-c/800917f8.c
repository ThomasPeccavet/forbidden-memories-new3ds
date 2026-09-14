/* Analysis pseudo-C, not buildable source. */

void FUN_800917f8(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  
  iVar3 = 0;
  pbVar6 = param_1;
  pbVar7 = &DAT_8009b488;
  do {
    uVar2 = (uint)*pbVar7;
    pbVar8 = pbVar7 + 1;
    if (uVar2 < 0xf0) {
      if (iVar3 == 0) {
        do {
          bVar1 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          uVar2 = uVar2 - 1;
          *pbVar6 = bVar1;
          pbVar6 = pbVar6 + 1;
        } while (-1 < (int)uVar2);
      }
      else {
        do {
          uVar2 = uVar2 - 1;
          *pbVar6 = pbVar6[-iVar3];
          pbVar6 = pbVar6 + 1;
        } while (-1 < (int)uVar2);
      }
    }
    else {
      iVar3 = 0;
      if (uVar2 != 0xf0) {
        bVar1 = *pbVar8;
        pbVar8 = pbVar7 + 2;
        iVar3 = CONCAT11(*pbVar7,bVar1) - 0xf0ff;
      }
    }
    iVar5 = 4;
    pbVar7 = pbVar8;
  } while (iVar3 != 0xf00);
  puVar4 = (ushort *)(param_1 + 8);
  do {
    iVar5 = iVar5 + 1;
    *puVar4 = *puVar4 ^ puVar4[-4];
    puVar4 = puVar4 + 1;
  } while (iVar5 < 0x8800);
  return;
}

