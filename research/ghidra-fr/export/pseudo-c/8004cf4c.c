/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004cf4c(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = DAT_8009c7d8;
  if (*(ushort *)(DAT_8009c7d8 + 0x7fa) != 0) {
    do {
      iVar1 = iVar1 + 1;
      if (*(char *)(iVar2 + 0x53c) != '\x01') {
        return 1;
      }
      iVar2 = iVar2 + 0x2c;
    } while (iVar1 < (int)(uint)*(ushort *)(DAT_8009c7d8 + 0x7fa));
  }
  return 3;
}

