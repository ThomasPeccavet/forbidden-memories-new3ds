/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80051904(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = _DAT_8009c7fc;
  uVar1 = _DAT_8009c7f8;
  iVar5 = (int)DAT_8009c7fa - (int)DAT_8009c800._2_2_;
  iVar4 = iVar5;
  if (iVar5 < 0) {
    iVar4 = -iVar5;
  }
  if (0x800 < iVar4) {
    if (iVar5 < 1) {
      iVar5 = iVar5 + 0x1000;
    }
    else {
      iVar5 = iVar5 + -0x1000;
    }
  }
  if ((param_1 != 0) || (iVar5 != 0)) {
    uVar3 = (uint)*(ushort *)(PTR_DAT_8009c318 + 0xa6);
    iVar4 = (iVar5 * 0x500) / 0x180 + (int)DAT_8009c31e + uVar3;
    if (uVar3 == 0) {
      trap(0x1c00);
    }
    if ((uVar3 == 0xffffffff) && (iVar4 == -0x80000000)) {
      trap(0x1800);
    }
    DAT_8009c31e = (short)(iVar4 % (int)uVar3);
  }
  if ((param_1 == 0) && (DAT_8009c7fc == (short)DAT_8009c804)) {
    DAT_8009c800 = uVar1;
    DAT_8009c804 = uVar2;
    return;
  }
  iVar4 = (int)DAT_8009c7fc;
  if (iVar4 < 0x801) {
    if (0x3ff < iVar4) {
      DAT_8009c320 = 0x139;
      DAT_8009c800 = uVar1;
      DAT_8009c804 = uVar2;
      return;
    }
    iVar4 = iVar4 * 0x1a;
  }
  else {
    iVar5 = iVar4 + -0x1000;
    if (iVar5 < 0) {
      iVar5 = 0x1000 - iVar4;
    }
    if (0x3ff < iVar5) {
      DAT_8009c320 = 0xfec7;
      DAT_8009c800 = uVar1;
      DAT_8009c804 = uVar2;
      return;
    }
    iVar4 = DAT_8009c7fc + -0x1000;
    if (iVar4 < 0) {
      iVar4 = (0x1000 - DAT_8009c7fc) * -0x1a;
      iVar5 = (int)((ulonglong)((longlong)iVar4 * 0x60606061) >> 0x20);
      goto LAB_80051aa8;
    }
    iVar4 = iVar4 * -0x1a;
  }
  iVar5 = (int)((ulonglong)((longlong)iVar4 * 0x60606061) >> 0x20);
LAB_80051aa8:
  DAT_8009c320 = (short)(iVar5 >> 5) - (short)(iVar4 >> 0x1f);
  DAT_8009c800 = _DAT_8009c7f8;
  DAT_8009c804 = _DAT_8009c7fc;
  return;
}

