/* Analysis pseudo-C, not buildable source. */

void FUN_8005b5cc(int param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  if (param_1 < 1) {
    piVar5 = &DAT_800f6c28;
    piVar6 = &DAT_800f6c34;
  }
  else {
    piVar5 = &DAT_800f6c34;
    piVar6 = &DAT_800f6c28;
  }
  if (10 < DAT_8009c7f8 + param_4) {
    DAT_8009c7f8 = DAT_8009c7f8 + (short)param_4;
  }
  if ((param_2 & 0xfff) != 0) {
    iVar4 = (int)DAT_8009c7fa + param_2 + 0x1000;
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = (int)DAT_8009c7fa + param_2 + 0x1fff;
    }
    DAT_8009c7fa = (short)iVar4 + (short)(iVar1 >> 0xc) * -0x1000;
  }
  if ((param_3 & 0xfff) != 0) {
    iVar4 = (int)DAT_8009c7fc + param_3 + 0x1000;
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = (int)DAT_8009c7fc + param_3 + 0x1fff;
    }
    DAT_8009c7fc = (short)iVar4 + (short)(iVar1 >> 0xc) * -0x1000;
  }
  if (((param_2 != 0) || (param_3 != 0)) || (param_4 != 0)) {
    iVar1 = FUN_800866f8((int)DAT_8009c7fc);
    iVar4 = FUN_80086628((int)DAT_8009c7fc);
    iVar1 = DAT_8009c7f8 * iVar1;
    iVar4 = DAT_8009c7f8 * iVar4;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xfff;
    }
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    iVar2 = FUN_800866f8((int)DAT_8009c7fa);
    iVar3 = FUN_80086628((int)DAT_8009c7fa);
    iVar3 = (iVar1 >> 0xc) * iVar3;
    iVar2 = (iVar1 >> 0xc) * iVar2;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xfff;
    }
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xfff;
    }
    *piVar6 = *piVar5 + (iVar2 >> 0xc) * param_1;
    piVar6[1] = piVar5[1] + (iVar4 >> 0xc) * param_1;
    piVar6[2] = piVar5[2] + (iVar3 >> 0xc) * param_1;
  }
  return;
}

