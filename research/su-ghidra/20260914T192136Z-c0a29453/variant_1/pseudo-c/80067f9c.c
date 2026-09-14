/* Analysis pseudo-C, not buildable source. */

undefined1 * FUN_80067f9c(undefined1 *param_1,int param_2,uint param_3,uint param_4,byte param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int local_18 [6];
  
  uVar8 = (uint)param_5;
  iVar1 = param_2;
  if (param_2 < 0) {
    iVar1 = param_2 + 0xfff;
  }
  uVar4 = ((iVar1 >> 0xc) + 1) % 6;
  iVar1 = (int)uVar4 / 2;
  if ((uVar4 & 1) == 0) {
    iVar5 = iVar1 + 1;
    iVar2 = iVar1 + 2;
  }
  else {
    iVar2 = iVar1 + 1;
    iVar5 = iVar1 + 2;
  }
  iVar5 = iVar5 % 3;
  param_3 = param_3 & 0xffff;
  param_4 = param_4 & 0xffff;
  if (param_3 < 0x801) {
    iVar3 = param_3 * (0x1000 - param_4);
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xfff;
    }
    iVar3 = (iVar3 >> 0xc) * uVar8;
    local_18[iVar5] = iVar3;
    local_18[iVar1] = param_3 * 2 * uVar8 - iVar3;
  }
  else {
    iVar3 = param_3 * (0x1000 - param_4);
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xfff;
    }
    iVar3 = ((iVar3 >> 0xc) + param_4) * uVar8;
    local_18[iVar1] = iVar3;
    local_18[iVar5] = param_3 * 2 * uVar8 - iVar3;
  }
  iVar3 = (param_2 + 0x1000) % 0x6000 + iVar1 * -0x2000;
  iVar6 = iVar3 + -0x1000;
  if (iVar6 < 0) {
    iVar6 = 0x1000 - iVar3;
  }
  local_18[iVar2 % 3] =
       ((uint)((local_18[iVar1] - local_18[iVar5]) * iVar6) >> 0xc) + local_18[iVar5];
  uVar8 = local_18[0] + 0x800U >> 0xc;
  uVar4 = local_18[1] + 0x800U >> 0xc;
  uVar7 = local_18[2] + 0x800U >> 0xc;
  if (0xff < uVar8) {
    uVar8 = 0xff;
  }
  if (0xff < uVar4) {
    uVar4 = 0xff;
  }
  if (0xff < uVar7) {
    uVar7 = 0xff;
  }
  *param_1 = (char)uVar8;
  param_1[1] = (char)uVar4;
  param_1[2] = (char)uVar7;
  return param_1;
}

