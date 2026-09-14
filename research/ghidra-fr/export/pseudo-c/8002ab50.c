/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8002ab50(int param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined1 auStack_20 [4];
  undefined1 auStack_1c [4];
  
  uVar1 = *(short *)(param_1 + 0x60) - 0x10;
  *(ushort *)(param_1 + 0x60) = uVar1;
  if ((int)((uint)uVar1 << 0x10) < 1) {
    FUN_80040690();
  }
  else {
    *(undefined1 *)(param_1 + 0xe) = *(undefined1 *)(param_1 + 0x60);
    FUN_800422c0(param_1,(int)*(short *)(param_1 + 0x30) + (int)*(short *)(param_1 + 0x18),
                 (int)*(short *)(param_1 + 0x32) + (int)*(short *)(param_1 + 0x1a),&DAT_1f800398);
    DAT_1f8002a3 = 6;
    _DAT_1f8002b8 = 0x55555555;
    _DAT_1f8002a4 = (undefined3)*(undefined4 *)(param_1 + 0xc);
    _DAT_1f8002a4 = CONCAT13(0x4c,_DAT_1f8002a4);
    _DAT_1f800300 = *(short *)(param_1 + 0x30) - _DAT_1f800398;
    _DAT_1f800308 = _DAT_1f800300 + *(short *)(param_1 + 0x3c);
    _DAT_1f800302 = *(short *)(param_1 + 0x32) - _DAT_1f80039a;
    _DAT_1f80031c = 0;
    _DAT_1f800314 = 0;
    _DAT_1f80030c = 0;
    _DAT_1f800304 = 0;
    _DAT_1f800312 = _DAT_1f800302 + *(short *)(param_1 + 0x3e);
    _DAT_1f80030a = _DAT_1f800302;
    _DAT_1f800310 = _DAT_1f800300;
    _DAT_1f800318 = _DAT_1f800308;
    _DAT_1f80031a = _DAT_1f800312;
    FUN_80087a38(&DAT_1f800300,&DAT_1f800308,&DAT_1f800310,&DAT_1f800318,0x1f8002a8,&DAT_1f8002ac,
                 &DAT_1f8002b4,0x1f8002b0,auStack_20,auStack_1c);
    FUN_8004d5b8(0x1f8002a0,param_2,*(undefined2 *)(param_1 + 0x14),1);
    DAT_1f8002a3 = 3;
    _DAT_1f8002a4 = CONCAT13(0x40,_DAT_1f8002a4);
    _DAT_1f8002ac = _DAT_1f8002b4;
    FUN_8004d5b8(0x1f8002a0,param_2,*(undefined2 *)(param_1 + 0x14),1);
  }
  return;
}

