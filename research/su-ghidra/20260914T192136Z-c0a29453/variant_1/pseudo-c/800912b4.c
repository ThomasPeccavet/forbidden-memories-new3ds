/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800912b4(void)

{
  uint uVar1;
  int local_10;
  
  local_10 = 0x100000;
  uVar1 = *DAT_8009b44c;
  while( true ) {
    if ((uVar1 & 0x20000000) == 0) {
      return 0;
    }
    local_10 = local_10 + -1;
    if (local_10 == -1) break;
    uVar1 = *DAT_8009b44c;
  }
  FUN_800913f4(s_MDEC_in_sync_80012898);
  return 0xffffffff;
}

