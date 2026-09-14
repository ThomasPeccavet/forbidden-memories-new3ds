/* Analysis pseudo-C, not buildable source. */

void FUN_80038a84(int param_1)

{
  byte *pbVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar1 = (byte *)*puVar3;
  uVar2 = (uint)*pbVar1;
  *puVar3 = pbVar1 + 1;
  if (uVar2 != 0) {
    FUN_8002ceb8(uVar2 + 0x1f);
    FUN_8002ceb8(uVar2 + 0x6e0);
  }
  return;
}

