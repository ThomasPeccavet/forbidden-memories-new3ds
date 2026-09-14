/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80027590(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = FUN_8008f708();
  if (((((uVar2 & 1) != 0) || (iVar3 = FUN_80026e50(), iVar3 != 0)) &&
      ((uVar2 = FUN_8008f708(), (uVar2 & 1) != 0 || (iVar3 = FUN_800270e8(), iVar3 != 0)))) &&
     (((uVar2 = FUN_8008f708(), (uVar2 & 3) != 0 || (iVar3 = FUN_800271b4(), iVar3 != 0)) &&
      (iVar3 = FUN_800272b0(), iVar3 != 0)))) {
    iVar3 = FUN_80035dfc(5);
    iVar3 = ((uint)DAT_8009c504 * 0xf + iVar3) * 0x1c;
    if (((int)(&DAT_801d4244)[*(short *)(&DAT_801a7ae4 + iVar3) + -1] >> 0x1a & 0x1fU) < 0x14) {
      iVar4 = FUN_80026c94(5);
      if (iVar4 < 0) {
        iVar4 = FUN_80035dfc(5);
      }
      DAT_800ec211 = 0;
      DAT_800ec216 = (char)iVar4 + (char)(iVar4 / 5) * -5 + '\x01';
      DAT_800ec210 = (char)(&DAT_801a7af0)[iVar3] % '\x05' + '\v';
      bVar1 = FUN_8008f708();
      DAT_800ec217 = bVar1 & 1;
    }
    else {
      iVar4 = FUN_80026c94(10);
      if (iVar4 < 0) {
        iVar4 = FUN_80035dfc(5);
      }
      DAT_800ec211 = 0;
      DAT_800ec217 = 0;
      DAT_800ec216 = (char)iVar4 + (char)(iVar4 / 5) * -5 + '\x06';
      DAT_800ec210 = (char)(&DAT_801a7af0)[iVar3] % '\x05' + '\v';
      bVar1 = FUN_8008f708();
      if (((int)(&DAT_801d4244)[*(short *)(&DAT_801a7ae4 + iVar3) + -1] >> 0x1a & 0x1fU) != 0x17) {
        DAT_800ec218 = bVar1 & 1;
        return 0;
      }
    }
    DAT_800ec218 = 1;
  }
  return 0;
}

