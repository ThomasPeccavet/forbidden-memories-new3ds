/* Analysis pseudo-C, not buildable source. */

uint FUN_800483c8(byte param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = 1;
  iVar1 = 0;
  do {
    if ((*(byte *)(DAT_8009c7e0 + iVar1 + 0x410) & 0xf) == param_1) {
      uVar3 = uVar3 | uVar2;
    }
    iVar1 = iVar1 + 1;
    uVar2 = uVar2 << 1;
  } while (iVar1 < 4);
  if (uVar3 != 0) {
    FUN_80077468(0,uVar3 << 0x14);
  }
  return uVar3;
}

