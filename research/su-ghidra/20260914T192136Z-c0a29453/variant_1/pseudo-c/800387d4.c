/* Analysis pseudo-C, not buildable source. */

void FUN_800387d4(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  
  puVar2 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar3 = (byte *)*puVar2;
  bVar1 = *pbVar3;
  *puVar2 = pbVar3 + 1;
  if ((bVar1 & 0x7f) == 0) {
    FUN_80040258();
  }
  else {
    FUN_8004027c();
  }
  if ((bVar1 & 0x80) != 0) {
    *(undefined1 *)(param_1 + 0x51) = 0xd;
    DAT_8009c6cc = 1;
  }
  return;
}

