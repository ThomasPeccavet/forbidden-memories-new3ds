/* Analysis pseudo-C, not buildable source. */

void FUN_80047278(void)

{
  byte *pbVar1;
  short *psVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = DAT_8009c7e0;
  pbVar1 = (byte *)(DAT_8009c7e0 + 0x164a);
  *(ushort *)(DAT_8009c7e0 + 0x42) = (ushort)*(byte *)(DAT_8009c7e0 + 0x1649);
  *(ushort *)(iVar6 + 0x44) = (ushort)*pbVar1;
  FUN_8004527c(0);
  psVar2 = (short *)(DAT_8009c7e0 + 0x157e);
  *(undefined2 *)(DAT_8009c7e0 + 0x512) = 0;
  if (*psVar2 != -1) {
    sVar4 = FUN_8004a3e0();
    if (sVar4 != 1) {
      FUN_8004a0d0((int)*(short *)(DAT_8009c7e0 + 0x157e));
      *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) & 0xff7f;
    }
    FUN_8004a140((int)*(short *)(DAT_8009c7e0 + 0x157e));
  }
  iVar6 = DAT_8009c7e0;
  sVar4 = *(short *)(DAT_8009c7e0 + 0x157a);
  *(undefined2 *)(DAT_8009c7e0 + 0x157c) = 0xffff;
  *(undefined2 *)(iVar6 + 0x157e) = 0xffff;
  if (sVar4 != -1) {
    FUN_80049d88();
  }
  iVar6 = DAT_8009c7e0;
  *(undefined2 *)(DAT_8009c7e0 + 0x1578) = 0xffff;
  *(undefined2 *)(iVar6 + 0x157a) = 0xffff;
  *(undefined2 *)(iVar6 + 0x1588) = 0;
  FUN_80077468(0,0xffffff);
  *(undefined1 *)(DAT_8009c7e0 + 0x434) = 0;
  iVar6 = 0;
  *(undefined1 *)(DAT_8009c7e0 + 0x435) = 0;
  do {
    *(undefined1 *)(DAT_8009c7e0 + iVar6 + 0x40c) = 0;
    iVar3 = DAT_8009c7e0;
    iVar5 = iVar6 * 2;
    iVar6 = iVar6 + 1;
    *(undefined2 *)(DAT_8009c7e0 + iVar5 + 0x404) = 0;
  } while (iVar6 < 4);
  *(undefined1 *)(iVar3 + 0x7c) = 0;
  iVar6 = DAT_8009c7e0;
  *(undefined2 *)(iVar3 + 0x4c) = 0;
  *(undefined1 *)(iVar6 + 0x7d) = 0;
  iVar6 = DAT_8009c7e0;
  *(undefined1 *)(DAT_8009c7e0 + 0x7e) = 0;
  iVar3 = DAT_8009c7e0;
  *(undefined2 *)(iVar6 + 0x4e) = 0;
  *(undefined4 *)(iVar6 + 0x50) = 0;
  *(undefined4 *)(iVar6 + 0x54) = 0;
  *(undefined4 *)(iVar6 + 0x58) = 0;
  *(undefined2 *)(iVar3 + 0x40) = 0;
  return;
}

