/* Analysis pseudo-C, not buildable source. */

void FUN_8004cef0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
    iVar2 = 0;
    iVar1 = DAT_8009c7d8;
    do {
      *(undefined1 *)(iVar1 + iVar2 + 0x53c) = 1;
      iVar1 = DAT_8009c7d8;
      iVar3 = iVar3 + 1;
      *(undefined4 *)(DAT_8009c7d8 + iVar2 + 0x518) = 0;
      iVar2 = iVar2 + 0x2c;
    } while (iVar3 < (int)(uint)*(ushort *)(iVar1 + 0x7fa));
  }
  return;
}

