/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800445f8(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_80044570(param_1,2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2b8(param_1);
    do {
    } while (DAT_8009c7bc < 0);
    FUN_80044204(&DAT_800f3c20);
    FUN_8008b328(DAT_8009c7b0);
    do {
    } while (DAT_8009c7bc < 0);
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2c8(param_1);
    do {
      uVar2 = 1;
    } while (DAT_8009c7bc < 0);
  }
  return uVar2;
}

