/* Analysis pseudo-C, not buildable source. */

undefined * FUN_8002c7a0(void)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_800ec110;
  iVar2 = 8;
  do {
    iVar2 = iVar2 + -1;
    if ((puVar1[0x1c] & 0x80) == 0) {
      return puVar1;
    }
    puVar1 = puVar1 + 0x20;
  } while (iVar2 != 0);
  return (undefined *)0x0;
}

