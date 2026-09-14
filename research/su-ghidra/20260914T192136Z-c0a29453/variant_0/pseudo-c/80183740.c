/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80183740(short *param_1,short *param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  
  iVar4 = (int)*param_1;
  iVar9 = (int)*param_2;
  if (iVar4 == iVar9) {
    uVar2 = FUN_8008f708();
    if ((uVar2 & 1) == 0) {
      return 0xffffffff;
    }
    return 1;
  }
  if (iVar4 == 0) {
    iVar4 = 0x7fffffff;
LAB_8018380c:
    uVar8 = 0x80000001;
    uVar2 = 0x80000001;
  }
  else {
    uVar2 = (&DAT_801d4244)[iVar4 + -1];
    iVar4 = (int)*(short *)(&DAT_801d4d8e + (iVar4 + -1) * 2);
    if (0x13 < ((int)uVar2 >> 0x1a & 0x1fU)) goto LAB_8018380c;
    uVar8 = ((int)uVar2 >> 9 & 0x1ffU) * 10;
    uVar5 = (uVar2 & 0x1ff) * 10;
    uVar2 = uVar8;
    if (uVar8 < uVar5) {
      uVar2 = uVar5;
    }
    if (uVar5 < uVar8) {
      uVar8 = uVar5;
    }
  }
  if (iVar9 == 0) {
    iVar9 = 0x7fffffff;
LAB_801838b8:
    uVar3 = 0x80000001;
    uVar5 = 0x80000001;
    bVar1 = (int)uVar2 < -0x7fffffff;
  }
  else {
    uVar5 = (&DAT_801d4244)[iVar9 + -1];
    iVar9 = (int)*(short *)(&DAT_801d4d8e + (iVar9 + -1) * 2);
    if (0x13 < ((int)uVar5 >> 0x1a & 0x1fU)) goto LAB_801838b8;
    uVar3 = ((int)uVar5 >> 9 & 0x1ffU) * 10;
    uVar6 = (uVar5 & 0x1ff) * 10;
    uVar5 = uVar3;
    if (uVar3 < uVar6) {
      uVar5 = uVar6;
    }
    bVar1 = (int)uVar2 < (int)uVar5;
    if (uVar6 < uVar3) {
      uVar3 = uVar6;
    }
  }
  if (bVar1) {
LAB_80183908:
    uVar7 = 1;
  }
  else {
    if ((int)uVar2 <= (int)uVar5) {
      if ((int)uVar8 < (int)uVar3) goto LAB_80183908;
      if ((int)uVar8 <= (int)uVar3) {
        if (iVar9 < iVar4) {
          return 1;
        }
        if (iVar9 <= iVar4) {
          return 0;
        }
      }
    }
    uVar7 = 0xffffffff;
  }
  return uVar7;
}

