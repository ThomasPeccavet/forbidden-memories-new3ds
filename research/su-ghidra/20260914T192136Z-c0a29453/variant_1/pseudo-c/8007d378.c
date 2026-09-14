/* Analysis pseudo-C, not buildable source. */

int FUN_8007d378(undefined4 *param_1,undefined4 param_2,undefined4 param_3,byte param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 local_20 [2];
  
  if ((DAT_80094e28 == 1) || (iVar1 = FUN_8007e820(), iVar1 != 0)) {
    iVar1 = 0;
  }
  else {
    DAT_80094e08 = 0x200;
    DAT_80094e0c = param_3;
    DAT_80094e10 = param_2;
    if (param_1 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)FUN_8007ed28(0);
      local_20[0] = *puVar2;
    }
    else {
      local_20[0] = *param_1;
    }
    iVar3 = FUN_8007ba00(param_4 | 0x20,local_20,6,FUN_8007d4a8,0xffffffff);
    iVar1 = 0;
    if (iVar3 != 0) {
      DAT_80094e20 = FUN_800746b8(0xffffffff);
      if ((DAT_80094e14 & 1) != 0) {
        DAT_80094e1c = FUN_8007ee38(FUN_8007d654);
      }
      DAT_80094e28 = 1;
      iVar1 = iVar3;
    }
  }
  return iVar1;
}

