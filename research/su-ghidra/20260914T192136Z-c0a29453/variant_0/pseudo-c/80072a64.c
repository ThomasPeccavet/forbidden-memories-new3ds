/* Analysis pseudo-C, not buildable source. */

void FUN_80072a64(void)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  
  iVar1 = FUN_80070bb8();
  uVar7 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar4 = 1;
  iVar1 = FUN_80070bb8();
  iVar6 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  uVar5 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  psVar3 = &DAT_801ab00c;
  while (((*psVar3 == 0 ||
          (((iVar6 == 1 && ((psVar3[3] & 0x4000U) != 0)) ||
           (iVar2 = FUN_80070f4c(uVar5,iVar4), iVar2 != 0)))) ||
         (iVar2 = FUN_80019998(uVar7,(int)*psVar3), iVar2 == 0))) {
    iVar4 = iVar4 + 1;
    psVar3 = psVar3 + 6;
    if (5 < iVar4) {
      *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
      return;
    }
  }
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = iVar4;
  return;
}

