/* Analysis pseudo-C, not buildable source. */

void FUN_8007d654(void)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_80094e0c = DAT_80094e0c + DAT_80094e08 * 4;
  DAT_80094e10 = DAT_80094e10 + -1;
  iVar1 = FUN_800746b8(0xffffffff);
  if (DAT_80094e20 + 0x4b0 < iVar1) {
    DAT_80094e10 = -1;
  }
  if ((DAT_80094e10 == 0) || (iVar1 = FUN_800746b8(0xffffffff), DAT_80094e20 + 0x4b0 < iVar1)) {
    FUN_8007d7cc(1);
    if (DAT_80094e2c != (code *)0x0) {
      uVar2 = 2;
      if (DAT_80094e10 < 0) {
        uVar2 = 5;
      }
      (*DAT_80094e2c)(uVar2,DAT_80094e18);
    }
  }
  return;
}

