/* Analysis pseudo-C, not buildable source. */

void FUN_80040530(short *param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  
  sVar1 = *param_1;
  sVar2 = param_1[1];
  iVar3 = (int)sVar2;
  DAT_8009c7a4 = DAT_8009c7a4 + 1;
  if (sVar1 < 0) {
    (&DAT_800f11c0)[param_1[0xf]] = sVar2;
    if (-1 < iVar3) {
      *(undefined2 *)(&DAT_800f1210 + iVar3 * 0x70) = 0xffff;
    }
  }
  else {
    *(short *)(&DAT_800f1212 + sVar1 * 0x70) = sVar2;
    if (-1 < iVar3) {
      *(short *)(&DAT_800f1210 + iVar3 * 0x70) = sVar1;
    }
  }
  param_1[4] = 0;
  return;
}

