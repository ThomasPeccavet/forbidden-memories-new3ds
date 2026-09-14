/* Analysis pseudo-C, not buildable source. */

undefined * FUN_80042e70(uint param_1)

{
  byte *pbVar1;
  undefined *puVar2;
  int iVar3;
  
  puVar2 = &DAT_800f1210;
  iVar3 = 0x60;
  pbVar1 = &DAT_800f127c;
  while (((*(ushort *)(pbVar1 + -100) & 0x80) == 0 || ((*pbVar1 & 0xf) != param_1))) {
    pbVar1 = pbVar1 + 0x70;
    iVar3 = iVar3 + -1;
    puVar2 = puVar2 + 0x70;
    if (iVar3 == 0) {
      return (undefined *)0x0;
    }
  }
  return puVar2;
}

