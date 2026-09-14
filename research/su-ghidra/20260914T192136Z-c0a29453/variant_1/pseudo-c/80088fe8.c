/* Analysis pseudo-C, not buildable source. */

void FUN_80088fe8(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  
  iVar16 = *param_1;
  uVar14 = (int)(short)param_1[1] >> 0x1f;
  uVar12 = iVar16 >> 0x1f;
  uVar10 = (int)(short)iVar16 >> 0x1f;
  uVar1 = *(int *)(&DAT_80096938 + (((int)(short)param_1[1] + uVar14 ^ uVar14) & 0xfff) * 4) *
          0x10000 + uVar14 ^ uVar14;
  uVar2 = *(int *)(&DAT_80096938 + (((iVar16 >> 0x10) + uVar12 ^ uVar12) & 0xfff) * 4) * 0x10000 +
          uVar12 ^ uVar12;
  uVar3 = *(int *)(&DAT_80096938 + (((int)(short)iVar16 + uVar10 ^ uVar10) & 0xfff) * 4) * 0x10000 +
          uVar10 ^ uVar10;
  iVar8 = (int)((*(int *)(&DAT_80096938 + (((iVar16 >> 0x10) + uVar12 ^ uVar12) & 0xfff) * 4) >>
                0x10) << 0x10 | uVar2 >> 0x10) >> 0x10;
  setCopReg(2,0x4000,iVar8);
  iVar7 = (int)(short)(uVar3 >> 0x10);
  setCopReg(2,0x4800,iVar7);
  iVar5 = (int)(short)(uVar1 >> 0x10);
  setCopReg(2,0x5000,iVar5);
  iVar4 = (int)((*(int *)(&DAT_80096938 + (((int)(short)param_1[1] + uVar14 ^ uVar14) & 0xfff) * 4)
                >> 0x10) << 0x10 | uVar1 >> 0x10) >> 0x10;
  setCopReg(2,0x5800,iVar4);
  iVar16 = (int)((*(int *)(&DAT_80096938 + (((int)(short)iVar16 + uVar10 ^ uVar10) & 0xfff) * 4) >>
                 0x10) << 0x10 | uVar3 >> 0x10) >> 0x10;
  copFunction(2,0x198003d);
  uVar9 = getCopReg(2,0x4800);
  iVar11 = getCopReg(2,0x5000);
  iVar13 = getCopReg(2,0x5800);
  iVar19 = (int)(short)(uVar2 >> 0x10);
  setCopReg(2,0x4000,iVar19);
  setCopReg(2,0x4800,iVar7);
  setCopReg(2,0x5000,iVar5);
  setCopReg(2,0x5800,iVar4);
  copFunction(2,0x198003d);
  *(short *)(param_2 + 4) = (short)(iVar16 * iVar8 >> 0xc);
  uVar15 = getCopReg(2,0x4800);
  iVar17 = getCopReg(2,0x5000);
  iVar18 = getCopReg(2,0x5800);
  setCopReg(2,0x4000,iVar4);
  setCopReg(2,0x4800,iVar16);
  setCopReg(2,0x5000,uVar15);
  setCopReg(2,0x5800,uVar9);
  copFunction(2,0x198003d);
  uVar1 = getCopReg(2,0x4800);
  iVar8 = getCopReg(2,0x5000);
  iVar6 = getCopReg(2,0x5800);
  setCopReg(2,0x4000,iVar5);
  setCopReg(2,0x4800,iVar16);
  setCopReg(2,0x5000,uVar15);
  setCopReg(2,0x5800,uVar9);
  copFunction(2,0x198003d);
  param_2[2] = uVar1 & 0xffff | iVar7 * -0x10000;
  iVar4 = getCopReg(2,0x4800);
  iVar5 = getCopReg(2,0x5000);
  iVar7 = getCopReg(2,0x5800);
  *param_2 = (iVar8 - iVar11) * 0x10000 | iVar13 + iVar5 & 0xffffU;
  param_2[1] = iVar4 << 0x10 | iVar16 * iVar19 >> 0xc & 0xffffU;
  param_2[3] = (iVar6 + iVar17) * 0x10000 | iVar7 - iVar18 & 0xffffU;
  return;
}

