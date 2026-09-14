/* Analysis pseudo-C, not buildable source. */

void FUN_8007fbcc(int param_1)

{
  undefined4 uVar1;
  
  if (1 < DAT_80095a9a) {
    (*(code *)PTR_FUN_80095a94)(s_SetDispMask__d_____80012124,param_1);
  }
  if (param_1 == 0) {
    FUN_800827c0(&DAT_80095b04,0xffffffff,0x14);
  }
  uVar1 = 0x3000001;
  if (param_1 != 0) {
    uVar1 = 0x3000000;
  }
  (**(code **)(PTR_PTR_80095a90 + 0x10))(uVar1);
  return;
}

