/* Analysis pseudo-C, not buildable source. */

void FUN_800842a8(int param_1,undefined4 param_2,undefined2 param_3)

{
  undefined4 *puVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = DAT_800ff5c4;
  sVar3 = DAT_800ff444;
  iVar4 = 4;
  bVar2 = *(byte *)(param_1 + 7);
  *(undefined4 *)(DAT_800ff5c4 + 4) = *(undefined4 *)(param_1 + 4);
  *(short *)(iVar6 + 8) = *(short *)(param_1 + 8) + sVar3;
  *(short *)(iVar6 + 10) = *(short *)(param_1 + 10) + DAT_800ff446;
  if ((bVar2 & 4) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0xc);
    param_1 = param_1 + 4;
    iVar4 = 5;
    *(undefined4 *)(iVar6 + 0xc) = *puVar1;
    iVar6 = iVar6 + 4;
  }
  if ((bVar2 & 0x10) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0xc);
    param_1 = param_1 + 4;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(iVar6 + 0xc) = *puVar1;
    iVar6 = iVar6 + 4;
  }
  *(short *)(iVar6 + 0xc) = *(short *)(param_1 + 0xc) + DAT_800ff444;
  *(short *)(iVar6 + 0xe) = *(short *)(param_1 + 0xe) + DAT_800ff446;
  if ((bVar2 & 4) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x10);
    param_1 = param_1 + 4;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(iVar6 + 0x10) = *puVar1;
    iVar6 = iVar6 + 4;
  }
  if ((bVar2 & 0x10) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x10);
    param_1 = param_1 + 4;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(iVar6 + 0x10) = *puVar1;
    iVar6 = iVar6 + 4;
  }
  *(short *)(iVar6 + 0x10) = *(short *)(param_1 + 0x10) + DAT_800ff444;
  *(short *)(iVar6 + 0x12) = *(short *)(param_1 + 0x12) + DAT_800ff446;
  if ((bVar2 & 4) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x14);
    param_1 = param_1 + 4;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(iVar6 + 0x14) = *puVar1;
    iVar6 = iVar6 + 4;
  }
  if ((bVar2 & 8) != 0) {
    iVar5 = iVar4;
    if ((bVar2 & 0x10) != 0) {
      puVar1 = (undefined4 *)(param_1 + 0x14);
      param_1 = param_1 + 4;
      iVar5 = iVar4 + 1;
      *(undefined4 *)(iVar6 + 0x14) = *puVar1;
      iVar6 = iVar6 + 4;
    }
    *(short *)(iVar6 + 0x14) = *(short *)(param_1 + 0x14) + DAT_800ff444;
    iVar4 = iVar5 + 1;
    *(short *)(iVar6 + 0x16) = *(short *)(param_1 + 0x16) + DAT_800ff446;
    if ((bVar2 & 4) != 0) {
      iVar4 = iVar5 + 2;
      *(undefined4 *)(iVar6 + 0x18) = *(undefined4 *)(param_1 + 0x18);
    }
  }
  DAT_800ff5c4 = FUN_80084018(DAT_800ff5c4,param_2,param_3,iVar4);
  return;
}

