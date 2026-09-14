/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80015c34(int param_1)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 extraout_at;
  
  FUN_80087858(300);
  FUN_80087838(0xa0,0x6c);
  FUN_80085558(&DAT_800ff4d0);
  _DAT_1f8003e0 = (uint)*(ushort *)(param_1 + 0x28);
  _DAT_1f8003e4 = CONCAT22(DAT_1f8003e4_2,*(undefined2 *)(param_1 + 0x2a));
  setCopReg(2,in_zero,_DAT_1f8003e0);
  setCopReg(2,extraout_at,_DAT_1f8003e4);
  copFunction(2,0x180001);
  uVar1 = getCopReg(2,0xe);
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) + -0x20;
  *(short *)(param_1 + 0x32) = *(short *)(param_1 + 0x32) + -0x1e;
  FUN_80087838(0,0);
  return;
}

