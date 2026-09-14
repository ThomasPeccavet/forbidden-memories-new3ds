/* Analysis pseudo-C, not buildable source. */

void FUN_8007fe78(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  FUN_8007fccc(s_ClearImage2_8001217c,param_1);
  (**(code **)(PTR_PTR_80095a90 + 8))
            (*(undefined4 *)(PTR_PTR_80095a90 + 0xc),param_1,8,
             (param_4 & 0xff) << 0x10 | (param_3 & 0xff) << 8 | 0x80000000 | param_2 & 0xff);
  return;
}

