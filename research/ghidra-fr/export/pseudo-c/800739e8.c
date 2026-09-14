/* Analysis pseudo-C, not buildable source. */

void FUN_800739e8(void)

{
  int iVar1;
  
  iVar1 = FUN_80070bb8();
  *(ushort *)(&DAT_801ab006 + *(int *)(&DAT_800f6f20 + iVar1 * 4) * 0xc) =
       *(ushort *)(&DAT_801ab006 + *(int *)(&DAT_800f6f20 + iVar1 * 4) * 0xc) | 0x4000;
  return;
}

