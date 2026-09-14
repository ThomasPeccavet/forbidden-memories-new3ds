/* Analysis pseudo-C, not buildable source. */

void FUN_80048bf8(uint param_1,short param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  short local_28 [4];
  
  if ((param_1 & 0x8000) == 0) {
    iVar3 = 0;
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
      FUN_800781e8(iVar3 + 0x14,local_28);
      iVar2 = DAT_8009c7e0 + iVar3 * 2;
      uVar1 = (uint)*(ushort *)(iVar2 + 0x404);
      if ((uVar1 == (param_1 & 0xffff)) && (local_28[0] != 0)) {
        if (param_2 != 0) {
          if ((ushort)(param_2 - 1U) < 0x80) {
            *(ushort *)(iVar2 + 0x414) =
                 (ushort)*(byte *)(uVar1 * 8 + *(int *)(DAT_8009c7e0 + 0x444)) * (0x80 - param_2);
          }
          if ((ushort)(param_2 + 0x80U) < 0x80) {
            *(ushort *)(DAT_8009c7e0 + iVar3 * 2 + 0x41c) =
                 (ushort)*(byte *)(uVar1 * 8 + *(int *)(DAT_8009c7e0 + 0x444)) * (param_2 + 0x80);
          }
        }
        FUN_80047cf4(iVar3);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 4);
  }
  else {
    FUN_8004534c((int)param_2);
  }
  return;
}

