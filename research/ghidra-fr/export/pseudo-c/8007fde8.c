/* Analysis pseudo-C, not buildable source. */

void FUN_8007fde8(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  FUN_8007fccc(s_ClearImage_80012170,param_1);
  (**(code **)(PTR_PTR_80095a90 + 8))
            (*(undefined4 *)(PTR_PTR_80095a90 + 0xc),param_1,8,
             (param_4 & 0xff) << 0x10 | (param_3 & 0xff) << 8 | param_2 & 0xff);
  return;
}

