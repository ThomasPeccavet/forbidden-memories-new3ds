/* Analysis pseudo-C, not buildable source. */

void FUN_8005ee7c(int param_1,int *param_2,int *param_3)

{
  bool bVar1;
  code *pcVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  short *psVar6;
  short *psVar7;
  int iVar8;
  uint uVar9;
  
  iVar8 = 0;
  uVar9 = (uint)*(ushort *)(*param_3 + 2);
  if (uVar9 != 0) {
    bVar1 = 1 < param_1;
    psVar7 = (short *)(*param_3 + 4);
    do {
      psVar6 = psVar7 + 6;
      if (*param_2 == 0x2000001) {
        iVar5 = 0;
        if (param_3[6] != 0) {
          puVar4 = (ushort *)(param_3[6] + *(int *)(psVar7 + 10) * 4);
          if (0 < psVar7[9]) {
            do {
              if (!bVar1) {
                *puVar4 = 0;
              }
              iVar3 = 1;
              puVar4 = puVar4 + 1;
              if (1 < psVar7[8]) {
                do {
                  iVar3 = iVar3 + 1;
                  *puVar4 = *puVar4 | 0x8000;
                  puVar4 = puVar4 + 1;
                } while (iVar3 < psVar7[8]);
              }
              iVar5 = iVar5 + 1;
            } while (iVar5 < psVar7[9]);
          }
          if (bVar1) {
            if (psVar7[7] < 0x100) {
              *psVar6 = *psVar6 + 0x280;
              psVar7[7] = (psVar7[7] & 0xfU) + 0xd0;
            }
            iVar5 = (int)psVar7[1] + (int)psVar7[3] + -0x200;
            if (0 < iVar5) {
              psVar7[3] = psVar7[3] - (short)iVar5;
            }
          }
          else {
            iVar5 = (int)psVar7[7];
            *psVar6 = 0x280;
            if (7 < iVar5) {
              if (iVar5 < 0) {
                iVar5 = iVar5 + 7;
              }
              psVar7[7] = psVar7[7] + (short)(iVar5 >> 3) * -8;
            }
            psVar7[7] = psVar7[7] + 0xd0 + (short)param_1 * 0x10;
          }
          psVar6 = psVar7 + 0xc;
        }
      }
      if (!bVar1) {
        *psVar7 = *psVar7 + -0x280 + (short)param_1 * 0x100;
      }
      iVar8 = iVar8 + 1;
      psVar7 = psVar6;
    } while (iVar8 < (int)uVar9);
  }
  pcVar2 = (code *)FUN_8005f06c(*param_2);
  (*pcVar2)(param_3);
  FUN_8007fc64(0);
  *(undefined1 **)param_2[1] = &LAB_80089da8;
  return;
}

