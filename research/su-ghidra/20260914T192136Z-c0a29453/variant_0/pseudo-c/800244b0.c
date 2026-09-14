/* Analysis pseudo-C, not buildable source. */

void FUN_800244b0(short *param_1,short *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  short sVar2;
  byte *pbVar3;
  uint uVar4;
  ushort *puVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  undefined1 *puVar9;
  int iVar10;
  byte local_300 [728];
  
  if (param_1 == (short *)0x0) {
    iVar7 = 0x2d1;
    do {
      pbVar3 = local_300 + iVar7;
      iVar7 = iVar7 + -1;
      *pbVar3 = 0;
    } while (-1 < iVar7);
    iVar10 = 0;
    psVar6 = param_2;
    puVar9 = param_3;
    do {
      uVar4 = FUN_8008f708();
      iVar7 = 0;
      iVar8 = 0;
      puVar5 = &DAT_801781d8;
      do {
        iVar7 = iVar7 + (uint)*puVar5;
        if ((int)((uVar4 & 0x7ff) + 1) <= iVar7) {
          pbVar3 = local_300 + iVar8;
          if (*pbVar3 < 3) {
            *psVar6 = (short)iVar8 + 1;
            *puVar9 = (char)iVar10;
            iVar10 = iVar10 + 1;
            psVar6 = psVar6 + 1;
            puVar9 = puVar9 + 1;
            *pbVar3 = *pbVar3 + 1;
          }
          break;
        }
        iVar8 = iVar8 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar8 < 0x2d0);
      iVar7 = 0;
    } while (iVar10 < 0x28);
  }
  else {
    iVar7 = 0;
    psVar6 = param_2;
    puVar9 = param_3;
    do {
      sVar2 = *param_1;
      param_1 = param_1 + 1;
      *psVar6 = sVar2;
      *puVar9 = (char)iVar7;
      puVar9 = puVar9 + 1;
      iVar7 = iVar7 + 1;
      psVar6 = psVar6 + 1;
    } while (iVar7 < 0x28);
    iVar7 = 0;
  }
  do {
    iVar10 = FUN_80035dfc(0x28);
    iVar8 = FUN_80035dfc(0x28);
    sVar2 = param_2[iVar10];
    param_2[iVar10] = param_2[iVar8];
    param_2[iVar8] = sVar2;
    uVar1 = param_3[iVar10];
    iVar7 = iVar7 + 1;
    param_3[iVar10] = param_3[iVar8];
    param_3[iVar8] = uVar1;
  } while (iVar7 < 0xa0);
  return;
}

