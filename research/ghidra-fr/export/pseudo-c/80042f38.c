/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80042f38(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  _DAT_1f800010 = (int)*(short *)(param_1 + 0x44);
  _DAT_1f800014 = (int)*(short *)(param_1 + 0x46);
  uVar1 = *(undefined2 *)(param_1 + 0x14);
  iVar7 = 0;
  sVar2 = *(short *)(param_1 + 0x30);
  sVar3 = *(short *)(param_1 + 0x32);
  iVar6 = (int)*(short *)(param_1 + 0x48);
  iVar4 = (int)*(short *)(param_1 + 0x4a);
  puVar5 = &DAT_1f800020;
  do {
    *(undefined4 *)(puVar5 + 4) = 0;
    *(undefined4 *)(puVar5 + 0x14) = 0;
    iVar7 = iVar7 + 1;
    puVar5 = puVar5 + 0x24;
  } while (iVar7 < 4);
  iVar8 = 4;
  iVar7 = 0x1f8000b0;
  do {
    *(undefined4 *)(iVar7 + 4) = 0xffffff;
    *(undefined4 *)(iVar7 + 0x14) = 0xffffff;
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + 0x24;
  } while (iVar8 < 8);
  iVar7 = 0;
  puVar5 = &DAT_1f800020;
  do {
    *(short *)(puVar5 + 0x12) = sVar3;
    *(short *)(puVar5 + 10) = sVar3;
    *(undefined4 *)(puVar5 + 0xc) = 0xffffff;
    *(undefined4 *)(puVar5 + 0x1c) = 0xffffff;
    puVar5[3] = 8;
    puVar5[7] = 0x38;
    iVar7 = iVar7 + 1;
    puVar5 = puVar5 + 0x24;
  } while (iVar7 < 8);
  _DAT_1f800000 = iVar6 * _DAT_1f800010;
  if (_DAT_1f800000 < 0) {
    _DAT_1f800000 = _DAT_1f800000 + 0xfff;
  }
  _DAT_1f800004 = iVar4 * _DAT_1f800010;
  _DAT_1f800000 = _DAT_1f800000 >> 0xc;
  if (_DAT_1f800004 < 0) {
    _DAT_1f800004 = _DAT_1f800004 + 0xfff;
  }
  _DAT_1f800004 = _DAT_1f800004 >> 0xc;
  _DAT_1f800008 = _DAT_1f800010 * 0xf0;
  if (_DAT_1f800008 < 0) {
    _DAT_1f800008 = _DAT_1f800008 + 0xfff;
  }
  _DAT_1f800008 = _DAT_1f800008 >> 0xc;
  _DAT_1f800094 = _DAT_1f800000 + sVar2;
  _DAT_1f80009c = _DAT_1f800004 + sVar2;
  _DAT_1f8000e4 = _DAT_1f800008 + sVar2;
  _DAT_1f800028 = sVar2 - _DAT_1f800000;
  _DAT_1f800030 = sVar2 - _DAT_1f800004;
  iVar7 = 0x100;
  _DAT_1f800108 = sVar2 - _DAT_1f800008;
  _DAT_1f800070 = _DAT_1f800028;
  _DAT_1f800078 = _DAT_1f800030;
  _DAT_1f8000b8 = _DAT_1f800030;
  _DAT_1f8000dc = _DAT_1f80009c;
  _DAT_1f80012c = _DAT_1f8000e4;
  _DAT_1f80004c = _DAT_1f800094;
  _DAT_1f800054 = _DAT_1f80009c;
  _DAT_1f8000c0 = _DAT_1f800108;
  _DAT_1f800100 = _DAT_1f800030;
  _DAT_1f800124 = _DAT_1f80009c;
  do {
    iVar8 = FUN_800866f8(iVar7);
    iVar8 = iVar6 * iVar8;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800000 = (iVar8 >> 0xc) * _DAT_1f800010;
    if (_DAT_1f800000 < 0) {
      _DAT_1f800000 = _DAT_1f800000 + 0xfff;
    }
    _DAT_1f800000 = _DAT_1f800000 >> 0xc;
    iVar8 = FUN_800866f8(iVar7);
    iVar8 = iVar4 * iVar8;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800004 = (iVar8 >> 0xc) * _DAT_1f800010;
    if (_DAT_1f800004 < 0) {
      _DAT_1f800004 = _DAT_1f800004 + 0xfff;
    }
    _DAT_1f800004 = _DAT_1f800004 >> 0xc;
    iVar8 = FUN_800866f8(iVar7);
    iVar8 = iVar8 * 0xf0;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800008 = (iVar8 >> 0xc) * _DAT_1f800010;
    if (_DAT_1f800008 < 0) {
      _DAT_1f800008 = _DAT_1f800008 + 0xfff;
    }
    _DAT_1f800008 = _DAT_1f800008 >> 0xc;
    _DAT_1f8000a4 = _DAT_1f800000 + sVar2;
    _DAT_1f8000ac = _DAT_1f800004 + sVar2;
    _DAT_1f8000f4 = _DAT_1f800008 + sVar2;
    _DAT_1f800038 = sVar2 - _DAT_1f800000;
    _DAT_1f800040 = sVar2 - _DAT_1f800004;
    _DAT_1f800118 = sVar2 - _DAT_1f800008;
    _DAT_1f800080 = _DAT_1f800038;
    _DAT_1f800088 = _DAT_1f800040;
    _DAT_1f8000ec = _DAT_1f8000ac;
    _DAT_1f80013c = _DAT_1f8000f4;
    _DAT_1f80005c = _DAT_1f8000a4;
    _DAT_1f800064 = _DAT_1f8000ac;
    _DAT_1f8000c8 = _DAT_1f800040;
    _DAT_1f8000d0 = _DAT_1f800118;
    _DAT_1f800110 = _DAT_1f800040;
    _DAT_1f800134 = _DAT_1f8000ac;
    iVar8 = FUN_80086628(iVar7);
    iVar8 = iVar6 * iVar8;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800000 = (iVar8 >> 0xc) * _DAT_1f800014;
    if (_DAT_1f800000 < 0) {
      _DAT_1f800000 = _DAT_1f800000 + 0xfff;
    }
    _DAT_1f800000 = _DAT_1f800000 >> 0xc;
    iVar8 = FUN_80086628(iVar7);
    iVar8 = iVar4 * iVar8;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800004 = (iVar8 >> 0xc) * _DAT_1f800014;
    if (_DAT_1f800004 < 0) {
      _DAT_1f800004 = _DAT_1f800004 + 0xfff;
    }
    _DAT_1f800004 = _DAT_1f800004 >> 0xc;
    iVar8 = FUN_80086628(iVar7);
    iVar8 = iVar8 * 0xf0;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xfff;
    }
    _DAT_1f800008 = (iVar8 >> 0xc) * _DAT_1f800014;
    if (_DAT_1f800008 < 0) {
      _DAT_1f800008 = _DAT_1f800008 + 0xfff;
    }
    _DAT_1f800008 = _DAT_1f800008 >> 0xc;
    _DAT_1f800082 = _DAT_1f800000 + sVar3;
    _DAT_1f80008a = _DAT_1f800004 + sVar3;
    _DAT_1f80011a = _DAT_1f800008 + sVar3;
    _DAT_1f80003a = sVar3 - _DAT_1f800000;
    _DAT_1f800042 = sVar3 - _DAT_1f800004;
    iVar8 = 0;
    _DAT_1f8000d2 = sVar3 - _DAT_1f800008;
    puVar5 = &DAT_1f800020;
    _DAT_1f8000a6 = _DAT_1f800082;
    _DAT_1f8000ae = _DAT_1f80008a;
    _DAT_1f8000ee = _DAT_1f800042;
    _DAT_1f8000f6 = _DAT_1f8000d2;
    _DAT_1f80005e = _DAT_1f80003a;
    _DAT_1f800066 = _DAT_1f800042;
    _DAT_1f8000ca = _DAT_1f800042;
    _DAT_1f800112 = _DAT_1f80008a;
    _DAT_1f800136 = _DAT_1f80008a;
    _DAT_1f80013e = _DAT_1f80011a;
    do {
      FUN_8004d5b8(puVar5,param_2,uVar1,2);
      iVar8 = iVar8 + 1;
      *(undefined4 *)(puVar5 + 8) = *(undefined4 *)(puVar5 + 0x18);
      *(undefined4 *)(puVar5 + 0x10) = *(undefined4 *)(puVar5 + 0x20);
      puVar5 = puVar5 + 0x24;
    } while (iVar8 < 8);
    iVar7 = iVar7 + 0x100;
  } while (iVar7 < 0x401);
  return;
}

