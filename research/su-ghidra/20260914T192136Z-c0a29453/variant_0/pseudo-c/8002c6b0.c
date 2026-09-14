/* Analysis pseudo-C, not buildable source. */

int FUN_8002c6b0(uint param_1)

{
  int iVar1;
  ushort *puVar2;
  
  puVar2 = &DAT_801d0200;
  iVar1 = 0;
  do {
    if (*puVar2 == param_1) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 0x28);
  return -1;
}

