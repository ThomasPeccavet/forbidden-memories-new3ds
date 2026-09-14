/* Analysis pseudo-C, not buildable source. */

bool FUN_800448a8(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = FUN_80044570(param_1,8);
  if (iVar1 != 0) {
    FUN_80090408(&DAT_800f3c30,s_bu_02X__s_800104c4,param_1,param_2);
    *(undefined2 *)(unaff_gp + 0x530) = param_3;
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2b8(param_1);
  }
  return iVar1 != 0;
}

