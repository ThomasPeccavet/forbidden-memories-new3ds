/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_800422c0(int param_1,undefined2 param_2,undefined2 param_3,undefined2 *param_4)

{
  code *pcVar1;
  int iVar2;
  
  *param_4 = param_2;
  param_4[1] = param_3;
  *(uint *)(param_4 + 2) = (uint)*(byte *)(param_1 + 0x65);
  FUN_80087838();
  FUN_80087858(300);
  _DAT_1f800308 =
       CONCAT22((ushort)*(byte *)(param_1 + 0x21) << 4,(ushort)*(byte *)(param_1 + 0x20) << 4);
  _DAT_1f80030c = CONCAT22(DAT_1f80030c_2,(ushort)*(byte *)(param_1 + 0x22) << 4);
  FUN_80088bd8(&DAT_1f800308,&DAT_1f8002d0);
  _DAT_1f8002e4 = 0;
  _DAT_1f8002e8 = 0;
  _DAT_1f8002ec = 300;
  if ((*(uint *)(param_1 + 4) & 0x8000000) == 0) {
    _DAT_1f800308 = (int)*(short *)(param_1 + 0x44);
    _DAT_1f80030c = (uint)*(short *)(param_1 + 0x46);
    _DAT_1f800310 = 0x1000;
    FUN_800875f8(&DAT_1f8002d0,&DAT_1f800308);
  }
  FUN_80085558(&DAT_1f8002d0);
  _DAT_1f800318 = 0;
  _DAT_1f800310 = 0x200;
  _DAT_1f800308 = 0;
  _DAT_1f80031a = 0x200;
  _DAT_1f80031c = 0;
  _DAT_1f800314 = 0;
  _DAT_1f80030c = _DAT_1f80030c & 0xffff0000;
  FUN_80089c78(&DAT_1f800308,&DAT_1f800310,&DAT_1f800318);
  iVar2 = getCopReg(2,0x18);
  pcVar1 = *(code **)(param_1 + 0x10);
  if (pcVar1 != (code *)0x0) {
    if ((int)pcVar1 < 0) {
      (*pcVar1)(param_1,iVar2);
    }
    if (iVar2 < 0) {
      _DAT_1f8002d0 = -_DAT_1f8002d0;
      _DAT_1f8002d6 = -_DAT_1f8002d6;
      _DAT_1f8002dc = -_DAT_1f8002dc;
      _DAT_1f8002d4 = -_DAT_1f8002d4;
      _DAT_1f8002da = -_DAT_1f8002da;
      _DAT_1f8002e0 = -_DAT_1f8002e0;
      FUN_80087738(&DAT_1f8002d0);
      FUN_80089c78(&DAT_1f800308,&DAT_1f800310,&DAT_1f800318);
      iVar2 = getCopReg(2,0x18);
    }
  }
  return iVar2;
}

