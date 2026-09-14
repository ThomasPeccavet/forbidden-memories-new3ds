/* Analysis pseudo-C, not buildable source. */

int FUN_80040390(void)

{
  int iVar1;
  undefined *puVar2;
  
  puVar2 = &DAT_800f1210;
  iVar1 = 0;
  do {
    if ((*(ushort *)(puVar2 + 8) & 0x80) == 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x70;
  } while (iVar1 < 0x60);
  return -1;
}

