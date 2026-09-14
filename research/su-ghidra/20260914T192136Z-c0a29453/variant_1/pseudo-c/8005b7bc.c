/* Analysis pseudo-C, not buildable source. */

void FUN_8005b7bc(undefined2 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 local_30;
  char local_2f;
  
  iVar1 = FUN_80086dd8((DAT_800f6c28 - param_3) * (DAT_800f6c28 - param_3) +
                       (DAT_800f6c30 - param_4) * (DAT_800f6c30 - param_4));
  iVar3 = DAT_800f6c34 * DAT_800f6c30;
  iVar5 = DAT_800f6c3c - DAT_800f6c30;
  iVar4 = DAT_800f6c28 - DAT_800f6c34;
  iVar6 = DAT_800f6c28 * DAT_800f6c3c;
  iVar2 = FUN_80086dd8(iVar5 * iVar5 + iVar4 * iVar4);
  local_30 = 0xff;
  local_2f = '\0';
  if (0 < iVar1 + -700) {
    iVar1 = 0xff - (iVar1 + -700) / 0xc;
    if (iVar1 < 0x10) {
      iVar1 = 0x10;
    }
    local_30 = (undefined1)iVar1;
  }
  if (iVar2 != 0) {
    iVar3 = param_3 * iVar5 + param_4 * iVar4 + (iVar3 - iVar6);
    iVar6 = iVar3 / iVar2;
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (iVar3 == -0x80000000)) {
      trap(0x1800);
    }
    iVar3 = iVar6;
    if (iVar6 < 0) {
      iVar3 = iVar6 + 0xf;
    }
    iVar3 = iVar3 >> 4;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (0x7f < iVar3) {
      iVar3 = 0x7f;
    }
    local_2f = (char)iVar3;
    if (iVar6 < 1) {
      local_2f = -local_2f;
    }
  }
  if (param_2 == 0) {
    FUN_80048eb8(param_1,local_30,(int)local_2f);
  }
  else {
    FUN_80048ae8(param_1,local_30,(int)local_2f);
  }
  return;
}

