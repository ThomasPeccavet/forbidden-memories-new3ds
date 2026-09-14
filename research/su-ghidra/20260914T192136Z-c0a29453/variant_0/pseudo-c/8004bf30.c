/* Analysis pseudo-C, not buildable source. */

int FUN_8004bf30(byte *param_1,byte *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  if (param_3 == 0) {
    return -1;
  }
  while (param_3 = param_3 + -1, param_3 != 0) {
    uVar2 = (uint)*param_1;
    uVar1 = (uint)*param_2;
    if (uVar2 != uVar1) goto LAB_8004bf6c;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  uVar2 = (uint)*param_1;
  uVar1 = (uint)*param_2;
LAB_8004bf6c:
  return uVar2 - uVar1;
}

