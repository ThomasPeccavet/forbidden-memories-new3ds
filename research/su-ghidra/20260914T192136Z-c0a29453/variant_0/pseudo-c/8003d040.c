/* Analysis pseudo-C, not buildable source. */

void FUN_8003d040(void)

{
  uint uVar1;
  
  uVar1 = (s_UUUU__8009c2f0._0_4_ << 0x1f | DAT_8009c2ec >> 1) ^ DAT_8009c2ec << 0xc;
  s_UUUU__8009c2f0._0_4_ = s_UUUU__8009c2f0._0_4_ * 2 + (DAT_8009c2ec & 1);
  DAT_8009c2ec = uVar1 ^ uVar1 >> 0x14;
  return;
}

