/* Analysis pseudo-C, not buildable source. */

void FUN_80088bd8(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  undefined4 uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  
  iVar15 = *param_1;
  uVar13 = (int)(short)param_1[1] >> 0x1f;
  uVar11 = iVar15 >> 0x1f;
  uVar9 = (int)(short)iVar15 >> 0x1f;
  uVar1 = *(int *)(&DAT_80096938 + (((int)(short)param_1[1] + uVar13 ^ uVar13) & 0xfff) * 4) *
          0x10000 + uVar13 ^ uVar13;
  uVar2 = *(int *)(&DAT_80096938 + (((iVar15 >> 0x10) + uVar11 ^ uVar11) & 0xfff) * 4) * 0x10000 +
          uVar11 ^ uVar11;
  uVar3 = *(int *)(&DAT_80096938 + (((int)(short)iVar15 + uVar9 ^ uVar9) & 0xfff) * 4) * 0x10000 +
          uVar9 ^ uVar9;
  iVar7 = (int)((*(int *)(&DAT_80096938 + (((int)(short)iVar15 + uVar9 ^ uVar9) & 0xfff) * 4) >>
                0x10) << 0x10 | uVar3 >> 0x10) >> 0x10;
  setCopReg(2,0x4000,iVar7);
  iVar6 = (int)(short)(uVar2 >> 0x10);
  setCopReg(2,0x4800,iVar6);
  iVar5 = (int)(short)(uVar1 >> 0x10);
  setCopReg(2,0x5000,iVar5);
  iVar4 = (int)((*(int *)(&DAT_80096938 + (((int)(short)param_1[1] + uVar13 ^ uVar13) & 0xfff) * 4)
                >> 0x10) << 0x10 | uVar1 >> 0x10) >> 0x10;
  setCopReg(2,0x5800,iVar4);
  copFunction(2,0x198003d);
  iVar15 = (int)((*(int *)(&DAT_80096938 + (((iVar15 >> 0x10) + uVar11 ^ uVar11) & 0xfff) * 4) >>
                 0x10) << 0x10 | uVar2 >> 0x10) >> 0x10;
  uVar8 = getCopReg(2,0x4800);
  iVar10 = getCopReg(2,0x5000);
  iVar12 = getCopReg(2,0x5800);
  iVar18 = (int)(short)(uVar3 >> 0x10);
  setCopReg(2,0x4000,iVar18);
  setCopReg(2,0x4800,iVar6);
  setCopReg(2,0x5000,iVar5);
  setCopReg(2,0x5800,iVar4);
  copFunction(2,0x198003d);
  *(short *)(param_2 + 4) = (short)(iVar15 * iVar7 >> 0xc);
  uVar14 = getCopReg(2,0x4800);
  iVar16 = getCopReg(2,0x5000);
  iVar17 = getCopReg(2,0x5800);
  setCopReg(2,0x4000,iVar4);
  setCopReg(2,0x4800,iVar15);
  setCopReg(2,0x5000,uVar14);
  setCopReg(2,0x5800,uVar8);
  copFunction(2,0x198003d);
  uVar1 = getCopReg(2,0x4800);
  iVar4 = getCopReg(2,0x5000);
  iVar7 = getCopReg(2,0x5800);
  setCopReg(2,0x4800,iVar15);
  setCopReg(2,0x4000,iVar5);
  setCopReg(2,0x5000,uVar14);
  setCopReg(2,0x5800,uVar8);
  param_2[3] = -iVar6 & 0xffffU | (iVar15 * iVar18 >> 0xc) << 0x10;
  copFunction(2,0x198003d);
  *param_2 = (iVar4 - iVar10) * 0x10000 | uVar1 & 0xffff;
  iVar4 = getCopReg(2,0x4800);
  iVar15 = getCopReg(2,0x5000);
  iVar5 = getCopReg(2,0x5800);
  param_2[1] = iVar4 << 0x10 | iVar7 + iVar16 & 0xffffU;
  param_2[2] = iVar15 + iVar12 & 0xffffU | (iVar5 - iVar17) * 0x10000;
  return;
}

