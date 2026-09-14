/* Analysis pseudo-C, not buildable source. */

void FUN_80038504(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  
  DAT_8009c6f2 = 0xff;
  puVar4 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar4;
  DAT_8009c6f3 = *pbVar2;
  *puVar4 = pbVar2 + 1;
  puVar4 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar4;
  bVar1 = *pbVar2;
  *puVar4 = pbVar2 + 1;
  DAT_8009c6ec = (ushort)bVar1;
  puVar4 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar4;
  bVar1 = *pbVar2;
  *puVar4 = pbVar2 + 1;
  DAT_8009c6ee = (ushort)bVar1;
  puVar4 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  puVar3 = (undefined1 *)*puVar4;
  DAT_8009c6f9 = *puVar3;
  *puVar4 = puVar3 + 1;
  DAT_8009c6ea = FUN_80036dfc();
  DAT_8009c6f6 = 0x72a0;
  if (DAT_8009c6f3 - 9 < 8) {
    DAT_8009c6f6 = 0x7280;
  }
  if (DAT_8009c6f3 == 0x11) {
    DAT_8009c6f6 = 0x7290;
  }
  if (DAT_8009c6f3 == 0x26) {
    DAT_8009c6f6 = 0x72b0;
  }
  DAT_8009c6fa = 2;
  DAT_8009c6fc = 0;
  DAT_8009c60a = 3;
  return;
}

