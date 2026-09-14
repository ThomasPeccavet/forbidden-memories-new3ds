/* Analysis pseudo-C, not buildable source. */

void FUN_80072590(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int local_18;
  int local_14;
  
  iVar1 = FUN_80070bb8();
  iVar4 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  FUN_80070df0(iVar3,&local_18,&local_14);
  if (local_18 <= local_14) {
    psVar2 = (short *)(&DAT_801ab000 + local_18 * 0xc);
    do {
      if (((((iVar3 != 1) && (iVar3 != 3)) && (iVar3 != 6)) && (iVar3 != 8)) ||
         ((psVar2[3] & 0x4000U) == 0)) {
        if (*psVar2 == 0) {
          if (iVar4 == 0) break;
        }
        else if ((psVar2[3] & 0x1000U) == 0) {
          if (iVar4 == 1) break;
        }
        else if (iVar4 == 2) break;
      }
      psVar2 = psVar2 + 6;
      local_18 = local_18 + 1;
    } while (local_18 <= local_14);
    if (local_18 <= local_14) {
      *(int *)(&DAT_800f6f20 + iVar1 * 4) = local_18;
      return;
    }
  }
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  return;
}

