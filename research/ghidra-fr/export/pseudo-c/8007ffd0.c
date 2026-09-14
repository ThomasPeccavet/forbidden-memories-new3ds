/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007ffd0(undefined4 *param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  
  FUN_8007fccc(s_MoveImage_800121a0,param_1);
  uVar1 = 0xffffffff;
  if (*(short *)(param_1 + 1) != 0) {
    if (*(short *)((int)param_1 + 6) == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      DAT_80095b3c = param_3 << 0x10 | param_2 & 0xffff;
      DAT_80095b38 = *param_1;
      DAT_80095b40 = param_1[1];
      uVar1 = (**(code **)(PTR_PTR_80095a90 + 8))
                        (*(undefined4 *)(PTR_PTR_80095a90 + 0x18),&DAT_80095b30,0x14,0);
    }
  }
  return uVar1;
}

