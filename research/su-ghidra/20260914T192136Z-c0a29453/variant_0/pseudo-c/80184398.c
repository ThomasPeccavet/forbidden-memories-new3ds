/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80184398(short *param_1,short *param_2)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = (int)*param_1;
  iVar5 = (int)*param_2;
  if (iVar7 == iVar5) {
    uVar2 = FUN_8008f708();
    uVar3 = 0xffffffff;
    if ((uVar2 & 1) != 0) {
      uVar3 = 1;
    }
  }
  else {
    if (iVar7 == 0) {
      iVar6 = 0x7fffffff;
      iVar7 = 0x7fffffff;
    }
    else {
      iVar6 = (int)*(short *)(&DAT_801d4d8e + (iVar7 + -1) * 2);
    }
    if (iVar5 == 0) {
      iVar4 = 0x7fffffff;
      iVar5 = 0x7fffffff;
      bVar1 = 0x7fffffff < iVar6;
    }
    else {
      iVar4 = (int)*(short *)(&DAT_801d4d8e + (iVar5 + -1) * 2);
      bVar1 = iVar4 < iVar6;
    }
    if (bVar1) {
      uVar3 = 1;
    }
    else if ((iVar6 < iVar4) || ((uVar3 = 1, iVar7 <= iVar5 && (uVar3 = 0, iVar7 < iVar5)))) {
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

