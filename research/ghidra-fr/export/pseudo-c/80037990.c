/* Analysis pseudo-C, not buildable source. */

void FUN_80037990(int param_1)

{
  bool bVar1;
  short sVar2;
  
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    DAT_8009c6dc = FUN_80036dfc();
  }
  sVar2 = DAT_8009c6dc + -1;
  bVar1 = DAT_8009c6dc == 1;
  DAT_8009c6dc = sVar2;
  if (bVar1) {
    *(undefined1 *)(param_1 + 0x51) = 0;
  }
  return;
}

