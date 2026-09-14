/* Analysis pseudo-C, not buildable source. */

void FUN_8007d4dc(undefined1 param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_80094e24 = FUN_800746b8(0xffffffff);
  if ((DAT_80094e14 & 1) == 0) {
    if (0 < DAT_80094e10) {
      FUN_8007e968(DAT_80094e0c,DAT_80094e08);
      DAT_80094e0c = DAT_80094e0c + DAT_80094e08 * 4;
      DAT_80094e10 = DAT_80094e10 + -1;
    }
    iVar1 = FUN_800746b8(0xffffffff);
    if (DAT_80094e20 + 0x4b0 < iVar1) {
      DAT_80094e10 = -1;
    }
    if ((DAT_80094e10 != 0) && (iVar1 = FUN_800746b8(0xffffffff), iVar1 <= DAT_80094e20 + 0x4b0)) {
      return;
    }
    FUN_8007d7cc(1);
    param_1 = 2;
  }
  else {
    if (0 < DAT_80094e10) {
      FUN_8007ea88(DAT_80094e0c,DAT_80094e08);
      DAT_80094e18 = param_2;
      return;
    }
    FUN_8007d7cc(1);
  }
  if (DAT_80094e2c != (code *)0x0) {
    if (DAT_80094e10 < 0) {
      param_1 = 5;
    }
    (*DAT_80094e2c)(param_1,param_2);
  }
  return;
}

