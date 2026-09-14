/* Analysis pseudo-C, not buildable source. */

uint FUN_8004bf74(uint *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_8009c7d8;
  bVar1 = *(byte *)(*(int *)(DAT_8009c7d8 + 0x7dc) + *param_1);
  uVar3 = *param_1 + 1;
  *param_1 = uVar3;
  if (uVar3 <= *(uint *)(iVar2 + 0x7ec)) {
    return (uint)bVar1;
  }
  *(undefined1 *)(param_1 + 9) = 1;
  return 0xffffffff;
}

