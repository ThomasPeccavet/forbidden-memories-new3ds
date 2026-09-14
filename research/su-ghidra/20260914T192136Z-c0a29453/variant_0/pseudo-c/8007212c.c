/* Analysis pseudo-C, not buildable source. */

void FUN_8007212c(void)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  
  iVar4 = FUN_80070bb8();
  iVar8 = *(int *)(&DAT_800f6f20 + iVar4 * 4);
  sVar10 = 9999;
  iVar4 = FUN_80070bb8();
  iVar11 = *(int *)(&DAT_800f6f20 + iVar4 * 4);
  iVar4 = 0;
  iVar5 = FUN_80070bb8();
  iVar9 = 1;
  iVar6 = iVar8 * 0xc;
  psVar3 = (short *)&DAT_801ab000;
  do {
    if ((psVar3[6] != 0) && ((psVar3[9] & 0x4000U) == 0)) {
      if (iVar11 == 0) {
        sVar1 = psVar3[7];
        sVar2 = (&DAT_801ab002)[iVar8 * 6];
      }
      else {
        sVar1 = psVar3[7];
        sVar2 = *(short *)(&DAT_801ab004 + iVar6);
      }
      iVar7 = FUN_8002cd54((int)*(char *)((int)psVar3 + 0x15),(int)(char)(&DAT_801ab009)[iVar6]);
      if (0 < ((int)sVar1 - (int)sVar2) + iVar7) {
        if (psVar3[7] < sVar10) {
          iVar4 = iVar9;
          sVar10 = psVar3[7];
        }
      }
    }
    iVar9 = iVar9 + 1;
    psVar3 = psVar3 + 6;
  } while (iVar9 < 6);
  *(int *)(&DAT_800f6f20 + iVar5 * 4) = iVar4;
  return;
}

