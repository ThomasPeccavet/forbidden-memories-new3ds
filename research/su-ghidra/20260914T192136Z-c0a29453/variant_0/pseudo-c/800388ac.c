/* Analysis pseudo-C, not buildable source. */

void FUN_800388ac(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar3;
  bVar1 = *pbVar2;
  *puVar3 = pbVar2 + 1;
  if ((bVar1 & 0x40) != 0) {
    DAT_8009c4c4 = DAT_8009c2fa + '\t';
  }
  if ((bVar1 & 0x20) != 0) {
    DAT_8009c4c4 = '\x04';
  }
  if ((bVar1 & 0x10) == 0) {
    if ((bVar1 & 1) == 0) {
      FUN_80015b28();
    }
    else {
      FUN_80015ba0();
    }
  }
  else {
    if ((bVar1 & 1) == 0) {
      FUN_80015738(0xffffff);
    }
    else {
      FUN_80015860(0xffffff);
    }
    DAT_800eb24f = 4;
  }
  if ((bVar1 & 0x80) != 0) {
    FUN_800158b4();
  }
  return;
}

