/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_8008e5e8(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = DAT_8009b1c4;
  puVar1 = DAT_8009b1c0;
  if (DAT_8009b1ec != 0) {
    if ((DAT_800ffbe0 != 0x11) || (DAT_8009b1f8 = DAT_8009b1f8 + 1, 2 < DAT_8009b1f8)) {
      DAT_8009b1e8 = 0x11;
      DAT_8009b1ec = 0;
      *DAT_8009b1c0 = 0xffffff7f;
      DAT_8009b1f8 = 0;
      puVar1[1] = puVar1[1] & 0xffffff7f;
      *(undefined2 *)(iVar2 + 10) = 0;
      FUN_80074588(1,&DAT_8009b1d8);
      iVar2 = DAT_8009b1c4;
      DAT_8009b23c = 0;
      *(undefined2 *)(DAT_8009b1c4 + 10) = 0x40;
      *(undefined2 *)(iVar2 + 0xe) = 0x88;
      *(undefined2 *)(iVar2 + 8) = 0xd;
      *(undefined2 *)(iVar2 + 10) = 0;
      return 0;
    }
    DAT_8009b1e8 = DAT_800ffbe0;
    FUN_8008e790(_DAT_8009b1f0);
    DAT_8009b1e8 = 2;
    *(undefined2 *)(DAT_8009b1c4 + 10) = 0;
    puVar1 = DAT_8009b1c0;
    *DAT_8009b1c0 = 0xffffff7f;
    puVar1[1] = puVar1[1] & 0xffffff7f;
    DAT_8009b1ec = 0;
    FUN_80074588(1,&DAT_8009b1d8);
  }
  if ((DAT_8009b1e8 & 1) == 0) {
    FUN_80074588(1,&DAT_8009b1d8);
    FUN_80074578(1,&DAT_8009b1d8);
    FUN_8008eb28();
    puVar1 = DAT_8009b1c0;
    *DAT_8009b1c0 = 0xffffff7f;
    puVar1[1] = puVar1[1] | 0x80;
  }
  return 0;
}

