/* Analysis pseudo-C, not buildable source. */

void FUN_80037614(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  
  DAT_8009c62c = 0;
  DAT_8009c62a = 0;
  DAT_8009c630 = FUN_80036dfc();
  if ((DAT_8009c630 & 0x8000) != 0) {
    puVar2 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
    pbVar3 = (byte *)*puVar2;
    bVar1 = *pbVar3;
    *puVar2 = pbVar3 + 1;
    DAT_8009c62c = (ushort)bVar1;
    DAT_8009c62a = FUN_80036dfc(param_1);
  }
  DAT_8009c6d2 = 5;
  DAT_8009c610 = 5;
  *(undefined1 *)(param_1 + 0x51) = 10;
  return;
}

