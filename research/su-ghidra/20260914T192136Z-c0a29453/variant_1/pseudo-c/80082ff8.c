/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80082ff8(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_8008305c(DAT_800ff388,param_1);
  if (iVar1 == -1) {
    param_1 = 0;
  }
  else {
    DAT_800ff388 = DAT_800ff388 + iVar1 * 4;
  }
  return param_1;
}

