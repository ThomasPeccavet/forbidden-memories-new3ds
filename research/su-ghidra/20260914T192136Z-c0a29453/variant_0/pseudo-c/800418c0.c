/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800418c0(int param_1,undefined4 param_2,uint param_3)

{
  bool bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  ushort uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  uint uVar12;
  undefined4 uVar13;
  ushort *puVar14;
  int local_30;
  int local_2c;
  
  local_30 = (int)*(short *)(param_1 + 0x30);
  local_2c = (int)*(short *)(param_1 + 0x32);
  if ((*(ushort *)(param_1 + 8) & 8) == 0) {
    local_30 = local_30 - DAT_8009c4c0;
    local_2c = local_2c - DAT_8009c4c2;
  }
  _DAT_1f80038c = *(short *)(param_1 + 0x48);
  _DAT_1f80038e = *(short *)(param_1 + 0x4a);
  _DAT_1f800392 = *(ushort *)(param_1 + 8) & 4;
  do {
    _DAT_1f80037c = *(uint *)(param_1 + 4);
    _DAT_1f800388 = (ushort)*(byte *)(param_1 + 0x5e);
    _DAT_1f80038a = (ushort)*(byte *)(param_1 + 0x5f);
    uVar12 = (uint)**(byte **)(param_1 + 0x4c);
    if (uVar12 == 0) {
      return;
    }
    _DAT_1f8003b4 = (uint)(*(byte **)(param_1 + 0x4c))[1];
    bVar1 = (_DAT_1f80037c & 0x1000000) == 0;
    if (bVar1) {
      bVar2 = *(byte *)(param_1 + 0x66);
      uVar4 = (ushort)*(byte *)(*(int *)(param_1 + 0x4c) + 2);
    }
    else {
      bVar2 = *(byte *)(param_1 + 0x66);
      uVar4 = (ushort)*(byte *)(*(int *)(param_1 + 0x4c) + 2) << 1;
    }
    _DAT_1f800394 = (uint)!bVar1;
    _DAT_1f80032c = bVar2 + uVar4;
    _DAT_1f800384 = *(ushort *)(param_1 + 0x40);
    _DAT_1f800386 = *(short *)(param_1 + 0x42);
    if ((*(ushort *)(param_1 + 8) & 0x20) != 0) {
      _DAT_1f800384 = _DAT_1f800384 + (*(byte *)(*(int *)(param_1 + 0x4c) + 3) & 0xf) * 0x10;
      _DAT_1f800386 = _DAT_1f800386 + (ushort)(*(byte *)(*(int *)(param_1 + 0x4c) + 3) >> 4);
    }
    puVar14 = *(ushort **)(param_1 + 0x4c);
    _DAT_1f800340 = (uint)*(byte *)(param_1 + 0x22) * 0x1680;
    _DAT_1f80033c = *(undefined2 *)(param_1 + 0x44);
    _DAT_1f80033e = *(undefined2 *)(param_1 + 0x46);
    _DAT_1f80033a = 0;
    _DAT_1f800338 = 0;
    puVar11 = puVar14 + 2;
    _DAT_1f800330 = _DAT_1f800384;
    _DAT_1f800332 = _DAT_1f800386;
    _DAT_1f8003ac = 0;
    _DAT_1f8003a8 = 0;
    _DAT_1f8003b0 = _DAT_1f80037c & 0x8000000;
    _DAT_1f800334 = CONCAT13(DAT_1f800334_3,*(undefined3 *)(param_1 + 0xc));
    if (_DAT_1f8003b0 != 0) {
      _DAT_1f80037c = _DAT_1f80037c & 0xf7ffffff;
    }
    if ((_DAT_1f80037c & 0x800000) != 0) {
      _DAT_1f80037c = _DAT_1f80037c & 0xf7ffffff;
      _DAT_1f8003ac = 0x2000;
      _DAT_1f8003a8 = 0x2000;
    }
    uVar13 = 0;
    _DAT_1f8003a0 = 0;
    _DAT_1f800390 = _DAT_1f80032c;
    if (_DAT_1f800392 == 0) goto LAB_80041bb4;
    uVar13 = 0x1f800344;
    DAT_1f800347 = 9;
    _DAT_1f800348 = CONCAT13(0x2c,*(undefined3 *)(param_1 + 0xc));
    DAT_8009c794 = 0;
    iVar5 = FUN_800422c0(param_1,local_30 + *(short *)(param_1 + 0x18),
                         local_2c + *(short *)(param_1 + 0x1a),&DAT_1f800398);
    if (iVar5 < 1) {
      return;
    }
  } while (DAT_8009c794 != 0);
  _DAT_1f8003a0 = 0xf0000;
LAB_80041bb4:
  param_3 = param_3 & 0xffff;
  do {
    puVar10 = puVar14 + 3;
    _DAT_1f800320 = _DAT_1f80037c;
    _DAT_1f800380 = *puVar10;
    _DAT_1f800382 = puVar14[4];
    uVar4 = _DAT_1f800382 >> 2 & 0x78;
    _DAT_1f800328 = uVar4 + 8;
    uVar3 = _DAT_1f800382 >> 6 & 0x78;
    _DAT_1f80032a = uVar3 + 8;
    if ((_DAT_1f8003b4 & 0x10) == 0) {
      uVar7 = (ushort)(char)(byte)*puVar11;
      uVar8 = (ushort)*(char *)((int)puVar14 + 5);
    }
    else {
      uVar6 = (*puVar10 & 0xc000) >> 6;
      uVar7 = (ushort)(byte)*puVar11 | (ushort)uVar6;
      if ((uVar6 & 0x200) != 0) {
        uVar7 = uVar7 | 0xfe00;
      }
      uVar6 = (puVar14[4] & 0xc000) >> 6;
      uVar8 = (ushort)*(byte *)((int)puVar14 + 5) | (ushort)uVar6;
      if ((uVar6 & 0x200) != 0) {
        uVar8 = uVar8 | 0xfe00;
      }
    }
    if (_DAT_1f8003a8 != 0) {
      uVar7 = -(uVar7 + _DAT_1f800328);
    }
    if ((_DAT_1f8003b4 & 0xe0) != 0) {
      _DAT_1f8003ac = (_DAT_1f800380 ^ _DAT_1f8003a8) & 0x2000;
      if (_DAT_1f800394 == 0) {
        iVar5 = (_DAT_1f800384 - 0x280) + (_DAT_1f800382 & 0xf) * 0x10;
        _DAT_1f80032c = _DAT_1f800390 + (*puVar10 >> 10 & 7);
        _DAT_1f800330 = ((ushort)iVar5 & 0xff) + 0x280;
        _DAT_1f800332 = _DAT_1f800386 + (short)((uint)iVar5 >> 8);
      }
      else {
        _DAT_1f80032c = _DAT_1f800390 + (*puVar10 >> 9 & 0xe);
        _DAT_1f800330 = _DAT_1f800384;
        _DAT_1f800332 = _DAT_1f800386 + (_DAT_1f800382 & 0x1f);
      }
    }
    _DAT_1f800324 = (short)local_30 + uVar7;
    _DAT_1f800326 = (short)local_2c + uVar8;
    uVar6 = (_DAT_1f800380 & 0x1f) * 8 + (uint)_DAT_1f800388;
    DAT_1f80032e = (char)uVar6;
    uVar9 = param_3 | 0x10000;
    DAT_1f80032f = (char)((_DAT_1f800380 & 0x3e0) >> 2) + DAT_1f80038a;
    _DAT_1f80032c = _DAT_1f80032c + (short)(uVar6 >> 8);
    if (_DAT_1f8003ac != 0) {
      uVar9 = param_3 | 0x20000;
      _DAT_1f800320 = _DAT_1f80037c | 0x800000;
      if (0xff < (ushort)(DAT_1f80032f + _DAT_1f80032a)) {
        _DAT_1f80032a = uVar3 + 7;
      }
      if (_DAT_1f800394 == 0) {
LAB_80041e78:
        if (DAT_1f80032e == '\0') {
          _DAT_1f800328 = uVar4 + 7;
          DAT_1f80032e = '\x01';
        }
      }
      else if ((((uVar6 & 0xff) + (uint)_DAT_1f800328 < 0x100) || (-1 < (int)(uVar6 * 0x1000000)))
              || (_DAT_1f80032c == 0x1f)) {
        if (DAT_1f80032e == '\0') {
          if (_DAT_1f80032c == 0x10) goto LAB_80041e78;
          DAT_1f80032e = -0x80;
          _DAT_1f8003b4 = _DAT_1f8003b4 | 0x80;
          _DAT_1f80032c = _DAT_1f80032c + -1;
        }
      }
      else {
        DAT_1f80032e = DAT_1f80032e + -0x80;
        _DAT_1f8003b4 = _DAT_1f8003b4 | 0x80;
        _DAT_1f80032c = _DAT_1f80032c + 1;
      }
    }
    if (_DAT_1f800392 == 0) {
      if (_DAT_1f8003b0 == 0) {
        uVar9 = param_3 | 0x30000;
        _DAT_1f800338 = _DAT_1f80038c - uVar7;
        _DAT_1f80033a = _DAT_1f80038e - uVar8;
        _DAT_1f800324 = _DAT_1f800324 + _DAT_1f800338;
        _DAT_1f800326 = _DAT_1f800326 + _DAT_1f80033a;
        goto LAB_80041f64;
      }
      if (((_DAT_1f800324 < 0x140) && (0 < (int)((int)_DAT_1f800324 + (uint)_DAT_1f800328))) &&
         ((_DAT_1f800326 < 0x100 && (0 < (int)((int)_DAT_1f800326 + (uint)_DAT_1f80032a)))))
      goto LAB_80041f64;
    }
    else {
LAB_80041f64:
      FUN_800424b8(&DAT_1f800320,uVar13,param_2,uVar9 | _DAT_1f8003a0,&DAT_1f800398);
    }
    uVar12 = uVar12 - 1;
    puVar11 = puVar11 + 3;
    puVar14 = puVar10;
    if (uVar12 == 0) {
      return;
    }
  } while( true );
}

