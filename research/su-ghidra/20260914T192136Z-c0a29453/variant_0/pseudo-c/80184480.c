/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80184480(short *param_1,short *param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = (int)*param_1;
  iVar6 = (int)*param_2;
  if (iVar2 == iVar6) {
    uVar3 = FUN_8008f708();
    uVar4 = 0xffffffff;
    if ((uVar3 & 1) != 0) {
      uVar4 = 1;
    }
  }
  else {
    if (iVar2 == 0) {
      iVar2 = 0x7fffffff;
      uVar3 = 0x80000001;
    }
    else {
      iVar2 = (int)*(short *)(&DAT_801d4d8e + (iVar2 + -1) * 2);
      uVar3 = (uint)(ushort)param_1[1];
    }
    if (iVar6 == 0) {
      iVar6 = 0x7fffffff;
      uVar5 = 0x80000001;
      bVar1 = (int)uVar3 < -0x7fffffff;
    }
    else {
      iVar6 = (int)*(short *)(&DAT_801d4d8e + (iVar6 + -1) * 2);
      uVar5 = (uint)(ushort)param_2[1];
      bVar1 = (int)uVar3 < (int)uVar5;
    }
    uVar4 = 1;
    if ((((!bVar1) && (uVar4 = 0xffffffff, (int)uVar3 <= (int)uVar5)) && (uVar4 = 1, iVar2 <= iVar6)
        ) && (uVar4 = 0, iVar2 < iVar6)) {
      uVar4 = 0xffffffff;
    }
  }
  return uVar4;
}

