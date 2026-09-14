/* Analysis pseudo-C, not buildable source. */

void FUN_80072714(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_20;
  int local_1c;
  
  iVar1 = FUN_80070bb8();
  iVar5 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar4 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  FUN_80070df0(iVar4,&local_20,&local_1c);
  if (local_20 <= local_1c) {
    psVar2 = (short *)(&DAT_801ab000 + local_20 * 0xc);
    do {
      if (((*psVar2 == iVar5) &&
          (((((iVar4 != 1 && (iVar4 != 3)) && (iVar4 != 6)) && (iVar4 != 8)) ||
           ((psVar2[3] & 0x4000U) == 0)))) &&
         (((iVar3 != 1 || (iVar4 < 5)) || ((psVar2[3] & 0x1000U) == 0)))) break;
      local_20 = local_20 + 1;
      psVar2 = psVar2 + 6;
    } while (local_20 <= local_1c);
    if (local_20 <= local_1c) {
      *(int *)(&DAT_800f6f20 + iVar1 * 4) = local_20;
      return;
    }
  }
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  return;
}

