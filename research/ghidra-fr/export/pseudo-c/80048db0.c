/* Analysis pseudo-C, not buildable source. */

void FUN_80048db0(uint param_1,undefined1 param_2)

{
  uint uVar1;
  int iVar2;
  short local_18 [4];
  
  if ((param_1 & 0x8000) == 0) {
    iVar2 = 0;
    if ((param_1 & 0xf000) == 0x4000) {
      uVar1 = (uint)*(ushort *)
                     (DAT_8009c7e0 + (param_1 & 0x1f) * 2 + (uint)((param_1 & 0x100) != 0) * 0x40 +
                     0x44c);
      if (uVar1 == 0xffff) {
        return;
      }
      param_1 = (uint)*(ushort *)(uVar1 * 2 + *(int *)(DAT_8009c7e0 + 0x43c));
      if (param_1 == 0xffff) {
        return;
      }
    }
    do {
      FUN_800781e8(iVar2 + 0x14,local_18);
      if (((uint)*(ushort *)(DAT_8009c7e0 + iVar2 * 2 + 0x404) == (param_1 & 0xffff)) &&
         (local_18[0] != 0)) {
        *(undefined1 *)(DAT_8009c7e0 + iVar2 + 0x424) = param_2;
        FUN_80047cf4(iVar2);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
  }
  else {
    FUN_8004527c(param_2);
  }
  return;
}

