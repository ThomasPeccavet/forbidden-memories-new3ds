/* Analysis pseudo-C, not buildable source. */

void FUN_80071cc8(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int local_38;
  int local_34;
  int local_30;
  
  iVar1 = FUN_80070bb8();
  iVar7 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = 0;
  iVar2 = FUN_80070bb8();
  iVar5 = *(int *)(&DAT_800f6f20 + iVar2 * 4);
  sVar6 = -1;
  iVar2 = FUN_80070bb8();
  iVar9 = *(int *)(&DAT_800f6f20 + iVar2 * 4);
  iVar2 = FUN_80070bb8();
  uVar8 = *(undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
  local_30 = FUN_80070bb8();
  FUN_80070d64(iVar5,&local_38,&local_34);
  if (local_38 <= local_34) {
    psVar4 = (short *)(&DAT_801ab000 + local_38 * 0xc);
    iVar2 = local_38;
    do {
      if (((((*psVar4 != 0) &&
            ((((iVar5 != 1 && (iVar5 != 4)) && (iVar5 != 5)) || ((psVar4[3] & 0x4000U) == 0)))) &&
           ((iVar5 != 4 || ((psVar4[3] & 0x800U) == 0)))) &&
          ((iVar5 != 5 || ((psVar4[3] & 0x800U) != 0)))) &&
         ((((2 < iVar5 - 3U || ((psVar4[3] & 0x1000U) == 0)) || (iVar9 != 1)) &&
          (iVar3 = FUN_80070f4c(uVar8,iVar2), iVar3 == 0)))) {
        if ((iVar7 != 1) && (sVar6 < psVar4[1])) {
          iVar1 = iVar2;
          sVar6 = psVar4[1];
        }
        if ((iVar7 != 0) && (sVar6 < psVar4[2])) {
          iVar1 = iVar2;
          sVar6 = psVar4[2];
        }
      }
      iVar2 = iVar2 + 1;
      psVar4 = psVar4 + 6;
    } while (iVar2 <= local_34);
  }
  *(int *)(&DAT_800f6f20 + local_30 * 4) = iVar1;
  return;
}

