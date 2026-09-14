/* Analysis pseudo-C, not buildable source. */

void FUN_80048240(uint param_1)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  
  if ((param_1 & 0x8000) == 0) {
    bVar3 = 1;
    if (((param_1 & 0xf000) != 0x4000) ||
       (param_1 = (uint)*(ushort *)
                         (DAT_8009c7e0 +
                          (param_1 & 0x1f) * 2 + (uint)((param_1 & 0x100) != 0) * 0x40 + 0x44c),
       param_1 != 0xffff)) {
      uVar4 = 0;
      uVar2 = 0x100000;
      iVar1 = 0;
      do {
        if ((uint)*(ushort *)(DAT_8009c7e0 + iVar1 * 2 + 0x404) == (param_1 & 0xffff)) {
          uVar4 = uVar4 | uVar2;
          *(byte *)(DAT_8009c7e0 + 0x434) = *(byte *)(DAT_8009c7e0 + 0x434) & ~bVar3;
          FUN_80048100(uVar2);
        }
        bVar3 = bVar3 << 1;
        iVar1 = iVar1 + 1;
        uVar2 = uVar2 << 1;
      } while (iVar1 < 4);
      if (uVar4 != 0) {
        FUN_80077468(0,uVar4);
      }
    }
  }
  else {
    FUN_800469ac();
    FUN_800455d0();
  }
  return;
}

