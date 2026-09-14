/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80078974(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_800f7160 == 0) {
    iVar1 = FUN_80078788(&DAT_800f7108);
    FUN_8007aca8(iVar1 + 1,param_1);
    uVar2 = DAT_800f710c;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

