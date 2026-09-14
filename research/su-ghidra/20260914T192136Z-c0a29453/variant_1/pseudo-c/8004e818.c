/* Analysis pseudo-C, not buildable source. */

void FUN_8004e818(short *param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short *psVar6;
  uint uVar7;
  short *psVar8;
  int iVar9;
  int iVar10;
  short *psVar11;
  short *psVar12;
  int unaff_gp;
  short *psVar13;
  short local_80;
  short local_7e;
  short local_7c;
  short local_78 [32];
  int local_38;
  uint local_34;
  short *local_30;
  
  iVar2 = (int)param_1[0x10];
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  local_38 = iVar2;
  if (iVar2 < 1) {
    local_38 = 1;
  }
  local_38 = local_38 << 1;
  FUN_8004fb40(param_1);
  iVar3 = *(int *)(unaff_gp + 0x74);
  param_1[0x12] = 0;
  if (*(char *)(iVar3 + 0x26) == '\0') {
    *(undefined1 *)(param_1 + 0x13) = 1;
    if (iVar2 < 0x4000) {
      param_1[0x11] = (short)local_38;
    }
    else {
      param_1[0x11] = 0x4000;
    }
    if (param_1[0x10] < 0) {
      iVar2 = 0;
      local_34 = 0x10624dd3;
      local_30 = local_78;
      psVar11 = param_1 + 1;
      psVar12 = &DAT_800f3ea8;
      psVar13 = param_1;
      do {
        sVar5 = psVar11[2];
        uVar1 = psVar11[2];
        if (sVar5 == 4) {
          sVar5 = DAT_800f3eb8;
          if (DAT_800f3eb8 < *psVar13) {
            sVar5 = *psVar13;
          }
          iVar3 = (int)*psVar11;
          if (iVar3 < 0) {
            iVar3 = -iVar3;
          }
          uVar1 = param_1[0x11];
          uVar7 = (uint)((ulonglong)
                         (uint)(local_38 *
                                ((int)((longlong)(sVar5 * 0x188c) * (longlong)(int)local_34 >> 0x26)
                                - (sVar5 * 0x188c >> 0x1f)) * iVar3) * (ulonglong)local_34 >> 0x32);
LAB_8004ebac:
          if (uVar1 < uVar7) {
            param_1[0x11] = (short)uVar7;
          }
        }
        else if (sVar5 < 5) {
          iVar3 = 0;
          if (sVar5 == 1) {
            iVar9 = 0;
            psVar8 = local_30;
            do {
              FUN_8004ec04(param_1,iVar2,iVar9,0x1e,psVar8);
              iVar9 = iVar9 + 1;
              psVar8 = psVar8 + 3;
            } while (iVar9 < 10);
            iVar9 = 1;
            iVar10 = 0;
            psVar8 = local_30;
            do {
              psVar6 = (short *)((int)local_30 + iVar10);
              iVar4 = (int)*psVar6 - (int)psVar8[3];
              iVar9 = iVar9 + 1;
              iVar10 = iVar10 + 6;
              iVar4 = FUN_80086dd8(iVar4 * iVar4 +
                                   ((int)psVar6[1] - (int)psVar8[4]) *
                                   ((int)psVar6[1] - (int)psVar8[4]) +
                                   ((int)psVar6[2] - (int)psVar8[5]) *
                                   ((int)psVar6[2] - (int)psVar8[5]));
              iVar3 = iVar3 + iVar4;
              psVar8 = psVar8 + 3;
            } while (iVar9 < 10);
            uVar1 = param_1[0x11];
            uVar7 = (int)((longlong)(local_38 * iVar3) * (longlong)(int)local_34 >> 0x26) -
                    (local_38 * iVar3 >> 0x1f);
            goto LAB_8004ebac;
          }
        }
        else if ((sVar5 < 0x82) && (0x7f < sVar5)) {
          iVar3 = FUN_8005bee0((int)(short)(uVar1 & 0xff7f));
          if (iVar3 == 1) {
            FUN_8005c0b8((int)(short)(uVar1 & 0xff7f),&local_80);
            local_80 = local_80 + *psVar13;
            local_7e = local_7e + *psVar11;
            local_7c = local_7c + psVar11[1];
            iVar3 = FUN_80086dd8(((int)local_80 - (int)*psVar12) * ((int)local_80 - (int)*psVar12) +
                                 ((int)local_7e - (int)psVar12[1]) *
                                 ((int)local_7e - (int)psVar12[1]) +
                                 ((int)local_7c - (int)psVar12[2]) *
                                 ((int)local_7c - (int)psVar12[2]));
            uVar7 = (int)((longlong)(local_38 * iVar3) * (longlong)(int)local_34 >> 0x26) -
                    (local_38 * iVar3 >> 0x1f);
            if ((ushort)param_1[0x11] < uVar7) {
              param_1[0x11] = (short)uVar7;
            }
          }
        }
        psVar12 = psVar12 + 4;
        iVar2 = iVar2 + 1;
        psVar11 = psVar11 + 4;
        psVar13 = psVar13 + 4;
      } while (iVar2 < 2);
    }
  }
  return;
}

