/* Analysis pseudo-C, not buildable source. */

int FUN_8007d888(undefined4 param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((param_2 & 0x100) == 0) {
    iVar3 = FUN_8007ba00(param_2 & 0xff,param_1,0x1b,0,0xffffffff);
  }
  else {
    DAT_800f7160 = (uint)((param_2 & 0x20) == 0);
    uVar1 = FUN_8007ee38(FUN_800788e8);
    uVar2 = FUN_8007edf8(FUN_8007d95c);
    iVar3 = FUN_8007ba00(param_2 & 0xff,param_1,0x1b,0,0xffffffff);
    if (iVar3 == 0) {
      FUN_8007ee38(uVar1);
      FUN_8007edf8(uVar2);
      iVar3 = 0;
    }
  }
  return iVar3;
}

