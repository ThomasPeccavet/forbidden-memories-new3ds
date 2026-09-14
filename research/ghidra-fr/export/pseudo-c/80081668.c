/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80081668(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  
  FUN_80082168();
  if (*(short *)(param_1 + 1) < 0) {
    sVar5 = 0;
  }
  else {
    sVar5 = *(short *)(param_1 + 1);
    if (DAT_80095a9c < *(short *)(param_1 + 1)) {
      sVar5 = DAT_80095a9c;
    }
  }
  sVar6 = *(short *)((int)param_1 + 6);
  *(short *)(param_1 + 1) = sVar5;
  if (*(short *)((int)param_1 + 6) < 0) {
    sVar5 = 0;
  }
  else {
    sVar5 = DAT_80095a9e;
    if (*(short *)((int)param_1 + 6) <= DAT_80095a9e) goto LAB_80081708;
  }
  sVar6 = sVar5;
LAB_80081708:
  *(short *)((int)param_1 + 6) = sVar6;
  iVar4 = (int)*(short *)(param_1 + 1) * (int)sVar6 + 1;
  iVar7 = iVar4 - (iVar4 >> 0x1f) >> 5;
  if (iVar4 / 2 < 1) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar4 = iVar4 / 2 + iVar7 * -0x10;
    uVar2 = *DAT_80095ba0;
    while ((uVar2 & 0x4000000) == 0) {
      iVar3 = FUN_8008219c();
      if (iVar3 != 0) {
        return 0xffffffff;
      }
      uVar2 = *DAT_80095ba0;
    }
    *DAT_80095ba0 = 0x4000000;
    *DAT_80095b9c = 0x1000000;
    *DAT_80095b9c = 0xc0000000;
    *DAT_80095b9c = *param_1;
    *DAT_80095b9c = param_1[1];
    uVar2 = *DAT_80095ba0;
    while ((uVar2 & 0x8000000) == 0) {
      iVar3 = FUN_8008219c();
      if (iVar3 != 0) {
        return 0xffffffff;
      }
      uVar2 = *DAT_80095ba0;
    }
    while (iVar4 = iVar4 + -1, iVar4 != -1) {
      *param_2 = *DAT_80095b9c;
      param_2 = param_2 + 1;
    }
    if (iVar7 != 0) {
      *DAT_80095ba0 = 0x4000003;
      *DAT_80095ba4 = (int)param_2;
      *DAT_80095ba8 = iVar7 << 0x10 | 0x10;
      *DAT_80095bac = 0x1000200;
    }
    uVar1 = 0;
  }
  return uVar1;
}

