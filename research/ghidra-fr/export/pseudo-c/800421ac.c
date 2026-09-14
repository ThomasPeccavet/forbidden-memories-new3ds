/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_800421ac(uint param_1,undefined2 param_2,undefined2 param_3,undefined2 *param_4)

{
  undefined4 uVar1;
  
  *param_4 = param_2;
  param_4[1] = param_3;
  *(undefined4 *)(param_4 + 2) = 0;
  FUN_80087838();
  FUN_80087858(300);
  _DAT_1f800308 = (undefined2)((param_1 & 0xff) << 4);
  _DAT_1f80030a = (ushort)(param_1 >> 4) & 0xff0;
  _DAT_1f80030c = (ushort)(param_1 >> 0xc) & 0xff0;
  FUN_80088bd8(&DAT_1f800308,&DAT_1f8002d0);
  _DAT_1f8002e4 = 0;
  _DAT_1f8002e8 = 0;
  _DAT_1f8002ec = 300;
  FUN_80085558(&DAT_1f8002d0);
  _DAT_1f800318 = 0;
  _DAT_1f800308 = 0;
  _DAT_1f800310 = 0x200;
  _DAT_1f800312 = 0;
  _DAT_1f80030a = 0;
  _DAT_1f80031a = 0x200;
  _DAT_1f80031c = 0;
  _DAT_1f800314 = 0;
  _DAT_1f80030c = 0;
  FUN_80089c78(&DAT_1f800308,&DAT_1f800310,&DAT_1f800318);
  uVar1 = getCopReg(2,0x18);
  return uVar1;
}

