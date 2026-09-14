/* Analysis pseudo-C, not buildable source. */

void FUN_80072894(void)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int local_30;
  int local_2c;
  
  iVar1 = FUN_80070bb8();
  iVar8 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar5 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar7 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  uVar6 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  FUN_80070df0(iVar5,&local_30,&local_2c);
  if (local_30 <= local_2c) {
    psVar3 = (short *)(&DAT_801ab000 + local_30 * 0xc);
    iVar4 = local_30;
    do {
      if (((((*psVar3 != 0) && ((char)psVar3[4] == iVar8)) &&
           (((iVar5 != 1 && (((iVar5 != 3 && (iVar5 != 6)) && (iVar5 != 8)))) ||
            ((psVar3[3] & 0x4000U) == 0)))) &&
          (((iVar7 != 1 || (iVar5 < 5)) || ((psVar3[3] & 0x1000U) == 0)))) &&
         (iVar2 = FUN_80070f4c(uVar6,iVar4), iVar2 == 0)) break;
      iVar4 = iVar4 + 1;
      psVar3 = psVar3 + 6;
    } while (iVar4 <= local_2c);
    if (iVar4 <= local_2c) {
      *(int *)(&DAT_800f6f20 + iVar1 * 4) = iVar4;
      return;
    }
  }
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  return;
}

