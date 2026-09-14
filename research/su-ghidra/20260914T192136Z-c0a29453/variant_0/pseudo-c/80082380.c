/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80082380(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  FUN_8007fccc(s_LoadImage2_80012270,param_1);
  iVar1 = FUN_800746b8(0xffffffff);
  DAT_80095bd4 = iVar1 + 0xf0;
  DAT_80095bd8 = 0;
  uVar2 = *DAT_80095bac;
  while (((uVar2 & 0x1000000) != 0 || ((*DAT_80095ba0 & 0x4000000) == 0))) {
    iVar1 = FUN_8008219c();
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    uVar2 = *DAT_80095bac;
  }
  FUN_80074938(2,FUN_80082798);
  (**(code **)(PTR_PTR_80095a90 + 0x20))(param_1,param_2);
  return 0;
}

