/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80183920(short *param_1,short *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar2 = (int)*param_1;
  iVar6 = (int)*param_2;
  if (iVar2 == iVar6) {
    uVar1 = FUN_8008f708();
    if ((uVar1 & 1) == 0) {
      return 0xffffffff;
    }
    return 1;
  }
  if (iVar2 == 0) {
    iVar2 = 0x7fffffff;
LAB_801839c8:
    iVar8 = -0x7fffffff;
    iVar7 = -0x7fffffff;
  }
  else {
    uVar1 = (&DAT_801d4244)[iVar2 + -1];
    iVar2 = (int)*(short *)(&DAT_801d4d8e + (iVar2 + -1) * 2);
    if (0x13 < ((int)uVar1 >> 0x1a & 0x1fU)) goto LAB_801839c8;
    iVar7 = (uVar1 & 0x1ff) * 10;
    iVar8 = ((int)uVar1 >> 9 & 0x1ffU) * 10;
  }
  if (iVar6 == 0) {
    iVar6 = 0x7fffffff;
LAB_80183a48:
    iVar3 = -0x7fffffff;
    iVar5 = -0x7fffffff;
  }
  else {
    uVar1 = (&DAT_801d4244)[iVar6 + -1];
    iVar6 = (int)*(short *)(&DAT_801d4d8e + (iVar6 + -1) * 2);
    if (0x13 < ((int)uVar1 >> 0x1a & 0x1fU)) goto LAB_80183a48;
    iVar5 = (uVar1 & 0x1ff) * 10;
    iVar3 = ((int)uVar1 >> 9 & 0x1ffU) * 10;
  }
  if (iVar7 < iVar5) {
LAB_80183a98:
    uVar4 = 1;
  }
  else {
    if (iVar7 <= iVar5) {
      if (iVar8 < iVar3) goto LAB_80183a98;
      if (iVar8 <= iVar3) {
        if (iVar6 < iVar2) {
          return 1;
        }
        if (iVar6 <= iVar2) {
          return 0;
        }
      }
    }
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

