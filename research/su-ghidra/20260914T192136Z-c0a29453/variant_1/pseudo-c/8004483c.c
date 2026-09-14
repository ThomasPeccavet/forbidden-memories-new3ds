/* Analysis pseudo-C, not buildable source. */

bool FUN_8004483c(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = FUN_80044570(param_1,0xc);
  if (iVar1 != 0) {
    *(undefined2 *)(unaff_gp + 0x522) = param_3;
    *(undefined4 *)(unaff_gp + 0x52c) = param_2;
    FUN_80044204(&DAT_800f3c10);
    FUN_8008b2b8(param_1);
  }
  return iVar1 != 0;
}

