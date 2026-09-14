/* Analysis pseudo-C, not buildable source. */

int FUN_800250d8(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  DAT_8009c558 = 0;
  iVar1 = (uint)DAT_8009c504 * 0x14;
  while( true ) {
    uVar2 = (uint)(byte)(&DAT_800919e0)[iVar1];
    if ((((&DAT_801a7aee)[uVar2 * 0xe] & 0x8000) != 0) &&
       (*(short *)(&DAT_801a7ae4 + uVar2 * 0x1c) == param_1)) break;
    iVar3 = iVar3 + 1;
    iVar1 = iVar3 + (uint)DAT_8009c504 * 0x14;
    if (4 < iVar3) {
      return 0;
    }
  }
  DAT_8009c558 = (short)param_1;
  DAT_8009c5b4 = *(undefined1 *)((&DAT_801a7ad8)[uVar2 * 7] + 0x6a);
  return param_1;
}

