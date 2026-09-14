/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80082558(undefined4 *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  FUN_8007fccc(s_MoveImage_800121a0,param_1);
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
  uVar3 = 0xffffffff;
  if (*(short *)(param_1 + 1) != 0) {
    if (*(short *)((int)param_1 + 6) == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      DAT_80095b3c = param_3 << 0x10 | param_2 & 0xffff;
      DAT_80095b38 = *param_1;
      DAT_80095b40 = param_1[1];
      (**(code **)(PTR_PTR_80095a90 + 0x18))(&DAT_80095b30);
      uVar3 = 0;
    }
  }
  return uVar3;
}

