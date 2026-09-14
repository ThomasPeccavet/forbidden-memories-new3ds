/* Analysis pseudo-C, not buildable source. */

void FUN_8004527c(short param_1)

{
  uint uVar1;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  
  uVar1 = ((uint)*(byte *)(DAT_8009c7e0 + 0x533) *
           ((int)((param_1 + 1) * (uint)*(ushort *)(DAT_8009c7e0 + 0x42)) >> 8) & 0xffff) >> 3;
  local_d = 0;
  local_10 = (undefined1)((int)(uVar1 * *(byte *)(DAT_8009c7e0 + 0x514)) >> 7);
  if (*(char *)(DAT_8009c7e0 + 0x48) == '\0') {
    local_f = 0;
    local_e = (undefined1)((int)(uVar1 * *(byte *)(DAT_8009c7e0 + 0x515)) >> 7);
  }
  else {
    local_e = 0;
    local_f = (undefined1)((int)(uVar1 * *(byte *)(DAT_8009c7e0 + 0x515)) >> 7);
  }
  FUN_8007d358(&local_10);
  *(short *)(DAT_8009c7e0 + 0x510) = param_1;
  return;
}

