/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007b53c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = FUN_8007d2ac();
  uVar2 = 0;
  if (iVar1 == 0) {
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
      iVar4 = 0;
    } while (iVar1 < 8);
    puVar3 = &DAT_800f71a8;
    do {
      FUN_8007ae28(puVar3);
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 6;
    } while (iVar4 < 8);
    iVar4 = 7;
    iVar1 = 0x70;
    DAT_800f726c = 0;
    DAT_800f7268 = 0;
    DAT_800f7270 = 0;
    do {
      *(undefined4 *)((int)&DAT_800f7278 + iVar1) = 0;
      iVar4 = iVar4 + -1;
      iVar1 = iVar1 + -0x10;
    } while (-1 < iVar4);
    DAT_800f72f8 = 0;
    FUN_8007c218();
    FUN_8007c460(FUN_8007b28c);
    FUN_8007c46c(FUN_8007c10c);
    FUN_8007c478(FUN_8007c1e0);
    FUN_8007c454(FUN_8007c068);
    FUN_8007e830();
    FUN_8007e3d0(0);
    uVar2 = 1;
  }
  return uVar2;
}

