/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8005c994(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_80073c4c(param_1,0,0);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = FUN_80073c7c(iVar1,0,2);
    FUN_80073c6c(iVar1);
  }
  return uVar2;
}

