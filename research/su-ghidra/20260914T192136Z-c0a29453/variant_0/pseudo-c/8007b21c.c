/* Analysis pseudo-C, not buildable source. */

bool FUN_8007b21c(void)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = FUN_8007c484(0);
  bVar1 = false;
  if (iVar2 == 1) {
    bVar1 = false;
    if ((&DAT_800f71a8)[DAT_800f726c * 6] != 0) {
      iVar2 = FUN_8007c3d8((&DAT_800f71ac)[DAT_800f726c * 0x18],(&DAT_800f71b4)[DAT_800f726c * 6]);
      bVar1 = iVar2 != 0;
    }
  }
  return bVar1;
}

