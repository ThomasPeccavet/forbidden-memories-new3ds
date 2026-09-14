/* Analysis pseudo-C, not buildable source. */

void FUN_80071eec(void)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  short *psVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int local_38;
  int local_34;
  int local_30;
  
  iVar3 = FUN_80070bb8();
  iVar10 = *(int *)(&DAT_800f6f20 + iVar3 * 4);
  iVar3 = 0;
  iVar4 = FUN_80070bb8();
  iVar9 = *(int *)(&DAT_800f6f20 + iVar4 * 4);
  sVar8 = 9999;
  iVar4 = FUN_80070bb8();
  iVar12 = *(int *)(&DAT_800f6f20 + iVar4 * 4);
  iVar4 = FUN_80070bb8();
  uVar11 = *(undefined4 *)(&DAT_800f6f20 + iVar4 * 4);
  local_30 = FUN_80070bb8();
  FUN_80070d64(iVar9,&local_38,&local_34);
  if (local_38 <= local_34) {
    psVar7 = (short *)(&DAT_801ab000 + local_38 * 0xc);
    iVar4 = local_38;
    do {
      if ((((*psVar7 != 0) &&
           ((((iVar9 != 1 && (iVar9 != 4)) && (iVar9 != 5)) || ((psVar7[3] & 0x4000U) == 0)))) &&
          (((iVar9 != 4 || ((psVar7[3] & 0x800U) == 0)) &&
           ((iVar9 != 5 || ((psVar7[3] & 0x800U) != 0)))))) &&
         ((((2 < iVar9 - 3U || ((psVar7[3] & 0x1000U) == 0)) || (iVar12 != 1)) &&
          (iVar5 = FUN_80070f4c(uVar11,iVar4), iVar5 == 0)))) {
        if (iVar10 == 0) {
          sVar6 = psVar7[1];
          bVar2 = sVar6 < sVar8;
LAB_800720c0:
          if (!bVar2) goto LAB_800720d0;
        }
        else {
          if (iVar10 == 1) {
            sVar6 = psVar7[2];
            bVar2 = sVar6 < sVar8;
            goto LAB_800720c0;
          }
          sVar1 = psVar7[1];
          sVar6 = psVar7[2];
          if (sVar1 <= sVar6) {
            bVar2 = sVar6 < sVar8;
            goto LAB_800720c0;
          }
          sVar6 = sVar1;
          if (sVar8 <= sVar1) goto LAB_800720d0;
        }
        iVar3 = iVar4;
        sVar8 = sVar6;
      }
LAB_800720d0:
      iVar4 = iVar4 + 1;
      psVar7 = psVar7 + 6;
    } while (iVar4 <= local_34);
  }
  *(int *)(&DAT_800f6f20 + local_30 * 4) = iVar3;
  return;
}

