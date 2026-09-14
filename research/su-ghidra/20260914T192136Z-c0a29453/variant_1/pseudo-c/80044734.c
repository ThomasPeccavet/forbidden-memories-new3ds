/* Analysis pseudo-C, not buildable source. */

bool FUN_80044734(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  
  iVar1 = FUN_80044570(param_1,0xb);
  if (iVar1 != 0) {
    DAT_8009c7ba = param_3;
    DAT_8009c7c4 = param_2;
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2b8(param_1);
  }
  return iVar1 != 0;
}

