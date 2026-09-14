/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80040c04(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  
  sVar5 = 1;
  _DAT_1f800320 = *(uint *)(param_1 + 4);
  if ((_DAT_1f800320 & 0x2000000) == 0) {
    if ((_DAT_1f800320 & 0x1000000) != 0) {
      sVar5 = 2;
    }
  }
  else {
    sVar5 = 4;
  }
  _DAT_1f80032c = (ushort)*(byte *)(param_1 + 0x66);
  _DAT_1f800324 = *(undefined4 *)(param_1 + 0x30);
  _DAT_1f800330 = *(undefined4 *)(param_1 + 0x40);
  _DAT_1f800334 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f80032e = *(ushort *)(param_1 + 0x5c);
  if ((*(ushort *)(param_1 + 8) & 8) == 0) {
    _DAT_1f800326 = (short)((uint)_DAT_1f800324 >> 0x10);
    _DAT_1f800324 = CONCAT22(_DAT_1f800326 - DAT_8009c4c2,_DAT_1f800324 - DAT_8009c4c0);
  }
  param_3 = param_3 & 0xffff;
  _DAT_1f80032a = *(undefined2 *)(param_1 + 0x3e);
  uVar3 = (uint)*(ushort *)(param_1 + 0x3c);
  _DAT_1f80037c = _DAT_1f800320 & 0x8000000;
  uVar4 = param_3 | 0x10000;
  if ((*(ushort *)(param_1 + 8) & 4) == 0) {
    if ((_DAT_1f800320 & 0x8000000) == 0) {
      _DAT_1f800340 = (uint)*(byte *)(param_1 + 0x22) * 0x1680;
      _DAT_1f80033c = *(undefined4 *)(param_1 + 0x44);
      uVar4 = param_3 | 0x30000;
      uVar2 = *(undefined4 *)(param_1 + 0x48);
      _DAT_1f800338 = (short)uVar2;
      _DAT_1f80033a = (short)((uint)uVar2 >> 0x10);
      _DAT_1f800324 = CONCAT22(_DAT_1f800326 + _DAT_1f80033a,_DAT_1f800324 + _DAT_1f800338);
      _DAT_1f800338 = uVar2;
    }
  }
  else {
    DAT_8009c794 = 0;
    iVar1 = FUN_800422c0(param_1,(int)_DAT_1f800324 + (int)*(short *)(param_1 + 0x18),
                         (int)_DAT_1f800326 + (int)*(short *)(param_1 + 0x1a),&DAT_1f800398);
    if (iVar1 < 1) {
      return;
    }
    DAT_1f800347 = 9;
    _DAT_1f800348 = CONCAT13(0x2c,(int3)_DAT_1f800334);
    if ((_DAT_1f800320 & 0x40000000) != 0) {
      FUN_80082da8(0x1f800344,1);
    }
    _DAT_1f80037c = 0x8000000;
    uVar4 = param_3 | 0xf0000;
  }
  do {
    _DAT_1f800328 = 0x40;
    if ((int)uVar3 < 0x40) {
      _DAT_1f800328 = (ushort)uVar3;
    }
    if (0x100 < (uint)DAT_1f80032e + (uint)_DAT_1f800328) {
      _DAT_1f800328 = 0x100 - (_DAT_1f80032e & 0xff);
    }
    FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar4,&DAT_1f800398);
    if (_DAT_1f80037c == 0) {
      _DAT_1f800338 = CONCAT22(_DAT_1f80033a,_DAT_1f800338 - _DAT_1f800328);
    }
    else {
      _DAT_1f800324 = CONCAT22(_DAT_1f800326,_DAT_1f800324 + _DAT_1f800328);
    }
    if (0xff < (uint)DAT_1f80032e + (uint)_DAT_1f800328) {
      _DAT_1f80032c = _DAT_1f80032c + sVar5;
    }
    uVar3 = uVar3 - _DAT_1f800328;
    _DAT_1f80032e = CONCAT11(DAT_1f80032f,DAT_1f80032e + DAT_1f800328);
  } while (uVar3 != 0);
  return;
}

