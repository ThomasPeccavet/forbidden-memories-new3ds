/* Analysis pseudo-C, not buildable source. */

void FUN_80046154(void)

{
  byte *pbVar1;
  bool bVar2;
  int iVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  
  iVar3 = DAT_8009c7e0;
  bVar2 = false;
  if (*(short *)(DAT_8009c7e0 + 0x1588) != 0) {
    sVar4 = *(short *)(DAT_8009c7e0 + 0x1586) + *(short *)(DAT_8009c7e0 + 0x1588);
    *(short *)(DAT_8009c7e0 + 0x1586) = sVar4;
    bVar2 = true;
    if ((sVar4 <= (short)(ushort)*(byte *)(iVar3 + 0x158a)) && (*(short *)(iVar3 + 0x1588) < 0)) {
      *(undefined2 *)(iVar3 + 0x1588) = 0;
      *(ushort *)(iVar3 + 0x1586) = (ushort)*(byte *)(iVar3 + 0x158a);
    }
    iVar3 = DAT_8009c7e0;
    if (((short)(ushort)*(byte *)(DAT_8009c7e0 + 0x158a) <= *(short *)(DAT_8009c7e0 + 0x1586)) &&
       (0 < *(short *)(DAT_8009c7e0 + 0x1588))) {
      pbVar1 = (byte *)(DAT_8009c7e0 + 0x158a);
      *(undefined2 *)(DAT_8009c7e0 + 0x1588) = 0;
      *(ushort *)(iVar3 + 0x1586) = (ushort)*pbVar1;
    }
  }
  iVar3 = DAT_8009c7e0;
  if (*(short *)(DAT_8009c7e0 + 0x1582) != 0) {
    sVar4 = *(short *)(DAT_8009c7e0 + 0x1580) + *(short *)(DAT_8009c7e0 + 0x1582);
    *(short *)(DAT_8009c7e0 + 0x1580) = sVar4;
    if ((sVar4 <= (short)(ushort)*(byte *)(iVar3 + 0x1584)) && (*(short *)(iVar3 + 0x1582) < 0)) {
      *(undefined2 *)(iVar3 + 0x1582) = 0;
      *(ushort *)(iVar3 + 0x1580) = (ushort)*(byte *)(iVar3 + 0x1584);
    }
    iVar3 = DAT_8009c7e0;
    bVar2 = true;
    if (((short)(ushort)*(byte *)(DAT_8009c7e0 + 0x1584) <= *(short *)(DAT_8009c7e0 + 0x1580)) &&
       (bVar2 = true, 0 < *(short *)(DAT_8009c7e0 + 0x1582))) {
      pbVar1 = (byte *)(DAT_8009c7e0 + 0x1584);
      *(undefined2 *)(DAT_8009c7e0 + 0x1582) = 0;
      *(ushort *)(iVar3 + 0x1580) = (ushort)*pbVar1;
      bVar2 = true;
    }
  }
  if (bVar2) {
    if (*(short *)(DAT_8009c7e0 + 0x44) == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = (uint)((ushort)(*(short *)(DAT_8009c7e0 + 0x44) *
                             (*(short *)(DAT_8009c7e0 + 0x1580) + 1)) >> 8);
    }
    if (uVar6 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = (ushort)(uVar6 * (*(short *)(DAT_8009c7e0 + 0x1586) + 1) >> 8) & 0xff;
    }
    FUN_8004a3a0(uVar5,uVar5);
  }
  iVar3 = DAT_8009c7e0;
  if (*(short *)(DAT_8009c7e0 + 0x512) != 0) {
    sVar4 = *(short *)(DAT_8009c7e0 + 0x510) + *(short *)(DAT_8009c7e0 + 0x512);
    *(short *)(DAT_8009c7e0 + 0x510) = sVar4;
    if ((sVar4 <= (short)(ushort)*(byte *)(iVar3 + 0x49)) && (*(short *)(iVar3 + 0x512) < 0)) {
      *(undefined2 *)(iVar3 + 0x512) = 0;
      *(ushort *)(iVar3 + 0x510) = (ushort)*(byte *)(iVar3 + 0x49);
    }
    iVar3 = DAT_8009c7e0;
    if (((short)(ushort)*(byte *)(DAT_8009c7e0 + 0x49) <= *(short *)(DAT_8009c7e0 + 0x510)) &&
       (0 < *(short *)(DAT_8009c7e0 + 0x512))) {
      pbVar1 = (byte *)(DAT_8009c7e0 + 0x49);
      *(undefined2 *)(DAT_8009c7e0 + 0x512) = 0;
      *(ushort *)(iVar3 + 0x510) = (ushort)*pbVar1;
    }
    FUN_8004527c((int)*(short *)(DAT_8009c7e0 + 0x510));
  }
  return;
}

