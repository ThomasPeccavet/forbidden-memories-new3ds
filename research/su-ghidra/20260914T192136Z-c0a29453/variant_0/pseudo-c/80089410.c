/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80089410(undefined4 param_1,int *param_2,int param_3,undefined4 *param_4)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  undefined4 uVar10;
  undefined4 in_zero;
  uint uVar11;
  undefined4 *puVar12;
  short *psVar13;
  short *psVar14;
  short *psVar15;
  short *psVar16;
  uint uVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined4 unaff_retaddr;
  
  psVar13 = (short *)param_4[0x1e];
  psVar14 = (short *)param_4[0x1f];
  psVar15 = (short *)param_4[0x20];
  psVar16 = (short *)param_4[0x21];
  iVar18 = getCopControlWord(2,0xd000);
  uVar17 = iVar18 >> 1;
  if ((((*(uint *)(psVar13 + 10) < uVar17) && (*(uint *)(psVar14 + 10) < uVar17)) &&
      (*(uint *)(psVar15 + 10) < uVar17)) && (*(uint *)(psVar16 + 10) < uVar17)) {
    return param_1;
  }
  iVar19 = getCopControlWord(2,0xc000);
  uVar17 = (uint)param_2[1] >> 1;
  iVar18 = (iVar19 >> 0x10) + uVar17;
  if (((iVar18 < psVar13[8]) && (iVar18 < psVar14[8])) &&
     ((iVar18 < psVar15[8] && (iVar18 < psVar16[8])))) {
    return param_1;
  }
  iVar18 = (iVar19 >> 0x10) - uVar17;
  if (((psVar13[8] < iVar18) && (psVar14[8] < iVar18)) &&
     ((psVar15[8] < iVar18 && (psVar16[8] < iVar18)))) {
    return param_1;
  }
  iVar19 = getCopControlWord(2,0xc800);
  iVar18 = (iVar19 >> 0x10) + ((uint)param_2[2] >> 1);
  if ((((iVar18 < psVar13[9]) && (iVar18 < psVar14[9])) && (iVar18 < psVar15[9])) &&
     (iVar18 < psVar16[9])) {
    return param_1;
  }
  iVar18 = (iVar19 >> 0x10) - ((uint)param_2[2] >> 1);
  uVar11 = (uint)(psVar14[9] < iVar18);
  if (((psVar13[9] < iVar18) && (bVar1 = uVar11 != 0, uVar11 = (uint)(psVar15[9] < iVar18), bVar1))
     && ((bVar1 = uVar11 != 0, uVar11 = (uint)(psVar16[9] < iVar18), bVar1 && (uVar11 != 0)))) {
    return param_1;
  }
  sVar6 = *psVar13;
  sVar7 = *psVar14;
  sVar8 = *psVar15;
  sVar9 = *psVar16;
  *(short *)(param_4 + 0xc) = (short)((int)sVar9 + (int)sVar7 >> 1);
  *(short *)(param_4 + 6) = (short)((int)sVar6 + (int)sVar8 >> 1);
  iVar18 = (int)sVar6 + (int)sVar7;
  iVar19 = (int)sVar9 + (int)sVar8;
  *(short *)param_4 = (short)(iVar18 >> 1);
  *(short *)(param_4 + 0x12) = (short)(iVar19 >> 1);
  *(short *)(param_4 + 0x18) = (short)(iVar18 + iVar19 >> 2);
  sVar6 = psVar13[1];
  sVar7 = psVar14[1];
  sVar8 = psVar15[1];
  sVar9 = psVar16[1];
  *(short *)((int)param_4 + 0x32) = (short)((int)sVar9 + (int)sVar7 >> 1);
  *(short *)((int)param_4 + 0x1a) = (short)((int)sVar6 + (int)sVar8 >> 1);
  iVar18 = (int)sVar6 + (int)sVar7;
  iVar19 = (int)sVar9 + (int)sVar8;
  *(short *)((int)param_4 + 2) = (short)(iVar18 >> 1);
  *(short *)((int)param_4 + 0x4a) = (short)(iVar19 >> 1);
  *(short *)((int)param_4 + 0x62) = (short)(iVar18 + iVar19 >> 2);
  sVar6 = psVar13[2];
  sVar7 = psVar14[2];
  sVar8 = psVar15[2];
  sVar9 = psVar16[2];
  *(short *)(param_4 + 0xd) = (short)((int)sVar9 + (int)sVar7 >> 1);
  *(short *)(param_4 + 7) = (short)((int)sVar6 + (int)sVar8 >> 1);
  iVar19 = (int)sVar6 + (int)sVar7;
  iVar20 = (int)sVar9 + (int)sVar8;
  iVar18 = iVar19 + iVar20 >> 2;
  *(short *)(param_4 + 1) = (short)(iVar19 >> 1);
  *(short *)(param_4 + 0x13) = (short)(iVar20 >> 1);
  *(short *)(param_4 + 0x19) = (short)iVar18;
  setCopReg(2,in_zero,*param_4);
  setCopReg(2,uVar11,param_4[1]);
  setCopReg(2,uVar17,param_4[6]);
  setCopReg(2,iVar18,param_4[7]);
  setCopReg(2,param_1,param_4[0x18]);
  setCopReg(2,param_2,param_4[0x19]);
  bVar2 = *(byte *)(psVar13 + 4);
  copFunction(2,0x280030);
  bVar3 = *(byte *)(psVar14 + 4);
  bVar4 = *(byte *)(psVar15 + 4);
  bVar5 = *(byte *)(psVar16 + 4);
  *(char *)(param_4 + 0xe) = (char)((int)((uint)bVar5 + (uint)bVar3) >> 1);
  *(char *)(param_4 + 8) = (char)((int)((uint)bVar2 + (uint)bVar4) >> 1);
  iVar19 = (uint)bVar2 + (uint)bVar3;
  iVar20 = (uint)bVar5 + (uint)bVar4;
  iVar18 = iVar19 + iVar20 >> 2;
  *(char *)(param_4 + 2) = (char)(iVar19 >> 1);
  *(char *)(param_4 + 0x14) = (char)(iVar20 >> 1);
  *(char *)(param_4 + 0x1a) = (char)iVar18;
  uVar10 = getCopReg(2,0xc);
  param_4[4] = uVar10;
  uVar10 = getCopReg(2,0xd);
  param_4[10] = uVar10;
  uVar10 = getCopReg(2,0xe);
  param_4[0x1c] = uVar10;
  uVar10 = getCopReg(2,0x11);
  param_4[5] = uVar10;
  uVar10 = getCopReg(2,0x12);
  param_4[0xb] = uVar10;
  uVar10 = getCopReg(2,0x13);
  param_4[0x1d] = uVar10;
  setCopReg(2,in_zero,param_4[0xc]);
  setCopReg(2,uVar11,param_4[0xd]);
  setCopReg(2,uVar17,param_4[0x12]);
  setCopReg(2,iVar18,param_4[0x13]);
  bVar2 = *(byte *)((int)psVar13 + 9);
  copFunction(2,0x280030);
  bVar3 = *(byte *)((int)psVar14 + 9);
  bVar4 = *(byte *)((int)psVar15 + 9);
  bVar5 = *(byte *)((int)psVar16 + 9);
  *(char *)((int)param_4 + 0x39) = (char)((int)((uint)bVar5 + (uint)bVar3) >> 1);
  *(char *)((int)param_4 + 0x21) = (char)((int)((uint)bVar2 + (uint)bVar4) >> 1);
  iVar18 = (uint)bVar2 + (uint)bVar3;
  iVar19 = (uint)bVar5 + (uint)bVar4;
  *(char *)((int)param_4 + 9) = (char)(iVar18 >> 1);
  *(char *)((int)param_4 + 0x51) = (char)(iVar19 >> 1);
  *(char *)((int)param_4 + 0x69) = (char)(iVar18 + iVar19 >> 2);
  if (*param_2 == param_3 + 1) {
    uVar10 = getCopReg(2,0xc);
    param_4[0x10] = uVar10;
    uVar10 = getCopReg(2,0xd);
    param_4[0x16] = uVar10;
    FUN_80089898();
    FUN_80089898();
    FUN_80089898();
    FUN_80089898();
  }
  else {
    puVar12 = param_4 + 0x23;
    param_4[0x45] = unaff_retaddr;
    param_4[0x41] = param_4[0x1e];
    param_4[0x42] = param_4;
    param_4[0x43] = param_4 + 6;
    param_4[0x44] = param_4 + 0x18;
    uVar10 = getCopReg(2,0xc);
    param_4[0x10] = uVar10;
    uVar10 = getCopReg(2,0xd);
    param_4[0x16] = uVar10;
    uVar10 = getCopReg(2,0x11);
    param_4[0x11] = uVar10;
    uVar10 = getCopReg(2,0x12);
    param_4[0x17] = uVar10;
    FUN_80089410();
    puVar12[0x1e] = puVar12[-4];
    puVar12[0x1f] = puVar12 + -0x17;
    puVar12[0x20] = puVar12 + -0x23;
    puVar12[0x21] = puVar12 + -0xb;
    FUN_80089410();
    puVar12[0x1e] = puVar12[-3];
    puVar12[0x1f] = puVar12 + -0x1d;
    puVar12[0x20] = puVar12 + -0x11;
    puVar12[0x21] = puVar12 + -0xb;
    FUN_80089410();
    puVar12[0x1e] = puVar12[-2];
    puVar12[0x1f] = puVar12 + -0x11;
    puVar12[0x20] = puVar12 + -0x17;
    puVar12[0x21] = puVar12 + -0xb;
    FUN_80089410();
  }
  return param_1;
}

