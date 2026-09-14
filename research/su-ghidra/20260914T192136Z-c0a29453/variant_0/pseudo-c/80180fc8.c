/* Analysis pseudo-C, not buildable source. */

void FUN_80180fc8(int param_1)

{
  int iVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0xc) & 0xffffff) == 0) {
    FUN_80040690();
  }
  else {
    iVar2 = *(byte *)(param_1 + 0xc) - 8;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    *(char *)(param_1 + 0xc) = (char)iVar2;
    iVar2 = *(byte *)(param_1 + 0xd) - 8;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    iVar1 = *(byte *)(param_1 + 0xe) - 8;
    *(char *)(param_1 + 0xd) = (char)iVar2;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    *(char *)(param_1 + 0xe) = (char)iVar1;
  }
  return;
}

