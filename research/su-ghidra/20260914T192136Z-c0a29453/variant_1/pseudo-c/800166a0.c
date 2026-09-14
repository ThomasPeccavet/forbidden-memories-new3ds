/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800166a0(int param_1,undefined4 param_2,int param_3,int param_4)

{
  char *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  uint uVar7;
  char acStack_40 [8];
  char acStack_38 [8];
  undefined4 *local_30;
  
  if (0x172 < param_3 + 0x33U) {
    return;
  }
  if (param_4 < -0x3b) {
    return;
  }
  if (0xff < param_4) {
    return;
  }
  puVar5 = &DAT_1f800320;
  _DAT_1f8003e8 = (short)param_3;
  _DAT_1f8003ea = (short)param_4;
  _DAT_1f800000 = *(uint *)(param_1 + 4);
  uVar7 = *(ushort *)(param_1 + 0x14) | 0x10000;
  local_30 = &DAT_801a7ad8 + (uint)*(byte *)(param_1 + 0x6a) * 7;
  _DAT_1f800320 = _DAT_1f800000;
  *(undefined1 *)(param_1 + 0x69) = 0;
  if ((*(ushort *)(param_1 + 8) & 4) != 0) {
    uVar7 = *(ushort *)(param_1 + 0x14) | 0xf0000;
    iVar4 = FUN_800422c0(param_1,_DAT_1f8003e8 + 0x1a,_DAT_1f8003ea + 0x1e,&DAT_1f8003e0);
    if (iVar4 < 0) {
      return;
    }
    DAT_1f800347 = 9;
    _DAT_1f800348 = CONCAT13(0x2c,(int3)*(undefined4 *)(param_1 + 0xc));
    if ((*(uint *)(param_1 + 0x20) & 0xffffff) == 0) {
      _DAT_1f800000 = _DAT_1f800320 | 0x80;
      _DAT_1f800320 = _DAT_1f800000;
    }
  }
  _DAT_1f80032c = 0x1e;
  _DAT_1f800334 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f800330 = 0xe10280;
  bVar2 = *(byte *)(param_1 + 0x67);
  if (bVar2 == 0) {
    if (*(char *)(param_1 + 0x69) != '\0') goto LAB_80016b8c;
    _DAT_1f800328 = 0x100020;
    _DAT_1f80032e = 0x6000;
    _DAT_1f800324 = _DAT_1f8003e8 + 10;
    _DAT_1f800326 = _DAT_1f8003ea + 0x28;
    bVar2 = *(byte *)(param_1 + 0x68);
    if (bVar2 == 0x15) {
      _DAT_1f80032e = 0x6040;
      FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
      _DAT_1f800330 = CONCAT22(_DAT_1f800332 + 2,_DAT_1f800330);
    }
    else if (bVar2 < 0x16) {
      if (bVar2 == 0x14) {
LAB_80016944:
        FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
        _DAT_1f800330 = CONCAT22(_DAT_1f800332 + 1,_DAT_1f800330);
      }
      else {
LAB_800169dc:
        iVar6 = 3;
        _DAT_1f800328 = 0x100008;
        _DAT_1f80032e = 0x7078;
        _DAT_1f800324 = _DAT_1f8003e8 + 5;
        FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
        _DAT_1f80032e = CONCAT11(0x58,DAT_1f80032e);
        _DAT_1f800328 = CONCAT22(8,_DAT_1f800328);
        _DAT_1f800324 = _DAT_1f8003e8 + 0xe;
        iVar4 = FUN_80016fe4(local_30);
        FUN_80035ce8((int)(short)iVar4,4,acStack_40);
        FUN_80035ce8(iVar4 >> 0x10,4,acStack_38);
        do {
          DAT_1f80032e = acStack_40[iVar6] << 3;
          FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
          _DAT_1f800326 = _DAT_1f800326 + 8;
          pcVar1 = acStack_38 + iVar6;
          iVar6 = iVar6 + -1;
          _DAT_1f80032e = CONCAT11(DAT_1f80032f,*pcVar1 << 3);
          FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
          _DAT_1f800324 = _DAT_1f800324 + 8;
          _DAT_1f800326 = _DAT_1f800326 + -8;
        } while (-1 < iVar6);
      }
    }
    else {
      if (bVar2 != 0x16) {
        if (bVar2 == 0x17) {
          _DAT_1f80032e = 0x6020;
          goto LAB_80016944;
        }
        goto LAB_800169dc;
      }
      _DAT_1f80032e = 0x6060;
      FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
      _DAT_1f800330 = CONCAT22(_DAT_1f800332 + 3,_DAT_1f800330);
    }
    _DAT_1f80000c = 0xe;
    _DAT_1f800014 = *(undefined4 *)(param_1 + 0xc);
    _DAT_1f800004 = _DAT_1f8003e8 + 6;
    _DAT_1f800006 = _DAT_1f8003ea + 6;
    cVar3 = *(char *)(local_30 + 6);
    puVar5 = (undefined1 *)0x1f800000;
    _DAT_1f800010 = 0x380;
    _DAT_1f800012 = cVar3 + 0xe0;
    _DAT_1f800008 = 0x200028;
    DAT_1f80000e = (cVar3 % '\x05') * '(';
    DAT_1f80000f = (cVar3 / '\x05') * ' ';
  }
  else {
    if (0x28 < bVar2) goto LAB_80016b8c;
    _DAT_1f800328 = 0x10000c;
    _DAT_1f800324 = _DAT_1f8003e8 + 0xf;
    _DAT_1f800326 = _DAT_1f8003ea + 0xf;
    DAT_1f80032e = (bVar2 / 10) * '\f';
    DAT_1f80032f = 0x70;
    FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
    _DAT_1f80032e = CONCAT11(DAT_1f80032f,(bVar2 % 10) * '\f');
    _DAT_1f800324 = _DAT_1f800324 + 0xc;
  }
  FUN_800424b8(puVar5,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
LAB_80016b8c:
  _DAT_1f800328 = 0x3c0034;
  _DAT_1f80032e = 0x8000;
  _DAT_1f800324 = _DAT_1f8003e8;
  _DAT_1f800326 = _DAT_1f8003ea;
  if (*(char *)(param_1 + 0x67) != '\0') {
    _DAT_1f80032e = 0xc000;
  }
  if (*(char *)(param_1 + 0x69) != '\0') {
    _DAT_1f80032e = 0x8038;
    _DAT_1f800330 = 0xe10280;
  }
  FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar7,&DAT_1f8003e0);
  return;
}

