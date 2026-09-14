/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80091348(void)

{
  uint uVar1;
  int local_10;
  
  local_10 = 0x100000;
  uVar1 = *DAT_8009b42c;
  while( true ) {
    if ((uVar1 & 0x1000000) == 0) {
      return 0;
    }
    local_10 = local_10 + -1;
    if (local_10 == -1) break;
    uVar1 = *DAT_8009b42c;
  }
  FUN_800913f4(s_MDEC_out_sync_800128a8);
  return 0xffffffff;
}

