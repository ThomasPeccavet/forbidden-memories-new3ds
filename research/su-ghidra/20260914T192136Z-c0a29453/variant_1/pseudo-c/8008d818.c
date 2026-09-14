/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_8008d818(undefined4 param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  
  iVar8 = 0;
  iVar6 = 0;
  puVar7 = &DAT_800ff7c0;
  do {
    FUN_8008f4d8(&DAT_800ffa00,0x80);
    FUN_8008f4d8(puVar7,0x20);
    (&DAT_800ff7c0)[iVar6 * 8] = 0xa0;
    (&DAT_800ff7c4)[iVar6 * 8] = 0;
    *(undefined2 *)(&DAT_800ff7c8 + iVar6 * 8) = 0xffff;
    _DAT_800ffa00 = *puVar7;
    DAT_800ffa04 = puVar7[1];
    DAT_800ffa08 = puVar7[2];
    DAT_800ffa0c = puVar7[3];
    DAT_800ffa10 = puVar7[4];
    DAT_800ffa14 = puVar7[5];
    DAT_800ffa18 = puVar7[6];
    DAT_800ffa1c = puVar7[7];
    iVar5 = 0;
    bVar2 = 0;
    iVar3 = 0x7e;
    pbVar4 = &DAT_800ffa00;
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      iVar3 = iVar3 + -1;
      bVar2 = bVar2 ^ bVar1;
    } while (-1 < iVar3);
    *pbVar4 = bVar2;
    do {
      FUN_8008d4e8();
      FUN_8008b2d8(param_1,iVar6 + 1,&DAT_800ffa00);
      iVar3 = FUN_8008d6c8();
      if (iVar3 == 0) break;
      if (iVar3 == 4) {
        FUN_8008d4e8();
        FUN_8008b328(param_1);
        FUN_8008d6c8();
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    iVar6 = iVar6 + 1;
    if (iVar3 != 0) {
      return iVar3;
    }
    puVar7 = puVar7 + 8;
  } while (iVar6 < 0xf);
  iVar6 = 0;
  puVar7 = &DAT_800ff9a0;
  do {
    *puVar7 = 0xffffffff;
    FUN_8008f4d8(&DAT_800ffa00,0x80);
    _DAT_800ffa00 = *puVar7;
    iVar5 = 0;
    bVar2 = 0;
    iVar3 = 0x7e;
    pbVar4 = &DAT_800ffa00;
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      iVar3 = iVar3 + -1;
      bVar2 = bVar2 ^ bVar1;
    } while (-1 < iVar3);
    *pbVar4 = bVar2;
    do {
      FUN_8008d4e8();
      FUN_8008b2d8(param_1,iVar6 + 0x10,&DAT_800ffa00);
      iVar3 = FUN_8008d6c8();
      if (iVar3 == 0) break;
      if (iVar3 == 4) {
        FUN_8008d4e8();
        FUN_8008b328(param_1);
        FUN_8008d6c8();
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    iVar6 = iVar6 + 1;
    if (iVar3 != 0) {
      return iVar3;
    }
    puVar7 = puVar7 + 1;
  } while (iVar6 < 0x14);
  pbVar4 = &DAT_800ffa00;
  FUN_8008f4d8(&DAT_800ffa00,0x80);
  iVar3 = 0;
  bVar2 = 0;
  iVar6 = 0x7e;
  _DAT_800ffa00 = CONCAT22(_DAT_800ffa02,0x434d);
  do {
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    iVar6 = iVar6 + -1;
    bVar2 = bVar2 ^ bVar1;
  } while (-1 < iVar6);
  *pbVar4 = bVar2;
  do {
    FUN_8008d4e8();
    FUN_8008b2d8(param_1,0,&DAT_800ffa00);
    iVar6 = FUN_8008d6c8();
    if (iVar6 == 0) break;
    if (iVar6 == 4) {
      FUN_8008d4e8();
      FUN_8008b328(param_1);
      FUN_8008d6c8();
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  if (iVar6 == 0) {
    do {
      FUN_8008d4e8();
      FUN_8008b2c8(param_1);
      iVar6 = FUN_8008d5f0();
      if (iVar6 == 0) {
        return 0;
      }
      iVar8 = iVar8 + 1;
      FUN_8008d4e8();
      FUN_8008b328(param_1);
      FUN_8008d6c8();
    } while (iVar8 < 8);
  }
  return iVar6;
}

