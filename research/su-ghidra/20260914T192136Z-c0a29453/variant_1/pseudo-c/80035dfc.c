/* Analysis pseudo-C, not buildable source. */

int FUN_80035dfc(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_8008f708();
  if (param_1 == 0) {
    trap(0x1c00);
  }
  if ((param_1 == -1) && (iVar1 == -0x80000000)) {
    trap(0x1800);
  }
  return iVar1 % param_1;
}

