/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007b680(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  FUN_8007d224();
  iVar1 = 0;
  DAT_800f9718 = 0;
  DAT_800f971c = 0;
  DAT_800f9720 = 0;
  DAT_800f7198 = 0;
  DAT_800f7188 = 0;
  DAT_800f7178 = 0;
  DAT_800f719c = 0;
  DAT_800f718c = 0;
  DAT_800f717c = 0;
  do {
    (&DAT_800f717d)[iVar1] = 0;
    (&DAT_800f718d)[iVar1] = 0;
    (&DAT_800f719d)[iVar1] = 0;
    iVar1 = iVar1 + 1;
    iVar3 = 0;
  } while (iVar1 < 8);
  puVar2 = &DAT_800f71a8;
  do {
    FUN_8007ae28(puVar2);
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 6;
  } while (iVar3 < 8);
  iVar3 = 7;
  iVar1 = 0x70;
  DAT_800f726c = 0;
  DAT_800f7268 = 0;
  DAT_800f7270 = 0;
  do {
    *(undefined4 *)((int)&DAT_800f7278 + iVar1) = 0;
    iVar3 = iVar3 + -1;
    iVar1 = iVar1 + -0x10;
  } while (-1 < iVar3);
  DAT_800f72f8 = 0;
  FUN_8007e830();
  FUN_8007e3d0(0);
  FUN_8007d29c();
  return 1;
}

