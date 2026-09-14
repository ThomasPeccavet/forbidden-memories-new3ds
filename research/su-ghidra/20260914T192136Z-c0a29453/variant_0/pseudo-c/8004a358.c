/* Analysis pseudo-C, not buildable source. */

void FUN_8004a358(ushort param_1,ushort param_2)

{
  short sVar1;
  int iVar2;
  
  iVar2 = DAT_8009c7d8;
  sVar1 = *(short *)(DAT_8009c7d8 + 0x7e2);
  *(ushort *)(DAT_8009c7d8 + 0x7e4) = param_1 & 0x7f;
  *(ushort *)(iVar2 + 0x7e6) = param_2 & 0x7f;
  if (sVar1 != 2) {
    FUN_8004a788();
  }
  return;
}

