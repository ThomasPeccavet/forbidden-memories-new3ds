/* Analysis pseudo-C, not buildable source. */

void FUN_80072c08(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  pbVar2 = &DAT_800ec210;
  iVar4 = 0;
  while( true ) {
    iVar3 = (uint)*pbVar2 * 0xc;
    if ((*(short *)(&DAT_801ab000 + iVar3) != 0) && ((char)(&DAT_801ab008)[iVar3] < '\x14')) break;
    iVar3 = iVar4 + 1;
    pbVar2 = &DAT_800ec211 + iVar4;
    iVar4 = iVar3;
    if (4 < iVar3) {
      *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
      return;
    }
  }
  *(uint *)(&DAT_800f6f20 + iVar1 * 4) = (uint)*pbVar2;
  return;
}

