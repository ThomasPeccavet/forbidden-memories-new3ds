/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_8008ee44(int param_1)

{
  ushort uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  DAT_800ffbf0 = (uint)*DAT_8009b218;
  if (param_1 < 0) {
    uVar1 = *(ushort *)(DAT_8009b218 + 4);
    while ((uVar1 & 1) == 0) {
      uVar1 = *(ushort *)(DAT_8009b218 + 4);
    }
    do {
      if ((_DAT_1f801124 & 0x1000) == 0) {
        if ((_DAT_1f801124 & 0x808) == 0x808) {
          DAT_800ffbfc = (uint)_DAT_1f801128 + DAT_800ffbfc;
        }
      }
      else {
        DAT_800ffbfc = DAT_800ffbfc + 0x10000;
      }
      if ((_DAT_1f801124 & 0x200) == 0) {
        bVar5 = (int)(((uint)_DAT_1f801120 + DAT_800ffbfc) - DAT_800ffbf4) < DAT_800ffbf8 << 3;
      }
      else {
        bVar5 = (int)(((uint)_DAT_1f801120 + DAT_800ffbfc) - DAT_800ffbf4) < DAT_800ffbf8;
      }
    } while (bVar5);
    *DAT_8009b218 = ~(byte)param_1;
    uVar4 = DAT_800ffbf0;
  }
  else {
    *DAT_8009b218 = (byte)param_1;
    pbVar2 = DAT_8009b218;
    DAT_800ffbf4 = (uint)_DAT_1f801120;
    DAT_800ffbfc = 0;
    *DAT_8009b21c = 0xffffff7f;
    uVar1 = *(ushort *)(pbVar2 + 4);
    DAT_800ffbf8 = 0x3c;
    while ((uVar1 & 0x80) != 0) {
      iVar3 = FUN_8008ed74();
      bVar5 = false;
      if (iVar3 != 0) goto LAB_8008f01c;
      uVar1 = *(ushort *)(DAT_8009b218 + 4);
    }
    bVar5 = true;
    *(ushort *)(DAT_8009b218 + 10) = *(ushort *)(DAT_8009b218 + 10) | 0x10;
LAB_8008f01c:
    uVar4 = DAT_800ffbf0;
    if (!bVar5) {
      uVar4 = -DAT_800ffbf0 - 0x300;
    }
  }
  return uVar4;
}

