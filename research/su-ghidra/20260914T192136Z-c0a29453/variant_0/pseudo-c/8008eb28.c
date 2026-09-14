/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_8008eb28(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (DAT_8009b23c == 0) {
    DAT_8009b1ec = DAT_8009b1ec + 1;
    iVar2 = FUN_8008e7e0();
    puVar1 = DAT_8009b21c;
    if (iVar2 != 0) {
      if (iVar2 == 1) {
        DAT_8009b1e8 = 0x41;
        if (DAT_8009b1f4 != 0) {
          FUN_8008e790(_DAT_8009b1f0);
          DAT_8009b1e8 = 2;
          DAT_8009b1f4 = DAT_8009b1f4 + -1;
        }
        puVar1 = DAT_8009b21c;
        *(undefined2 *)(DAT_8009b218 + 10) = 0;
        *puVar1 = 0xffffff7f;
        puVar1[1] = puVar1[1] & 0xffffff7f;
      }
      else {
        *(undefined2 *)(DAT_8009b218 + 10) = 0;
        *puVar1 = 0xffffff7f;
        puVar1[1] = puVar1[1] & 0xffffff7f;
        DAT_8009b1e8 = 0x21;
      }
      DAT_8009b1ec = 0;
      FUN_80074588(1,&DAT_8009b1d8);
    }
  }
  else {
    DAT_8009b240 = 1;
    FUN_8008f368();
    DAT_8009b240 = 0;
  }
  return 0;
}

