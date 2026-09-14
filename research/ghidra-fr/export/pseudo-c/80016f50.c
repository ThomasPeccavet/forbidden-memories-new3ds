/* Analysis pseudo-C, not buildable source. */

int FUN_80016f50(int param_1)

{
  bool bVar1;
  
  bVar1 = true;
  if (0x13 < (byte)(&DAT_800919e0)
                   [*(char *)(DAT_8009c5b0 + 0x10) * 5 + (int)*(char *)(DAT_8009c5b0 + 0xf)]) {
    bVar1 = (*(ushort *)(param_1 + 0x16) & 0x1000) == 0;
  }
  if ((((DAT_8009c72c & 0x10) != 0) && ((*(ushort *)(param_1 + 0x16) & 0x8000) != 0)) && (bVar1)) {
    return (int)*(short *)(param_1 + 0xc);
  }
  return 0;
}

