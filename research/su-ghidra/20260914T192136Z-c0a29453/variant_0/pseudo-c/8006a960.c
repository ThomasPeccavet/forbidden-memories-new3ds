/* Analysis pseudo-C, not buildable source. */

undefined4
FUN_8006a960(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_8006a9ec(param_1,&DAT_800f6f08);
  uVar2 = 0xffffffff;
  if (iVar1 == 0) {
    iVar1 = FUN_8007eca8(&DAT_800f6f08);
    uVar2 = FUN_80069d90(&DAT_800f6f08,param_2,param_3,iVar1 + (DAT_800f6f0c + 0x7ffU >> 0xb),
                         param_4,param_5);
  }
  return uVar2;
}

