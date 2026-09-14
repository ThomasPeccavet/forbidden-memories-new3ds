/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_8007afa4(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)0x0;
  if (DAT_800f7270 < 8) {
    uVar2 = FUN_80074a54(0);
    iVar3 = DAT_800f7268 + DAT_800f7270;
    if (7 < iVar3) {
      iVar3 = iVar3 + -8;
    }
    FUN_80074a54(uVar2);
    puVar1 = &DAT_800f71a8 + iVar3 * 6;
  }
  return puVar1;
}

