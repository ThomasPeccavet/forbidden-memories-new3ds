/* Analysis pseudo-C, not buildable source. */

void FUN_80072cbc(void)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = FUN_80070bb8();
  iVar5 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar2 = FUN_80070bb8();
  pbVar3 = &DAT_800ec210;
  iVar1 = 0;
  while( true ) {
    iVar4 = (uint)*pbVar3 * 0xc;
    if ((*(short *)(&DAT_801ab000 + iVar4) != 0) && ((char)(&DAT_801ab008)[iVar4] == iVar5)) break;
    iVar4 = iVar1 + 1;
    pbVar3 = &DAT_800ec211 + iVar1;
    iVar1 = iVar4;
    if (4 < iVar4) {
      *(undefined4 *)(&DAT_800f6f20 + iVar2 * 4) = 0;
      return;
    }
  }
  *(uint *)(&DAT_800f6f20 + iVar2 * 4) = (uint)*pbVar3;
  return;
}

