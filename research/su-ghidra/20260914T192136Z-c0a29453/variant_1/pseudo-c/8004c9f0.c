/* Analysis pseudo-C, not buildable source. */

bool FUN_8004c9f0(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_8004c04c(*param_1);
  *param_1 = iVar1;
  if (iVar1 != -1) {
    iVar2 = FUN_8004c0bc(param_1);
    param_1[2] = iVar2;
    param_1[4] = *param_1;
    param_1[3] = *param_1 + iVar2;
  }
  return iVar1 == -1;
}

