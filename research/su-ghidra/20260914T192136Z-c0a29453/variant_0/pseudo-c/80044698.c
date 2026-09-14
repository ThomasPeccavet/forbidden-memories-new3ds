/* Analysis pseudo-C, not buildable source. */

bool FUN_80044698(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                 undefined2 param_5)

{
  int iVar1;
  
  iVar1 = FUN_80044570(param_1,3);
  if (iVar1 != 0) {
    FUN_80090408(&DAT_800f3c30,s_bu_02X__s_800104c4,param_1,param_2);
    DAT_8009c7c8 = param_5;
    DAT_8009c7ba = param_4;
    DAT_8009c7c4 = param_3;
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2b8(param_1);
  }
  return iVar1 != 0;
}

