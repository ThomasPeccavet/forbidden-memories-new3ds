/* Analysis pseudo-C, not buildable source. */

void FUN_80054b9c(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  iVar3 = (int)DAT_800f406a;
  iVar8 = (int)DAT_800f4072;
  iVar4 = (int)DAT_800f407a;
  iVar9 = (int)DAT_800f4082;
  iVar5 = FUN_8004fb18();
  if ((iVar5 != 0) && (DAT_800f4059 != 0)) {
    if (DAT_800f4062 != 0xffff) {
      iVar5 = FUN_8005bf24();
      if ((((uint)DAT_800f4060 < DAT_800f4062 / 5) ||
          (((uint)DAT_800f4062 << 2) / 5 < (uint)DAT_800f4060)) && (iVar5 = iVar5 / 2, iVar5 < 2)) {
        iVar5 = 2;
      }
      uVar6 = (uint)DAT_800f4060;
      DAT_800f4060 = DAT_800f4062;
      if ((int)(uVar6 + iVar5) < (int)(uint)DAT_800f4062) {
        DAT_800f4060 = (ushort)(uVar6 + iVar5);
      }
    }
    sVar1 = DAT_800f4066;
    if (-1 < iVar3) {
      iVar5 = (int)(short)(&DAT_800f4f48)[iVar3 * 0x710] - (int)DAT_800f4064;
      iVar3 = (int)(short)(&DAT_800f4f4a)[iVar3 * 0x710] - (int)DAT_800f4066;
      if (iVar5 < 1) {
        sVar1 = DAT_800f4064 + (short)iVar5;
        if (iVar5 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054d40;
        }
      }
      else {
        sVar1 = DAT_800f4064 + (short)iVar5;
        if (0x1e < iVar5) {
          sVar1 = 0x1e;
LAB_80054d40:
          sVar1 = DAT_800f4064 + sVar1;
        }
      }
      DAT_800f4064 = sVar1;
      if (iVar3 < 1) {
        sVar1 = DAT_800f4066 + (short)iVar3;
        if (iVar3 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054d7c;
        }
      }
      else {
        sVar1 = DAT_800f4066 + (short)iVar3;
        if (0x1e < iVar3) {
          sVar1 = 0x1e;
LAB_80054d7c:
          sVar1 = DAT_800f4066 + sVar1;
        }
      }
    }
    DAT_800f4066 = sVar1;
    sVar1 = DAT_800f4070;
    if (-1 < iVar8) {
      iVar11 = (int)(short)(&DAT_800f4f48)[iVar8 * 0x710] - (int)DAT_800f406c;
      iVar3 = (int)(short)(&DAT_800f4f4c)[iVar8 * 0x710] - (int)DAT_800f4070;
      iVar5 = (int)(short)(&DAT_800f4f4a)[iVar8 * 0x710] - (int)DAT_800f406e;
      if (iVar11 < 1) {
        sVar1 = DAT_800f406c + (short)iVar11;
        if (iVar11 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054e0c;
        }
      }
      else {
        sVar1 = DAT_800f406c + (short)iVar11;
        if (0x1e < iVar11) {
          sVar1 = 0x1e;
LAB_80054e0c:
          sVar1 = DAT_800f406c + sVar1;
        }
      }
      if (iVar5 < 1) {
        sVar2 = DAT_800f406e + (short)iVar5;
        if (iVar5 < -0x1e) {
          sVar2 = -0x1e;
          goto LAB_80054e48;
        }
      }
      else {
        sVar2 = DAT_800f406e + (short)iVar5;
        if (0x1e < iVar5) {
          sVar2 = 0x1e;
LAB_80054e48:
          sVar2 = DAT_800f406e + sVar2;
        }
      }
      DAT_800f406c = sVar1;
      DAT_800f406e = sVar2;
      if (iVar3 < 1) {
        sVar1 = DAT_800f4070 + (short)iVar3;
        if (iVar3 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054e84;
        }
      }
      else {
        sVar1 = DAT_800f4070 + (short)iVar3;
        if (0x1e < iVar3) {
          sVar1 = 0x1e;
LAB_80054e84:
          sVar1 = DAT_800f4070 + sVar1;
        }
      }
    }
    DAT_800f4070 = sVar1;
    sVar1 = DAT_800f4076;
    if (-1 < iVar4) {
      iVar5 = (int)(short)(&DAT_800f4f48)[iVar4 * 0x710] - (int)DAT_800f4074;
      iVar3 = (int)(short)(&DAT_800f4f4a)[iVar4 * 0x710] - (int)DAT_800f4076;
      if (iVar5 < 1) {
        sVar1 = DAT_800f4074 + (short)iVar5;
        if (iVar5 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054f00;
        }
      }
      else {
        sVar1 = DAT_800f4074 + (short)iVar5;
        if (0x1e < iVar5) {
          sVar1 = 0x1e;
LAB_80054f00:
          sVar1 = DAT_800f4074 + sVar1;
        }
      }
      DAT_800f4074 = sVar1;
      if (iVar3 < 1) {
        sVar1 = DAT_800f4076 + (short)iVar3;
        if (iVar3 < -0x1e) {
          sVar1 = -0x1e;
          goto LAB_80054f3c;
        }
      }
      else {
        sVar1 = DAT_800f4076 + (short)iVar3;
        if (0x1e < iVar3) {
          sVar1 = 0x1e;
LAB_80054f3c:
          sVar1 = DAT_800f4076 + sVar1;
        }
      }
    }
    DAT_800f4076 = sVar1;
    sVar1 = DAT_800f4080;
    if (iVar9 < 0) goto LAB_8005504c;
    iVar5 = (int)(short)(&DAT_800f4f48)[iVar9 * 0x710] - (int)DAT_800f407c;
    iVar3 = (int)(short)(&DAT_800f4f4c)[iVar9 * 0x710] - (int)DAT_800f4080;
    iVar4 = (int)(short)(&DAT_800f4f4a)[iVar9 * 0x710] - (int)DAT_800f407e;
    if (iVar5 < 1) {
      sVar1 = DAT_800f407c + (short)iVar5;
      if (iVar5 < -0x1e) {
        sVar1 = -0x1e;
        goto LAB_80054fcc;
      }
    }
    else {
      sVar1 = DAT_800f407c + (short)iVar5;
      if (0x1e < iVar5) {
        sVar1 = 0x1e;
LAB_80054fcc:
        sVar1 = DAT_800f407c + sVar1;
      }
    }
    if (iVar4 < 1) {
      sVar2 = DAT_800f407e + (short)iVar4;
      if (iVar4 < -0x1e) {
        sVar2 = -0x1e;
        goto LAB_80055008;
      }
    }
    else {
      sVar2 = DAT_800f407e + (short)iVar4;
      if (0x1e < iVar4) {
        sVar2 = 0x1e;
LAB_80055008:
        sVar2 = DAT_800f407e + sVar2;
      }
    }
    DAT_800f407c = sVar1;
    DAT_800f407e = sVar2;
    if (iVar3 < 1) {
      sVar1 = DAT_800f4080 + (short)iVar3;
      if (-0x1f < iVar3) goto LAB_8005504c;
      sVar1 = -0x1e;
    }
    else {
      sVar1 = DAT_800f4080 + (short)iVar3;
      if (iVar3 < 0x1f) goto LAB_8005504c;
      sVar1 = 0x1e;
    }
    sVar1 = DAT_800f4080 + sVar1;
LAB_8005504c:
    DAT_800f4080 = sVar1;
    if ((DAT_800f4059 & 1) == 0) {
      if (DAT_800f4058 != '\0') {
        iVar3 = FUN_8005bf24();
        FUN_8005b5cc(1,(uint)DAT_800f405c * iVar3 * (int)DAT_8009c329,0,0,0);
      }
    }
    else {
      iVar3 = ((int)DAT_800f406c - (int)DAT_800f4064) * (uint)DAT_800f4060;
      uVar6 = (uint)DAT_800f4062;
      if (uVar6 == 0) {
        trap(0x1c00);
      }
      if ((uVar6 == 0xffffffff) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
      iVar4 = ((int)DAT_800f406e - (int)DAT_800f4066) * (uint)DAT_800f4060;
      uVar10 = (uint)DAT_800f4062;
      if (uVar10 == 0) {
        trap(0x1c00);
      }
      if ((uVar10 == 0xffffffff) && (iVar4 == -0x80000000)) {
        trap(0x1800);
      }
      iVar5 = ((int)DAT_800f4070 - (int)DAT_800f4068) * (uint)DAT_800f4060;
      uVar7 = (uint)DAT_800f4062;
      if (uVar7 == 0) {
        trap(0x1c00);
      }
      if ((uVar7 == 0xffffffff) && (iVar5 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_800f6c28 = iVar3 / (int)uVar6 + (int)DAT_800f4064;
      DAT_800f6c2c = iVar4 / (int)uVar10 + (int)DAT_800f4066;
      DAT_800f6c30 = iVar5 / (int)uVar7 + (int)DAT_800f4068;
      if (-0x65 < DAT_800f6c2c) {
        DAT_800f6c2c = -100;
      }
    }
    if ((DAT_800f4059 & 2) != 0) {
      iVar3 = ((int)DAT_800f407c - (int)DAT_800f4074) * (uint)DAT_800f4060;
      uVar6 = (uint)DAT_800f4062;
      if (uVar6 == 0) {
        trap(0x1c00);
      }
      if ((uVar6 == 0xffffffff) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
      iVar4 = ((int)DAT_800f407e - (int)DAT_800f4076) * (uint)DAT_800f4060;
      uVar10 = (uint)DAT_800f4062;
      if (uVar10 == 0) {
        trap(0x1c00);
      }
      if ((uVar10 == 0xffffffff) && (iVar4 == -0x80000000)) {
        trap(0x1800);
      }
      iVar5 = ((int)DAT_800f4080 - (int)DAT_800f4078) * (uint)DAT_800f4060;
      uVar7 = (uint)DAT_800f4062;
      if (uVar7 == 0) {
        trap(0x1c00);
      }
      if ((uVar7 == 0xffffffff) && (iVar5 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_800f6c34 = iVar3 / (int)uVar6 + (int)DAT_800f4074;
      DAT_800f6c38 = iVar4 / (int)uVar10 + (int)DAT_800f4076;
      DAT_800f6c3c = iVar5 / (int)uVar7 + (int)DAT_800f4078;
      if (-0x65 < DAT_800f6c38) {
        DAT_800f6c38 = -100;
      }
    }
    FUN_8005b0bc(0);
    FUN_800557e8(1);
    if (DAT_800f4060 < DAT_800f4062) {
      return;
    }
    FUN_8005cfc4(1);
    return;
  }
  if (DAT_800f4058 == '\0') {
    return;
  }
  iVar3 = FUN_8004fb24();
  if (-1 < iVar8) {
    iVar11 = (short)(&DAT_800f4f48)[iVar8 * 0x710] - DAT_800f6c28;
    iVar4 = (short)(&DAT_800f4f4c)[iVar8 * 0x710] - DAT_800f6c30;
    iVar5 = (short)(&DAT_800f4f4a)[iVar8 * 0x710] - DAT_800f6c2c;
    if (iVar11 < 1) {
      iVar8 = DAT_800f6c28 + iVar11;
      if (iVar11 < -0x1e) {
        iVar8 = -0x1e;
        goto LAB_800553e4;
      }
    }
    else {
      iVar8 = DAT_800f6c28 + iVar11;
      if (0x1e < iVar11) {
        iVar8 = 0x1e;
LAB_800553e4:
        iVar8 = DAT_800f6c28 + iVar8;
      }
    }
    if (iVar5 < 1) {
      iVar11 = DAT_800f6c2c + iVar5;
      if (iVar5 < -0x1e) {
        iVar11 = -0x1e;
        goto LAB_80055420;
      }
    }
    else {
      iVar11 = DAT_800f6c2c + iVar5;
      if (0x1e < iVar5) {
        iVar11 = 0x1e;
LAB_80055420:
        iVar11 = DAT_800f6c2c + iVar11;
      }
    }
    if (iVar4 < 1) {
      iVar5 = DAT_800f6c30 + iVar4;
      if (iVar4 < -0x1e) {
        iVar5 = -0x1e;
        goto LAB_8005545c;
      }
    }
    else {
      iVar5 = DAT_800f6c30 + iVar4;
      if (0x1e < iVar4) {
        iVar5 = 0x1e;
LAB_8005545c:
        iVar5 = DAT_800f6c30 + iVar5;
      }
    }
    DAT_800f6c28 = iVar8;
    DAT_800f6c2c = iVar11;
    DAT_800f6c30 = iVar5;
    if (-0x65 < iVar11) {
      DAT_800f6c2c = -100;
    }
  }
  if (iVar9 < 0) goto LAB_800555ac;
  iVar8 = (short)(&DAT_800f4f48)[iVar9 * 0x710] - DAT_800f6c34;
  iVar4 = (short)(&DAT_800f4f4c)[iVar9 * 0x710] - DAT_800f6c3c;
  iVar5 = (short)(&DAT_800f4f4a)[iVar9 * 0x710] - DAT_800f6c38;
  if (iVar8 < 1) {
    iVar9 = DAT_800f6c34 + iVar8;
    if (iVar8 < -0x1e) {
      iVar9 = -0x1e;
      goto LAB_8005550c;
    }
  }
  else {
    iVar9 = DAT_800f6c34 + iVar8;
    if (0x1e < iVar8) {
      iVar9 = 0x1e;
LAB_8005550c:
      iVar9 = DAT_800f6c34 + iVar9;
    }
  }
  if (iVar5 < 1) {
    iVar8 = DAT_800f6c38 + iVar5;
    if (iVar5 < -0x1e) {
      iVar8 = -0x1e;
      goto LAB_80055548;
    }
  }
  else {
    iVar8 = DAT_800f6c38 + iVar5;
    if (0x1e < iVar5) {
      iVar8 = 0x1e;
LAB_80055548:
      iVar8 = DAT_800f6c38 + iVar8;
    }
  }
  if (iVar4 < 1) {
    iVar5 = DAT_800f6c3c + iVar4;
    if (iVar4 < -0x1e) {
      iVar5 = -0x1e;
      goto LAB_80055584;
    }
  }
  else {
    iVar5 = DAT_800f6c3c + iVar4;
    if (0x1e < iVar4) {
      iVar5 = 0x1e;
LAB_80055584:
      iVar5 = DAT_800f6c3c + iVar5;
    }
  }
  DAT_800f6c34 = iVar9;
  DAT_800f6c38 = iVar8;
  DAT_800f6c3c = iVar5;
  if (-0x65 < iVar8) {
    DAT_800f6c38 = -100;
  }
LAB_800555ac:
  if ((iVar3 == 0) || ((*(short *)(iVar3 + 6) != 4 && (*(short *)(iVar3 + 0xe) != 4)))) {
    iVar3 = FUN_8005bf24();
    FUN_8005b5cc(1,(uint)DAT_800f405c * iVar3 * (int)DAT_8009c329,0,0,0);
    FUN_800557e8(1);
  }
  if (DAT_800f405a != 0) {
    iVar3 = FUN_8005bf24();
    if ((int)((uint)DAT_800f405a - iVar3) < 1) {
      DAT_800f405a = 0;
    }
    else {
      sVar1 = FUN_8005bf24();
      DAT_800f405a = DAT_800f405a - sVar1;
    }
  }
  return;
}

