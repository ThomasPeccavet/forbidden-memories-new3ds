/* Analysis pseudo-C, not buildable source. */

void FUN_80071a64(void)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  iVar4 = 0;
  iVar3 = 0xb;
  psVar2 = &DAT_801ab084;
  do {
    if (*psVar2 != 0) {
      iVar4 = iVar4 + 1;
    }
    iVar3 = iVar3 + 1;
    psVar2 = psVar2 + 6;
  } while (iVar3 < 0x38);
  *(int *)(&DAT_800f6f20 + iVar1 * 4) = iVar4 + -5;
  return;
}

