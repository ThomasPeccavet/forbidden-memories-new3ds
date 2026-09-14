/* Analysis pseudo-C, not buildable source. */

void FUN_80028a2c(void)

{
  int iVar1;
  
  iVar1 = FUN_80028370();
  if (iVar1 == 0) {
    iVar1 = FUN_8008f708();
    DAT_801d0534 = iVar1 * 0x100 + 1;
    DAT_8009c750 = 1;
    FUN_8003fba0();
  }
  iVar1 = FUN_8003fa30();
  if (iVar1 != 0) {
    DAT_8009c5dc = DAT_8009c5dc | 0x40;
  }
  return;
}

