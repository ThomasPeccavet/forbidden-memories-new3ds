/* Analysis pseudo-C, not buildable source. */

void FUN_800379f0(int param_1)

{
  bool bVar1;
  ushort uVar2;
  short sVar3;
  
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    DAT_8009c6dc = FUN_80036dfc();
    DAT_8009c6c4 = DAT_8009c4c0;
    DAT_8009c6c6 = DAT_8009c4c2;
  }
  if ((DAT_8009c42c & 1) != 0) {
    uVar2 = FUN_8008f708();
    DAT_8009c4c0 = DAT_8009c6c4 + ((uVar2 & 7) - 4);
    uVar2 = FUN_8008f708();
    DAT_8009c4c2 = DAT_8009c6c6 + ((uVar2 & 3) - 2);
  }
  sVar3 = DAT_8009c6dc + -1;
  bVar1 = DAT_8009c6dc == 1;
  DAT_8009c6dc = sVar3;
  if (bVar1) {
    DAT_8009c4c0 = DAT_8009c6c4;
    DAT_8009c4c2 = DAT_8009c6c6;
    *(undefined1 *)(param_1 + 0x51) = 0;
  }
  return;
}

