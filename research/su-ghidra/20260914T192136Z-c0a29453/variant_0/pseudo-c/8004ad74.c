/* Analysis pseudo-C, not buildable source. */

int FUN_8004ad74(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)*(byte *)(DAT_8009c7d8 + param_1 * 0x28 + 0x183);
  if (uVar2 != 99) {
    iVar3 = DAT_8009c7d8 + uVar2 * 0x18;
    bVar1 = *(byte *)(iVar3 + 6);
    if ((bVar1 & 0xf) != 0) {
      *(byte *)(iVar3 + 6) = bVar1 - 1;
    }
  }
  return param_1;
}

