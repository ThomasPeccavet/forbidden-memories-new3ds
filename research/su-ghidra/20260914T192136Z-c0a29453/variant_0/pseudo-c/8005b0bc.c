/* Analysis pseudo-C, not buildable source. */

void FUN_8005b0bc(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = &DAT_800f6c28;
  if ((param_1 != (int *)0x0) && (piVar1 = param_1, param_1 != &DAT_800f6c28)) {
    DAT_800f6c28 = *param_1;
    DAT_800f6c2c = param_1[1];
    DAT_800f6c30 = param_1[2];
    DAT_800f6c34 = param_1[3];
    DAT_800f6c38 = param_1[4];
    DAT_800f6c3c = param_1[5];
    DAT_800f6c40 = param_1[6];
    DAT_800f6c44 = param_1[7];
  }
  DAT_8009c7f8 = FUN_80086dd8((*piVar1 - piVar1[3]) * (*piVar1 - piVar1[3]) +
                              (piVar1[2] - piVar1[5]) * (piVar1[2] - piVar1[5]));
  DAT_8009c7fa = FUN_80089928(piVar1[2] - piVar1[5],*piVar1 - piVar1[3]);
  DAT_8009c7fc = FUN_80089928(piVar1[1] - piVar1[4],(int)DAT_8009c7f8);
  DAT_8009c7f8 = FUN_80086dd8((*piVar1 - piVar1[3]) * (*piVar1 - piVar1[3]) +
                              (piVar1[1] - piVar1[4]) * (piVar1[1] - piVar1[4]) +
                              (piVar1[2] - piVar1[5]) * (piVar1[2] - piVar1[5]));
  iVar3 = DAT_8009c7fa + 0x1000;
  iVar2 = iVar3;
  if (iVar3 < 0) {
    iVar2 = DAT_8009c7fa + 0x1fff;
  }
  DAT_8009c7fa = (short)iVar3 + (short)(iVar2 >> 0xc) * -0x1000;
  iVar3 = DAT_8009c7fc + 0x1000;
  iVar2 = iVar3;
  if (iVar3 < 0) {
    iVar2 = DAT_8009c7fc + 0x1fff;
  }
  DAT_8009c7fc = (short)iVar3 + (short)(iVar2 >> 0xc) * -0x1000;
  return;
}

