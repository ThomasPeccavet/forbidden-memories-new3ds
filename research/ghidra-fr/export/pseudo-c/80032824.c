/* Analysis pseudo-C, not buildable source. */

void FUN_80032824(int *param_1,int param_2,int param_3,undefined1 param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  short *psVar3;
  int *piVar4;
  int *piVar5;
  undefined1 *puVar6;
  ushort *puVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int unaff_gp;
  
  FUN_80032754();
  FUN_8004022c(0x70e0);
  DAT_8009c4c2 = 0;
  DAT_8009c4c0 = 0;
  FUN_8003279c();
  iVar12 = 0;
  piVar11 = param_1 + 1;
  *(int **)(unaff_gp + 0x3ec) = param_1;
  *(undefined1 *)((int)param_1 + 0x6343) = param_4;
  *param_1 = param_2;
  param_1[0x18d1] = param_3;
  *(undefined1 *)((int)param_1 + 0x6342) = 0;
  *(undefined1 *)((int)param_1 + 0xc686) = 0;
  do {
    if (*param_1 != 0) {
      *(undefined1 *)((int)piVar11 + 0x6066) = 0;
      iVar9 = 1;
      piVar5 = param_1;
      do {
        *(undefined1 *)((int)piVar5 + 0x606b) = 0;
        iVar10 = 0xf;
        psVar3 = &DAT_801d07da;
        do {
          if (*psVar3 == iVar9) {
            *(char *)((int)piVar5 + 0x606b) = (char)iVar10 + '\x01';
          }
          iVar10 = iVar10 + -1;
          psVar3 = psVar3 + -1;
        } while (-1 < iVar10);
        iVar9 = iVar9 + 1;
        piVar5 = (int *)((int)piVar5 + 1);
      } while (iVar9 < 0x2d3);
      iVar9 = 0;
      *(undefined1 *)((int)piVar11 + 0x5a93) = 1;
      iVar10 = 0;
      *(undefined2 *)((int)piVar11 + 0x5a8a) = 0;
      *(undefined2 *)(piVar11 + 0x16a2) = 0;
      *(undefined1 *)(piVar11 + 0x16a5) = 0;
      *(undefined1 *)((int)piVar11 + 0x5a92) = 0;
      piVar5 = param_1 + 0xb56;
      *(byte *)((int)piVar11 + 0x5a91) = DAT_80092225 & 0xf;
      puVar7 = (ushort *)*param_1;
      do {
        *(undefined1 *)((int)piVar5 + 5) = 0;
        *(short *)(piVar5 + -1) = 0;
        uVar1 = *puVar7;
        if (uVar1 != 0) {
          *(ushort *)(piVar5 + -1) = uVar1;
          piVar4 = &DAT_801d4244 + (uVar1 - 1);
          *(undefined1 *)((int)piVar5 + 5) = 1;
          *(byte *)((int)piVar5 + 2) = (byte)(*piVar4 >> 0x1a) & 0x1f;
          *(ushort *)((int)piVar5 + -2) = ((ushort)*piVar4 & 0x1ff) * 10;
          iVar9 = iVar9 + 1;
          *(ushort *)piVar5 = ((ushort)(*piVar4 >> 9) & 0x1ff) * 10;
        }
        iVar10 = iVar10 + 1;
        piVar5 = piVar5 + 4;
        puVar7 = puVar7 + 1;
      } while (iVar10 < 0x28);
      *(undefined2 *)(param_1 + 0xbf5) = 0xffff;
      piVar11[0x16a7] = iVar9;
      *(undefined2 *)(piVar11 + 0x16a3) = 0x28;
      *(undefined2 *)((int)piVar11 + 0x5a8e) = 0x28;
      FUN_80033144(param_1 + 0xb54);
      FUN_800323f0(param_1);
      iVar10 = 0;
      iVar9 = 0;
      *(undefined1 *)((int)piVar11 + 0x2d47) = 0;
      *(undefined2 *)((int)piVar11 + 0x2d3e) = 0;
      *(undefined2 *)(piVar11 + 0xb4f) = 0;
      *(undefined2 *)(piVar11 + 0xb50) = 0x2d2;
      *(undefined1 *)(piVar11 + 0xb52) = 0;
      *(undefined1 *)((int)piVar11 + 0x2d46) = 0;
      puVar6 = (undefined1 *)((int)piVar11 + 0xd);
      *(byte *)((int)piVar11 + 0x2d45) =
           (&DAT_80092215)[(uint)*(byte *)((int)piVar11 + 0x2d47) * 0x10] & 0xf;
      pbVar8 = (byte *)(*param_1 + 0x50);
      piVar5 = &DAT_801d4244;
      do {
        *puVar6 = 0;
        *(short *)(puVar6 + -9) = (short)iVar9 + 1;
        puVar6[-3] = (byte)(*piVar5 >> 0x1a) & 0x1f;
        *(ushort *)(puVar6 + -7) = ((ushort)*piVar5 & 0x1ff) * 10;
        *(ushort *)(puVar6 + -5) = ((ushort)(*piVar5 >> 9) & 0x1ff) * 10;
        *(byte *)((int)param_1 + iVar9 + 0x5d98) = *pbVar8;
        if (*pbVar8 == 0) {
          if (*(char *)((int)param_1 + iVar9 + 0x5ac5) != '\0') {
            *puVar6 = 0x80;
          }
        }
        else {
          *puVar6 = 1;
          iVar10 = iVar10 + (uint)*pbVar8;
        }
        piVar5 = piVar5 + 1;
        iVar9 = iVar9 + 1;
        puVar6 = puVar6 + 0x10;
        pbVar8 = pbVar8 + 1;
      } while (iVar9 < 0x2d2);
      *(undefined2 *)(piVar11 + 0xb49) = 0;
      piVar11[0x16a6] = iVar10;
      *(undefined2 *)((int)piVar11 + 0x2d42) = 0x2d2;
      *(undefined2 *)(piVar11 + 0xb50) = 0x2d2;
      FUN_80033144(piVar11);
    }
    iVar12 = iVar12 + 1;
    piVar11 = piVar11 + 0x18d1;
    param_1 = param_1 + 0x18d1;
  } while (iVar12 < 2);
  iVar10 = *(int *)(unaff_gp + 0x3ec);
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0,0,0,4,0,0xc,0x208);
  uVar2 = FUN_80040350();
  iVar9 = FUN_800403d0(uVar2,6);
  *(undefined1 *)(iVar9 + 0x67) = 0;
  uVar2 = *(undefined4 *)(iVar12 + 0x30);
  *(code **)(iVar9 + 0x4c) = FUN_80031b58;
  *(undefined4 *)(iVar9 + 0x30) = uVar2;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x140,0,0,4,1,0xc,0x208);
  uVar2 = FUN_80040350();
  iVar9 = FUN_800403d0(uVar2,6);
  *(undefined1 *)(iVar9 + 0x67) = 1;
  uVar2 = *(undefined4 *)(iVar12 + 0x30);
  *(code **)(iVar9 + 0x4c) = FUN_80031b58;
  *(undefined4 *)(iVar9 + 0x30) = uVar2;
  *(undefined2 *)(iVar10 + 0x633e) = 2;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x136,0x2a,0,4,0xc,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,8);
  *(int *)(iVar10 + 0x2d3c) = iVar12;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x26a,0x2a,0,4,0xc,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,8);
  *(int *)(iVar10 + 0x5a88) = iVar12;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0,0x2b,0,4,2,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,10);
  *(int *)(iVar10 + 0x2d38) = iVar12;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x148,0x2b,0,4,3,0xc,0x218);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,10);
  *(int *)(iVar10 + 0x5a84) = iVar12;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0,0,0,4,9,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,10);
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x140,0,0,4,10,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,10);
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0,0,0,4,0xb,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,0xfffffffc);
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,2);
  FUN_80040800(iVar12,0x140,0,0,4,0xb,0xc,0x208);
  *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x20;
  FUN_80042c1c(iVar12,0xfffffffc);
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,4);
  FUN_80042b0c(iVar12,0);
  *(uint *)(iVar12 + 4) = *(uint *)(iVar12 + 4) | 0x60000000;
  FUN_80042c1c(iVar12,0xfffffffd);
  *(undefined4 *)(iVar12 + 0x28) = 0xf80000;
  *(undefined4 *)(iVar12 + 0x30) = 0xf80140;
  *(undefined4 *)(iVar12 + 0x38) = 0x1000000;
  *(undefined4 *)(iVar12 + 0x40) = 0x1000140;
  *(undefined4 *)(iVar12 + 0x3c) = 0x808080;
  *(undefined4 *)(iVar12 + 0x44) = 0x808080;
  uVar2 = FUN_80040350();
  iVar12 = FUN_800403d0(uVar2,4);
  FUN_80042b0c(iVar12,0);
  *(uint *)(iVar12 + 4) = *(uint *)(iVar12 + 4) | 0x60000000;
  FUN_80042c1c(iVar12,0xfffffffd);
  *(undefined4 *)(iVar12 + 0x30) = 0x140;
  *(undefined4 *)(iVar12 + 0x28) = 0;
  *(undefined4 *)(iVar12 + 0x38) = 0x80000;
  *(undefined4 *)(iVar12 + 0x40) = 0x80140;
  *(undefined4 *)(iVar12 + 0x2c) = 0x808080;
  *(undefined4 *)(iVar12 + 0x34) = 0x808080;
  uVar2 = FUN_80040350();
  uVar2 = FUN_800403d0(uVar2,2);
  FUN_80040800(uVar2,0x140,0,3,0,3,0xb,0x2f8);
  FUN_80042c1c(uVar2,0xfffffffc);
  FUN_80032230(iVar10);
  return;
}

