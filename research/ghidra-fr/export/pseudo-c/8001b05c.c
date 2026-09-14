/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_8001b05c(int param_1)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 extraout_at;
  short local_10;
  
  FUN_80087858((int)DAT_800f11ee);
  FUN_80087838(0xa0,0x6c);
  FUN_80085558(&DAT_800ff4d0);
  _DAT_1f8003e0 = CONCAT22(0xffe8,*(undefined2 *)(&DAT_80091aa8 + param_1 * 4));
  _DAT_1f8003e4 = CONCAT22(DAT_1f8003e4_2,*(undefined2 *)(&DAT_80091aaa + param_1 * 4));
  setCopReg(2,in_zero,_DAT_1f8003e0);
  setCopReg(2,extraout_at,_DAT_1f8003e4);
  copFunction(2,0x180001);
  uVar1 = getCopReg(2,0xe);
  FUN_80087838(0,0);
  local_10 = (short)uVar1;
  return (int)local_10;
}

