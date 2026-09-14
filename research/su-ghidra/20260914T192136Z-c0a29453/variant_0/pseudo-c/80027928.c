/* Analysis pseudo-C, not buildable source. */

uint FUN_80027928(undefined4 *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = 5;
  while( true ) {
    bVar1 = (&DAT_800919e0)[iVar4 + (uint)DAT_8009c504 * 0x14];
    if (((((&DAT_801a7aee)[(uint)bVar1 * 0xe] & 0x8000) != 0) &&
        (iVar5 = iVar5 + 1, ((&DAT_801a7aee)[(uint)bVar1 * 0xe] & 0x1000) == 0)) &&
       (iVar2 = FUN_8001ef34(*param_1,(&DAT_801a7ad8)[(uint)bVar1 * 7]), 0 < iVar2)) break;
    iVar4 = iVar4 + 1;
    if (9 < iVar4) {
      uVar3 = 0xffffffff;
      if (iVar5 == 0) {
        uVar3 = (uint)(byte)(&DAT_800919e7)[(uint)DAT_8009c504 * 0x14];
      }
      return uVar3;
    }
  }
  return (uint)*(byte *)((&DAT_801a7ad8)[(uint)bVar1 * 7] + 0x6a);
}

