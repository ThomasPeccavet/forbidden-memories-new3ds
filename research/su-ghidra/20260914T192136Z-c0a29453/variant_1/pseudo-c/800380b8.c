/* Analysis pseudo-C, not buildable source. */

void FUN_800380b8(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  uint uVar4;
  undefined4 *puVar5;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  byte abStack_19 [9];
  
  puVar2 = (undefined4 *)FUN_80036e30();
  puVar5 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar3 = (byte *)*puVar5;
  bVar1 = *pbVar3;
  uVar7 = (uint)bVar1;
  *puVar5 = pbVar3 + 1;
  FUN_80035ce8(*puVar2,uVar7 & 0xf,abStack_19 + 1);
  uVar9 = 0;
  if ((bVar1 & 0x80) == 0) {
    if (1 < uVar7) {
      do {
        uVar4 = uVar7 - 1;
        if (abStack_19[uVar7] < 10) break;
        uVar7 = uVar4;
      } while (1 < (int)uVar4);
    }
  }
  else if ((bVar1 & 0x40) != 0) {
    uVar9 = (uint)DAT_800ec290;
  }
  pcVar6 = (char *)(param_1 + 0x44);
  iVar8 = (uVar7 & 0xf) - 1;
  do {
    uVar7 = uVar9;
    if (abStack_19[iVar8 + 1] < 10) {
      uVar7 = (uint)(&DAT_800ec290)[abStack_19[iVar8 + 1]];
    }
    if (uVar7 < 0xf0) {
      *pcVar6 = (char)uVar7;
      pcVar6 = pcVar6 + 1;
    }
    else {
      *pcVar6 = (char)(uVar7 >> 8) + -0x10;
      pcVar6[1] = (char)uVar7;
      pcVar6 = pcVar6 + 2;
    }
    iVar8 = iVar8 + -1;
  } while (-1 < iVar8);
  *pcVar6 = -1;
  bVar1 = *(char *)(param_1 + 0x58) + 1;
  *(byte *)(param_1 + 0x58) = bVar1;
  *(int *)(param_1 + ((int)((uint)bVar1 << 0x18) >> 0x16)) = param_1 + 0x44;
  return;
}

