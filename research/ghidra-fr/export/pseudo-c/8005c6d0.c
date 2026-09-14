/* Analysis pseudo-C, not buildable source. */

void FUN_8005c6d0(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  param_1 = param_1 * 0xe20;
  iVar1 = -0x1000;
  if ((-0x1001 < param_2) && (iVar1 = 0x3000, param_2 < 0x3001)) {
    iVar1 = param_2;
  }
  *(int *)(&DAT_800f4f18 + param_1) = iVar1;
  if (param_3 < -0x1000) {
    iVar2 = -0x1000;
  }
  else {
    iVar2 = 0x3000;
    if (param_3 < 0x3001) {
      iVar2 = param_3;
    }
  }
  *(int *)(&DAT_800f4f1c + param_1) = iVar2;
  if (param_4 < -0x1000) {
    iVar3 = -0x1000;
  }
  else {
    iVar3 = 0x3000;
    if (param_4 < 0x3001) {
      iVar3 = param_4;
    }
  }
  *(int *)(&DAT_800f4f20 + param_1) = iVar3;
  if ((&DAT_800f4f89)[param_1] != '\x04') {
    if (((iVar1 == 0x800) && (iVar2 == 0x800)) && (iVar3 == 0x800)) {
      (&DAT_800f4f89)[param_1] = 0;
      return;
    }
    (&DAT_800f4f89)[param_1] = 3;
  }
  return;
}

