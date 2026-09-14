/* Analysis pseudo-C, not buildable source. */

void FUN_8003ce34(void)

{
  uint uVar1;
  
  uVar1 = 0;
  if (DAT_800f0a10 == '\0') {
    uVar1 = CONCAT11(DAT_800f0a12,DAT_800f0a13) ^ 0xffff;
  }
  if (DAT_800f0a34 == '\0') {
    uVar1 = uVar1 | (CONCAT11(DAT_800f0a36,DAT_800f0a37) ^ 0xffff) << 0x10;
  }
  DAT_8009c70c = DAT_8009c70c | uVar1;
  return;
}

