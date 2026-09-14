/* Analysis pseudo-C, not buildable source. */

bool FUN_8007e2e8(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = DAT_80094e68 != 1;
  if (bVar1) {
    DAT_80094e48 = 0xffffffff;
    DAT_80094e4c = 0;
    DAT_80094e54 = 0;
    DAT_80094e50 = param_1;
    DAT_80094e58 = param_2;
    DAT_80094e5c = FUN_8007edf8(FUN_8007e3e4);
    DAT_80094e60 = FUN_8007ee18(FUN_8007e6c0);
    DAT_80094e68 = 1;
  }
  return bVar1;
}

