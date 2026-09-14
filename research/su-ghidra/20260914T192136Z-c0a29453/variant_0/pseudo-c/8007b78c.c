/* Analysis pseudo-C, not buildable source. */

int FUN_8007b78c(byte param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  
  if ((*(int *)(&DAT_80094c18 + (uint)param_1 * 4) != 0) && (param_2 != 0)) {
    iVar1 = 0;
    if (DAT_800f7270 < 8) {
      iVar1 = DAT_80094c98 + 1;
      if (iVar1 == 0) {
        iVar1 = DAT_80094c98 + 2;
      }
      DAT_80094c98 = iVar1;
      piVar2 = (int *)FUN_8007afa4();
      *piVar2 = iVar1;
      *(undefined1 *)(piVar2 + 1) = 2;
      if (param_2 == 0) {
        piVar2[3] = 0;
      }
      else {
        FUN_8007d2bc((int)piVar2 + 5,param_2);
        piVar2[3] = (int)piVar2 + 5;
      }
      piVar2[4] = 0;
      piVar2[5] = 0;
      uVar3 = FUN_80074a54(0);
      DAT_800f7270 = DAT_800f7270 + 1;
      FUN_80074a54(uVar3);
      iVar4 = FUN_8007c484(0);
      if ((iVar4 == 1) && ((&DAT_800f71a8)[DAT_800f726c * 6] == iVar1)) {
        FUN_8007b21c();
      }
    }
    if (iVar1 == 0) {
      return 0;
    }
  }
  iVar1 = 0;
  if (DAT_800f7270 < 8) {
    iVar1 = DAT_80094c98 + 1;
    if (iVar1 == 0) {
      iVar1 = DAT_80094c98 + 2;
    }
    DAT_80094c98 = iVar1;
    piVar2 = (int *)FUN_8007afa4();
    *piVar2 = iVar1;
    *(byte *)(piVar2 + 1) = param_1;
    if (param_2 == 0) {
      piVar2[3] = 0;
    }
    else {
      FUN_8007d2bc((int)piVar2 + 5,param_2);
      piVar2[3] = (int)piVar2 + 5;
    }
    piVar2[4] = param_3;
    piVar2[5] = param_4;
    uVar3 = FUN_80074a54(0);
    DAT_800f7270 = DAT_800f7270 + 1;
    FUN_80074a54(uVar3);
    iVar4 = FUN_8007c484(0);
    if ((iVar4 == 1) && ((&DAT_800f71a8)[DAT_800f726c * 6] == iVar1)) {
      FUN_8007b21c();
    }
  }
  return iVar1;
}

