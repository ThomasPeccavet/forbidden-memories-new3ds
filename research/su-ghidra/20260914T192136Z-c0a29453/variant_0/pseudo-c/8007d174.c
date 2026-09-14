/* Analysis pseudo-C, not buildable source. */

void FUN_8007d174(char param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == '\x05') {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(&DAT_80094d84 + (uint)DAT_80094cb4 * 4) + -1;
    if (iVar1 < 0) {
      return;
    }
  }
  DAT_80094cc8 = *(byte *)(param_2 + iVar1);
  DAT_80094ce4 = DAT_80094cc8 >> 7;
  DAT_80094ce5 = DAT_80094cc8 >> 6 & 1;
  DAT_80094ce6 = DAT_80094cc8 >> 5 & 1;
  DAT_80094ce7 = DAT_80094cc8 >> 1 & 1;
  FUN_8007d304(&DAT_80094cc0,param_2);
  return;
}

