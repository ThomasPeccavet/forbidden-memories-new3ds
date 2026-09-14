/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80029acc(void)

{
  uint uVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 in_zero;
  undefined4 extraout_at;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = 0;
  FUN_80087838(0xd0,0x68);
  FUN_80087858(300);
  uVar4 = DAT_8009c864;
  FUN_80085558(&DAT_800ff4d0);
  _DAT_1f800200 = uRam80181000;
  _DAT_1f800204 = uRam80181004;
  DAT_1f800003 = 7;
  _DAT_1f800004 = 0x58000000;
  _DAT_1f80001c = 0x55555555;
  _DAT_1f800052 = 0;
  _DAT_1f80004a = 0;
  _DAT_1f800040 = _DAT_1f800040 & 0xffff;
  _DAT_1f800038 = _DAT_1f800038 & 0xffff;
  do {
    iVar6 = (0x400 - iVar9) * 0xff;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0x3ff;
    }
    uVar5 = (undefined1)(iVar6 >> 10);
    _DAT_1f80000c = CONCAT31(CONCAT21(CONCAT11(DAT_1f80000f,uVar5),uVar5),uVar5);
    _DAT_1f800014 = _DAT_1f80000c;
    _DAT_1f800068 = FUN_800866f8(iVar9);
    _DAT_1f800068 = DAT_800eb580 * _DAT_1f800068;
    if (_DAT_1f800068 < 0) {
      _DAT_1f800068 = _DAT_1f800068 + 0xfff;
    }
    _DAT_1f800068 = _DAT_1f800068 >> 0xc;
    if (_DAT_1f800068 == 0) break;
    _DAT_1f80006c = FUN_80086628(iVar9);
    _DAT_1f80006c = DAT_800eb580 * _DAT_1f80006c;
    if (_DAT_1f80006c < 0) {
      _DAT_1f80006c = _DAT_1f80006c + 0xfff;
    }
    _DAT_1f80006c = _DAT_1f80006c >> 0xc;
    _DAT_1f80004c = _DAT_1f80006c + _DAT_1f800204;
    _DAT_1f800044 = CONCAT22(_DAT_1f800046,_DAT_1f80004c);
    _DAT_1f80003c = CONCAT22(DAT_1f80003c_2,_DAT_1f80004c);
    _DAT_1f800054 = _DAT_1f80004c;
    FUN_8002981c(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800200,_DAT_1f800068);
    FUN_8002981c(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800200,-_DAT_1f800068);
    if (iVar9 != 0) {
      _DAT_1f80004c = _DAT_1f800204 - _DAT_1f80006c;
      _DAT_1f800044 = CONCAT22(_DAT_1f800046,_DAT_1f80004c);
      _DAT_1f80003c = CONCAT22(DAT_1f80003c_2,_DAT_1f80004c);
      _DAT_1f800054 = _DAT_1f80004c;
      FUN_8002981c(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800200,_DAT_1f800068);
      FUN_8002981c(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800200,-_DAT_1f800068);
    }
    _DAT_1f800048 = _DAT_1f800200 + _DAT_1f80006c;
    _DAT_1f800040 = CONCAT22(_DAT_1f800042,_DAT_1f800048);
    _DAT_1f800038 = CONCAT22(_DAT_1f80003a,_DAT_1f800048);
    _DAT_1f800050 = _DAT_1f800048;
    FUN_80029974(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800204,_DAT_1f800068);
    FUN_80029974(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800204,-_DAT_1f800068);
    if (iVar9 != 0) {
      _DAT_1f800048 = _DAT_1f800200 - _DAT_1f80006c;
      _DAT_1f800040 = CONCAT22(_DAT_1f800042,_DAT_1f800048);
      _DAT_1f800038 = CONCAT22(_DAT_1f80003a,_DAT_1f800048);
      _DAT_1f800050 = _DAT_1f800048;
      FUN_80029974(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800204,_DAT_1f800068);
      FUN_80029974(0x1f800000,uVar4,&DAT_1f800038,&DAT_1f800060,(int)_DAT_1f800204,-_DAT_1f800068);
    }
    iVar9 = iVar9 + 0x80;
  } while (iVar9 < 0x400);
  iVar9 = 0;
  DAT_1f800003 = 7;
  _DAT_1f80000c = 0xffffff;
  _DAT_1f800004 = 0x58000000;
  _DAT_1f80001c = 0x55555555;
  _DAT_1f800014 = 0;
  _DAT_1f800038 = _DAT_1f800038 & 0xffff;
  _DAT_1f800040 = _DAT_1f800040 & 0xffff;
  do {
    iVar8 = DAT_800eb580 + 0x80;
    iVar6 = FUN_800866f8(iVar9);
    iVar6 = iVar8 * iVar6;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    _DAT_1f800038 = CONCAT22(_DAT_1f80003a,_DAT_1f800200 + (short)(iVar6 >> 0xc));
    iVar6 = FUN_800866f8(iVar9 + 0x80);
    iVar6 = iVar8 * iVar6;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    _DAT_1f800040 = CONCAT22(_DAT_1f800042,_DAT_1f800200 + (short)(iVar6 >> 0xc));
    iVar6 = FUN_80086628(iVar9);
    iVar6 = iVar8 * iVar6;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    _DAT_1f80003c = CONCAT22(DAT_1f80003c_2,_DAT_1f800204 + (short)(iVar6 >> 0xc));
    iVar6 = FUN_80086628(iVar9 + 0x80);
    iVar6 = iVar8 * iVar6;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    _DAT_1f800044 = CONCAT22(_DAT_1f800046,_DAT_1f800204 + (short)(iVar6 >> 0xc));
    setCopReg(2,in_zero,_DAT_1f800038);
    setCopReg(2,extraout_at,_DAT_1f80003c);
    copFunction(2,0x180001);
    uVar1 = getCopReg(2,0xe);
    setCopReg(2,in_zero,_DAT_1f800040);
    setCopReg(2,extraout_at,_DAT_1f800044);
    copFunction(2,0x180001);
    uVar2 = getCopReg(2,0xe);
    iVar6 = 0;
    _DAT_1f80000a = (short)(uVar1 >> 0x10);
    _DAT_1f800008 = (undefined2)uVar1;
    sVar3 = (short)(iVar8 / 0x28);
    _DAT_1f800012 = _DAT_1f80000a - sVar3;
    _DAT_1f800010 = _DAT_1f800008;
    _DAT_1f800018 = (undefined2)uVar2;
    _DAT_1f800018 = CONCAT22(_DAT_1f800012,_DAT_1f800018);
    _DAT_1f800008 = uVar1;
    do {
      FUN_8004d5b8(0x1f800000,uVar4,1,1);
      iVar7 = (_DAT_1f800008 >> 0x10) - iVar8 / 0x28;
      _DAT_1f800008 = CONCAT22((short)iVar7,_DAT_1f800008);
      if (iVar7 * 0x10000 < 1) break;
      iVar6 = iVar6 + 1;
      _DAT_1f800012 = _DAT_1f800012 - sVar3;
      _DAT_1f800018 = CONCAT22(_DAT_1f80001a - sVar3,_DAT_1f800018);
    } while (iVar6 < 7);
    iVar9 = iVar9 + 0x80;
    if (0xfff < iVar9) {
      FUN_8005721c(0);
      FUN_80058b4c(0);
      FUN_80058860(0);
      return;
    }
  } while( true );
}

