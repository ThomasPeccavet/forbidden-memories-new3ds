/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80081ef0(uint param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  DAT_80095bd0 = FUN_80074a54(0);
  DAT_80095bc4 = 0;
  DAT_80095bc0 = 0;
  uVar2 = param_1 & 7;
  if (uVar2 == 1) {
LAB_80081fac:
    *DAT_80095bac = 0x401;
    *DAT_80095bbc = *DAT_80095bbc | 0x800;
    *DAT_80095ba0 = 0x2000000;
    *DAT_80095ba0 = 0x1000000;
  }
  else {
    if (uVar2 < 2) {
      if (uVar2 != 0) goto LAB_80081ff8;
    }
    else {
      if (uVar2 == 3) goto LAB_80081fac;
      if (uVar2 != 5) goto LAB_80081ff8;
    }
    *DAT_80095bac = 0x401;
    *DAT_80095bbc = *DAT_80095bbc | 0x800;
    *DAT_80095ba0 = 0;
    FUN_800827c0(&DAT_800fdb88,0,0x1800);
  }
LAB_80081ff8:
  FUN_80074a54(DAT_80095bd0);
  uVar1 = 0;
  if ((param_1 & 7) == 0) {
    uVar1 = FUN_800822e0(param_1);
  }
  return uVar1;
}

