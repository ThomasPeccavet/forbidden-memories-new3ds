/* Analysis pseudo-C, not buildable source. */

void FUN_80086798(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_2 - param_1;
  if (99 < iVar2) {
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (-param_1 * param_2 == -0x80000000)) {
      trap(0x1800);
    }
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (param_2 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    iVar1 = (-param_1 * param_2) / iVar2 << 8;
    iVar3 = iVar1 / param_3;
    if (param_3 == 0) {
      trap(0x1c00);
    }
    if ((param_3 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    if (iVar3 < -0x8000) {
      iVar3 = -0x8000;
    }
    if (0x7fff < iVar3) {
      iVar3 = 0x7fff;
    }
    FUN_80089b88(iVar3);
    FUN_80089b98((param_2 << 0xc) / iVar2 << 0xc);
  }
  return;
}

