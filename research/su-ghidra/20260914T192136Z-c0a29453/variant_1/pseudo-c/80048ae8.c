/* Analysis pseudo-C, not buildable source. */

void FUN_80048ae8(uint param_1,undefined1 param_2,short param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if ((param_1 & 0x8000) == 0) {
    uVar3 = param_1 & 0xffff;
    if ((param_1 & 0xf000) == 0x4000) {
      uVar3 = (uint)*(ushort *)
                     (DAT_8009c7e0 + (param_1 & 0x1f) * 2 + (uint)((param_1 & 0x100) != 0) * 0x40 +
                     0x44c);
      if (uVar3 == 0xffff) {
        return;
      }
      uVar1 = (uint)*(ushort *)(uVar3 * 2 + *(int *)(DAT_8009c7e0 + 0x43c));
      if (uVar1 == 0xffff) {
        return;
      }
      iVar2 = *(int *)(DAT_8009c7e0 + 0x444);
    }
    else {
      uVar1 = (uint)*(ushort *)(uVar3 * 2 + *(int *)(DAT_8009c7e0 + 0x43c));
      if (uVar1 == 0xffff) {
        return;
      }
      iVar2 = *(int *)(DAT_8009c7e0 + 0x444);
    }
    iVar2 = uVar1 * 8 + iVar2;
    FUN_80048740(uVar3,0,param_2,(int)param_3,*(undefined1 *)(iVar2 + 3),*(undefined1 *)(iVar2 + 2))
    ;
  }
  else {
    FUN_8004569c(param_1 & 0xffff,0);
  }
  return;
}

