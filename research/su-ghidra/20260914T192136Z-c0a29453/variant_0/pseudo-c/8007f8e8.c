/* Analysis pseudo-C, not buildable source. */

uint FUN_8007f8e8(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 7;
  if (uVar1 == 3) {
LAB_8007f934:
    FUN_8008fa78(s_ResetGraph_jtb__08x_env__08x_80012094,
                 &PTR_s__Id__sys_c_v_1_140_1998_01_12_07_80095a50,&DAT_80095a98);
LAB_8007f950:
    FUN_800827c0(&DAT_80095a98,0,0x80);
    FUN_800748d8();
    FUN_800827e8((uint)PTR_PTR_80095a90 & 0xffffff);
    DAT_80095a98 = FUN_80081ef0(param_1);
    DAT_80095a99 = 1;
    DAT_80095a9c = *(undefined2 *)(&DAT_80095b18 + (uint)DAT_80095a98 * 4);
    DAT_80095a9e = *(undefined2 *)(&DAT_80095b24 + (uint)DAT_80095a98 * 4);
    FUN_800827c0(&DAT_80095aa8,0xffffffff,0x5c);
    FUN_800827c0(&DAT_80095b04,0xffffffff,0x14);
    uVar1 = (uint)DAT_80095a98;
  }
  else {
    if (uVar1 < 4) {
      if (uVar1 == 0) goto LAB_8007f934;
    }
    else if (uVar1 == 5) goto LAB_8007f950;
    if (1 < DAT_80095a9a) {
      (*(code *)PTR_FUN_80095a94)(s_ResetGraph__d_____800120b4,param_1);
    }
    uVar1 = (**(code **)(PTR_PTR_80095a90 + 0x34))(1);
  }
  return uVar1;
}

