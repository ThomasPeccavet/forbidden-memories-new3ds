/* Analysis pseudo-C, not buildable source. */

void FUN_8005d7b0(int param_1,int param_2,undefined1 *param_3,char *param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = FUN_80086dd8((DAT_800f6c28 - param_1) * (DAT_800f6c28 - param_1) +
                       (DAT_800f6c30 - param_2) * (DAT_800f6c30 - param_2));
  iVar4 = DAT_800f6c34 * DAT_800f6c30;
  iVar6 = DAT_800f6c3c - DAT_800f6c30;
  iVar5 = DAT_800f6c28 - DAT_800f6c34;
  iVar7 = DAT_800f6c28 * DAT_800f6c3c;
  iVar3 = FUN_80086dd8(iVar6 * iVar6 + iVar5 * iVar5);
  *param_3 = 0xff;
  *param_4 = '\0';
  if (0 < iVar2 + -700) {
    iVar2 = 0xff - (iVar2 + -700) / 0xc;
    if (iVar2 < 0x10) {
      iVar2 = 0x10;
    }
    *param_3 = (char)iVar2;
  }
  if (iVar3 != 0) {
    iVar4 = param_1 * iVar6 + param_2 * iVar5 + (iVar4 - iVar7);
    iVar7 = iVar4 / iVar3;
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar4 == -0x80000000)) {
      trap(0x1800);
    }
    iVar4 = iVar7;
    if (iVar7 < 0) {
      iVar4 = iVar7 + 0xf;
    }
    iVar4 = iVar4 >> 4;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    if (0x7f < iVar4) {
      iVar4 = 0x7f;
    }
    cVar1 = (char)iVar4;
    if (iVar7 < 1) {
      cVar1 = -cVar1;
    }
    *param_4 = cVar1;
  }
  return;
}

