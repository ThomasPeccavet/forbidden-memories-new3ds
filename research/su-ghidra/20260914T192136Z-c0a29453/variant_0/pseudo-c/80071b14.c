/* Analysis pseudo-C, not buildable source. */

void FUN_80071b14(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80070bb8();
  uVar2 = *(uint *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  *(uint *)(&DAT_800f6f20 + iVar1 * 4) =
       (uint)((&DAT_800eb291)[(DAT_8009c504 ^ 1 ^ uVar2) * 0x20] != '\0');
  return;
}

