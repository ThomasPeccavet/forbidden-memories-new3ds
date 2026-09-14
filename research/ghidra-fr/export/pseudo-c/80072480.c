/* Analysis pseudo-C, not buildable source. */

void FUN_80072480(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int local_18;
  int local_14;
  
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar4 = 0;
  iVar1 = FUN_80070bb8();
  FUN_80070df0(iVar3,&local_18,&local_14);
  if (local_18 <= local_14) {
    psVar2 = (short *)(&DAT_801ab000 + local_18 * 0xc);
    do {
      if ((*psVar2 != 0) &&
         (((((iVar3 != 1 && (iVar3 != 3)) && (iVar3 != 6)) && (iVar3 != 8)) ||
          ((psVar2[3] & 0x4000U) == 0)))) {
        iVar4 = iVar4 + 1;
      }
      local_18 = local_18 + 1;
      psVar2 = psVar2 + 6;
    } while (local_18 <= local_14);
  }
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = iVar4;
  return;
}

