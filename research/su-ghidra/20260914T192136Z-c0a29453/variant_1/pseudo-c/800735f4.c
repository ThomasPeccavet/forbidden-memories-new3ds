/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8007371c) */
/* WARNING: Removing unreachable block (ram,0x80073740) */
/* WARNING: Removing unreachable block (ram,0x8007372c) */
/* WARNING: Removing unreachable block (ram,0x80073758) */

void FUN_800735f4(void)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  
  iVar3 = FUN_80070bb8();
  iVar3 = *(int *)(&DAT_800f6f20 + iVar3 * 4);
  FUN_80070bb8();
  DAT_800f7008 = 0;
  do {
    do {
      do {
      } while (DAT_801ab00c == 0);
    } while ((DAT_801ab012 & 0x4000) != 0);
    iVar7 = 0x38;
    psVar6 = &DAT_801ab2a0;
    do {
      if (*psVar6 != 0) {
        uVar2 = psVar6[3];
        if ((((uVar2 & 0x4000) == 0) && ((uVar2 & 0x800) == 0)) &&
           ((iVar3 == 0 || ((uVar2 & 0x1000) == 0)))) {
          iVar5 = (int)DAT_801ab00e;
          sVar1 = psVar6[1];
          iVar4 = FUN_8002cd54((int)DAT_801ab015,(int)*(char *)((int)psVar6 + 9));
          iVar4 = (iVar5 - sVar1) + iVar4;
          if ((int)(uint)DAT_800f7008 < iVar4) {
            DAT_800f7008 = (ushort)iVar4;
            DAT_800f700a = 1;
            DAT_800f700b = (undefined1)iVar7;
          }
        }
      }
      iVar7 = iVar7 + 1;
      psVar6 = psVar6 + 6;
    } while (iVar7 < 0x3d);
  } while( true );
}

