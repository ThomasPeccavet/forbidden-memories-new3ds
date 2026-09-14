/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80183c40(short *param_1,short *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = (int)*param_1;
  iVar5 = (int)*param_2;
  if (iVar2 == iVar5) {
    uVar1 = FUN_8008f708();
    uVar3 = 0xffffffff;
    if ((uVar1 & 1) != 0) {
      uVar3 = 1;
    }
  }
  else {
    if (iVar2 == 0) {
      uVar1 = 0x7fffffff;
      iVar6 = 0x7fffffff;
    }
    else {
      iVar6 = (int)*(short *)(&DAT_801d4d8e + (iVar2 + -1) * 2);
      uVar1 = (int)(&DAT_801d4244)[iVar2 + -1] >> 0x1a & 0x1f;
    }
    if (iVar5 == 0) {
      uVar4 = 0x7fffffff;
      iVar2 = 0x7fffffff;
    }
    else {
      iVar2 = (int)*(short *)(&DAT_801d4d8e + (iVar5 + -1) * 2);
      uVar4 = (int)(&DAT_801d4244)[iVar5 + -1] >> 0x1a & 0x1f;
    }
    if (uVar4 < uVar1) {
      uVar3 = 1;
    }
    else if ((uVar1 < uVar4) || ((uVar3 = 1, iVar6 <= iVar2 && (uVar3 = 0, iVar6 < iVar2)))) {
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

