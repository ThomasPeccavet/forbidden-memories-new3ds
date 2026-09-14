/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800418c0(int param_1,undefined4 param_2,uint param_3)

{
  bool bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  uint uVar8;
  ushort uVar9;
  ushort uVar10;
  uint uVar11;
  ushort *puVar12;
  ushort *puVar13;
  uint uVar14;
  undefined4 uVar15;
  int unaff_gp;
  ushort *puVar16;
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
    uVar14 = (uint)**(byte **)(param_1 + 0x4c);
    if (uVar14 == 0) {
      return;
    }
    _DAT_1f8003b4 = (uint)(*(byte **)(param_1 + 0x4c))[1];
    bVar1 = (_DAT_1f80037c & 0x1000000) == 0;
    if (bVar1) {
      bVar2 = *(byte *)(param_1 + 0x66);
      uVar6 = (ushort)*(byte *)(*(int *)(param_1 + 0x4c) + 2);
    }
    else {
      bVar2 = *(byte *)(param_1 + 0x66);
      uVar6 = (ushort)*(byte *)(*(int *)(param_1 + 0x4c) + 2) << 1;
    }
    _DAT_1f800394 = (uint)!bVar1;
    _DAT_1f80032c = bVar2 + uVar6;
    _DAT_1f800384 = *(ushort *)(param_1 + 0x40);
    _DAT_1f800386 = *(short *)(param_1 + 0x42);
    if ((*(ushort *)(param_1 + 8) & 0x20) != 0) {
      _DAT_1f800384 = _DAT_1f800384 + (*(byte *)(*(int *)(param_1 + 0x4c) + 3) & 0xf) * 0x10;
      _DAT_1f800386 = _DAT_1f800386 + (ushort)(*(byte *)(*(int *)(param_1 + 0x4c) + 3) >> 4);
    }
    puVar16 = *(ushort **)(param_1 + 0x4c);
    _DAT_1f800340 = (uint)*(byte *)(param_1 + 0x22) * 0x1680;
    _DAT_1f80033c = *(undefined2 *)(param_1 + 0x44);
    _DAT_1f80033e = *(undefined2 *)(param_1 + 0x46);
    _DAT_1f80033a = 0;
    _DAT_1f800338 = 0;
    puVar13 = puVar16 + 2;
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
    uVar15 = 0;
    _DAT_1f8003a0 = 0;
    _DAT_1f800390 = _DAT_1f80032c;
    if (_DAT_1f800392 == 0) goto LAB_80041bb4;
    uVar15 = 0x1f800344;
    DAT_1f800347 = 9;
    _DAT_1f800348 = CONCAT13(0x2c,*(undefined3 *)(param_1 + 0xc));
    sVar3 = *(short *)(param_1 + 0x18);
    sVar4 = *(short *)(param_1 + 0x1a);
    *(undefined4 *)(unaff_gp + 0x4fc) = 0;
    iVar7 = FUN_800422c0(param_1,local_30 + sVar3,local_2c + sVar4,&DAT_1f800398);
    if (iVar7 < 1) {
      return;
    }
  } while (*(int *)(unaff_gp + 0x4fc) != 0);
  _DAT_1f8003a0 = 0xf0000;
LAB_80041bb4:
  param_3 = param_3 & 0xffff;
  do {
    puVar12 = puVar16 + 3;
    _DAT_1f800320 = _DAT_1f80037c;
    _DAT_1f800380 = *puVar12;
    _DAT_1f800382 = puVar16[4];
    uVar6 = _DAT_1f800382 >> 2 & 0x78;
    _DAT_1f800328 = uVar6 + 8;
    uVar5 = _DAT_1f800382 >> 6 & 0x78;
    _DAT_1f80032a = uVar5 + 8;
    if ((_DAT_1f8003b4 & 0x10) == 0) {
      uVar9 = (ushort)(char)(byte)*puVar13;
      uVar10 = (ushort)*(char *)((int)puVar16 + 5);
    }
    else {
      uVar8 = (*puVar12 & 0xc000) >> 6;
      uVar9 = (ushort)(byte)*puVar13 | (ushort)uVar8;
      if ((uVar8 & 0x200) != 0) {
        uVar9 = uVar9 | 0xfe00;
      }
      uVar8 = (puVar16[4] & 0xc000) >> 6;
      uVar10 = (ushort)*(byte *)((int)puVar16 + 5) | (ushort)uVar8;
      if ((uVar8 & 0x200) != 0) {
        uVar10 = uVar10 | 0xfe00;
      }
    }
    if (_DAT_1f8003a8 != 0) {
      uVar9 = -(uVar9 + _DAT_1f800328);
    }
    if ((_DAT_1f8003b4 & 0xe0) != 0) {
      _DAT_1f8003ac = (_DAT_1f800380 ^ _DAT_1f8003a8) & 0x2000;
      if (_DAT_1f800394 == 0) {
        iVar7 = (_DAT_1f800384 - 0x280) + (_DAT_1f800382 & 0xf) * 0x10;
        _DAT_1f80032c = _DAT_1f800390 + (*puVar12 >> 10 & 7);
        _DAT_1f800330 = ((ushort)iVar7 & 0xff) + 0x280;
        _DAT_1f800332 = _DAT_1f800386 + (short)((uint)iVar7 >> 8);
      }
      else {
        _DAT_1f80032c = _DAT_1f800390 + (*puVar12 >> 9 & 0xe);
        _DAT_1f800330 = _DAT_1f800384;
        _DAT_1f800332 = _DAT_1f800386 + (_DAT_1f800382 & 0x1f);
      }
    }
    _DAT_1f800324 = (short)local_30 + uVar9;
    _DAT_1f800326 = (short)local_2c + uVar10;
    uVar8 = (_DAT_1f800380 & 0x1f) * 8 + (uint)_DAT_1f800388;
    DAT_1f80032e = (char)uVar8;
    uVar11 = param_3 | 0x10000;
    DAT_1f80032f = (char)((_DAT_1f800380 & 0x3e0) >> 2) + DAT_1f80038a;
    _DAT_1f80032c = _DAT_1f80032c + (short)(uVar8 >> 8);
    if (_DAT_1f8003ac != 0) {
      uVar11 = param_3 | 0x20000;
      _DAT_1f800320 = _DAT_1f80037c | 0x800000;
      if (0xff < (ushort)(DAT_1f80032f + _DAT_1f80032a)) {
        _DAT_1f80032a = uVar5 + 7;
      }
      if (_DAT_1f800394 == 0) {
LAB_80041e78:
        if (DAT_1f80032e == '\0') {
          _DAT_1f800328 = uVar6 + 7;
          DAT_1f80032e = '\x01';
        }
      }
      else if ((((uVar8 & 0xff) + (uint)_DAT_1f800328 < 0x100) || (-1 < (int)(uVar8 * 0x1000000)))
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
        uVar11 = param_3 | 0x30000;
        _DAT_1f800338 = _DAT_1f80038c - uVar9;
        _DAT_1f80033a = _DAT_1f80038e - uVar10;
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
      FUN_800424b8(&DAT_1f800320,uVar15,param_2,uVar11 | _DAT_1f8003a0,&DAT_1f800398);
    }
    uVar14 = uVar14 - 1;
    puVar13 = puVar13 + 3;
    puVar16 = puVar12;
    if (uVar14 == 0) {
      return;
    }
  } while( true );
}

