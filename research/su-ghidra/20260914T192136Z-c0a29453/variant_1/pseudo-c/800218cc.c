/* Analysis pseudo-C, not buildable source. */

int FUN_800218cc(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  
  puVar4 = (ushort *)(&DAT_8017878c + param_1 * 0x5b4);
  uVar1 = FUN_8008f708();
  iVar3 = 0;
  iVar2 = 0;
  do {
    iVar3 = iVar3 + (uint)*puVar4;
    if ((int)((uVar1 & 0x7ff) + 1) <= iVar3) {
      return iVar2 + 1;
    }
    iVar2 = iVar2 + 1;
    puVar4 = puVar4 + 1;
  } while (iVar2 < 0x2d2);
  return 0;
}

