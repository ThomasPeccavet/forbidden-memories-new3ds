/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80017860(void)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 extraout_at;
  int unaff_gp;
  short local_18;
  short sStack_16;
  
  FUN_8001704c();
  FUN_80087858((int)DAT_800f11ee);
  FUN_80087838(0xa0,0x6c);
  DAT_800f11e2 = *(undefined2 *)(unaff_gp + 0x18);
  DAT_800f11e0 = 0x14e;
  DAT_800f11e4 = 0x3fe;
  FUN_80013448();
  FUN_80085558(&DAT_800ff4d0);
  _DAT_1f8003e0 = 1000;
  _DAT_1f8003e4 = CONCAT22(DAT_1f8003e4_2,1000);
  setCopReg(2,in_zero,1000);
  setCopReg(2,extraout_at,_DAT_1f8003e4);
  copFunction(2,0x180001);
  uVar1 = getCopReg(2,0xe);
  local_18 = (short)uVar1;
  sStack_16 = (short)((uint)uVar1 >> 0x10);
  *(short *)(unaff_gp + 0x27c) = local_18 + -0xa0;
  *(short *)(unaff_gp + 0x27e) = sStack_16 + -0x6c;
  FUN_80087838(0,0);
  FUN_8001704c();
  return;
}

