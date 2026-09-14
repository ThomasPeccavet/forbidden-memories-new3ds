/* Analysis pseudo-C, not buildable source. */

void FUN_80038bf0(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  int *piVar4;
  byte bVar5;
  
  DAT_8009c6cc = 1;
  puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar3;
  bVar1 = *pbVar2;
  *puVar3 = pbVar2 + 1;
  bVar5 = 0xf;
  if ((bVar1 & 8) != 0) {
    puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
    pbVar2 = (byte *)*puVar3;
    bVar5 = *pbVar2;
    *puVar3 = pbVar2 + 1;
  }
  if ((bVar1 & 0x80) == 0) {
    DAT_8009c6c1 = bVar1 & 7;
    DAT_8009c6c8 = bVar1 & 0xf0;
    DAT_8009c6a8 = bVar5 & 0xf;
    DAT_8009c6d0 = '\0';
    DAT_8009c6e0 = (bVar5 & 0x80) != 0;
    FUN_80036238(*(undefined1 *)(param_1 + 0x57));
    *(undefined1 *)(param_1 + 0x56) = 0;
    DAT_8009c6bc = &LAB_80037c78;
    *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) | 0x1000;
  }
  else {
    piVar4 = (int *)(param_1 + *(char *)(param_1 + 0x58) * 4);
    *piVar4 = *piVar4 + DAT_8009c6d0 * 2;
    FUN_80038ba8();
  }
  return;
}

