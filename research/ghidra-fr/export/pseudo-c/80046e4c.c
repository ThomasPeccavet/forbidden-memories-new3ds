/* Analysis pseudo-C, not buildable source. */

void FUN_80046e4c(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = DAT_8009c7e0;
  *(undefined4 *)(DAT_8009c7e0 + 0x3c) = 0;
  if (param_1 == 0) {
    *(byte *)(iVar1 + 0x4a) = *(byte *)(iVar1 + 0x4a) & 0xfe;
  }
  if (param_2 == 0) {
    *(byte *)(DAT_8009c7e0 + 0x4a) = *(byte *)(DAT_8009c7e0 + 0x4a) & 0xfd;
  }
  if (param_3 == 0) {
    *(byte *)(DAT_8009c7e0 + 0x4a) = *(byte *)(DAT_8009c7e0 + 0x4a) & 0xbf;
  }
  *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) | 10;
  return;
}

