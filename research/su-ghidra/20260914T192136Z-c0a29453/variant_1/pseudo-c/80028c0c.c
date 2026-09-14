/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80028c0c(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  char acStack_38 [8];
  char acStack_30 [8];
  
  iVar8 = *(int *)(param_1 + 0x54);
  if ((-1 < *(int *)(param_1 + 4)) && ((*(ushort *)(iVar8 + 8) & 0x40) != 0)) {
    uVar9 = (int)*(short *)(iVar8 + 0x14) - 1U & 0xffff | 0x10000;
    if ((*(ushort *)(iVar8 + 8) & 4) != 0) {
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar8 + 0x20);
      uVar4 = *(undefined4 *)(iVar8 + 0x44);
      uVar9 = *(uint *)(param_1 + 4) & 0xf7ffffff;
      *(uint *)(param_1 + 4) = uVar9;
      *(undefined4 *)(param_1 + 0x44) = uVar4;
      *(uint *)(param_1 + 4) = uVar9 | *(uint *)(iVar8 + 4) & 0x8000000;
      iVar5 = FUN_800422c0(param_1,(int)*(short *)(iVar8 + 0x30) + (int)*(short *)(iVar8 + 0x18),
                           (int)*(short *)(iVar8 + 0x32) + (int)*(short *)(iVar8 + 0x1a),
                           &DAT_1f800398);
      if (iVar5 < 1) {
        return;
      }
      DAT_1f800347 = 9;
      uVar9 = (int)*(short *)(iVar8 + 0x14) - 1U & 0xffff | 0xf0000;
      _DAT_1f800348 = (undefined3)*(undefined4 *)(iVar8 + 0xc);
      _DAT_1f800348 = CONCAT13(0x2c,_DAT_1f800348);
    }
    _DAT_1f800320 = *(uint *)(param_1 + 4);
    _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 0x13;
    _DAT_1f800328 = 0x600066;
    _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0x32;
    _DAT_1f800334 = *(undefined4 *)(iVar8 + 0xc);
    _DAT_1f800330 = *(undefined4 *)(param_1 + 0x40);
    _DAT_1f80032e = *(undefined2 *)(param_1 + 0x5c);
    _DAT_1f80032c = (ushort)*(byte *)(param_1 + 0x66);
    FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
    uVar4 = _DAT_1f800334;
    _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 0xc;
    _DAT_1f800328 = 0xe0060;
    _DAT_1f80032e = CONCAT11(DAT_1f80032f + '`',DAT_1f80032e);
    _DAT_1f800320 = _DAT_1f800320 & 0xfeffffff | 0x50000000;
    _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0xe;
    _DAT_1f800332 = 0xe8;
    _DAT_1f800330 = 0x360;
    uVar1 = (undefined1)((uint)*(byte *)(param_1 + 0xc) * 3 >> 2);
    uVar2 = (undefined1)((uint)*(byte *)(param_1 + 0xd) * 3 >> 2);
    uVar3 = (undefined1)((uint)*(byte *)(param_1 + 0xe) * 3 >> 2);
    _DAT_1f800348 = CONCAT12(uVar3,CONCAT11(uVar2,uVar1));
    _DAT_1f800348 = CONCAT13(DAT_1f80034b,_DAT_1f800348) | 0x2000000;
    DAT_1f800334_3 = SUB41(uVar4,3);
    _DAT_1f800334 = CONCAT12(uVar3,CONCAT11(uVar2,uVar1));
    FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
    _DAT_1f800348 = CONCAT13(DAT_1f80034b,*(undefined3 *)(param_1 + 0xc));
    _DAT_1f800334 = *(undefined4 *)(iVar8 + 0xc);
    _DAT_1f800320 = _DAT_1f800320 & 0x8fffffff | 0x60000000;
    _DAT_1f80039c = 0;
    uVar6 = (uint)*(byte *)(param_1 + 0x67);
    _DAT_1f800330 = _DAT_1f800330 + 0x10;
    _DAT_1f80032c = 0x1f;
    _DAT_1f800324 = *(short *)(iVar8 + 0x30) + *(short *)(param_1 + 0x30);
    _DAT_1f800326 = *(short *)(iVar8 + 0x32) + *(short *)(param_1 + 0x32);
    _DAT_1f800328 = *(undefined4 *)(param_1 + 0x3c);
    _DAT_1f80032e = *(short *)(param_1 + 0x5e);
    iVar5 = uVar6 * 0x40;
    if (*(byte *)(param_1 + 0x68) < 0x14) {
      if (((&DAT_800eb4ac)[iVar5] & 0x80) != 0) {
        _DAT_1f800330 = CONCAT22(_DAT_1f800332 + 1,_DAT_1f800330);
      }
      FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
      _DAT_1f800330 = CONCAT22(0xe8,_DAT_1f800330);
      _DAT_1f800324 = _DAT_1f800324 + 0x33;
      if (((&DAT_800eb4ac)[iVar5] & 0x40) != 0) {
        _DAT_1f800330 = CONCAT22(0xe9,_DAT_1f800330);
      }
      DAT_1f80032e = DAT_1f80032e + ' ';
      FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
      _DAT_1f800330 = CONCAT22(0xe8,_DAT_1f800330);
      iVar7 = (int)(short)(&DAT_800eb4a2)[uVar6 * 0x20] + (int)*(short *)(&DAT_800eb4a6 + iVar5);
      if (9999 < iVar7) {
        iVar7 = 9999;
      }
      FUN_80035ce8(iVar7,4,acStack_38);
      iVar7 = (int)(short)(&DAT_800eb4a4)[uVar6 * 0x20] + (int)*(short *)(&DAT_800eb4a8 + iVar5);
      if (9999 < iVar7) {
        iVar7 = 9999;
      }
      FUN_80035ce8(iVar7,4,acStack_30);
      DAT_1f80032f = (DAT_1f80032f & 0x80) + 0x10;
      _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 0x30;
      _DAT_1f800328 = 0xd0006;
      _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0xbd;
      if (((&DAT_800eb4ac)[iVar5] & 0x80) != 0) {
        _DAT_1f800330 = CONCAT22(0xe9,_DAT_1f800330);
      }
      iVar7 = 3;
      do {
        DAT_1f80032e = acStack_38[iVar7] * '\x06' + '\x10';
        FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
        iVar7 = iVar7 + -1;
        _DAT_1f800324 = _DAT_1f800324 + 6;
      } while (-1 < iVar7);
      _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 99;
      _DAT_1f800330 = CONCAT22(0xe8,_DAT_1f800330);
      _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0xbd;
      if (((&DAT_800eb4ac)[iVar5] & 0x40) != 0) {
        _DAT_1f800330 = CONCAT22(0xe9,_DAT_1f800330);
      }
      iVar7 = 3;
      do {
        DAT_1f80032e = acStack_30[iVar7] * '\x06' + '\x10';
        FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
        iVar7 = iVar7 + -1;
        _DAT_1f800324 = _DAT_1f800324 + 6;
      } while (-1 < iVar7);
      _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 0x77;
      _DAT_1f800328 = 0x90009;
      _DAT_1f80032e = (ushort)DAT_1f80032f << 8;
      _DAT_1f800330 = 0xe80340;
      _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0x20;
      iVar7 = 0;
      if ((&DAT_800eb4aa)[iVar5] != '\0') {
        do {
          FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
          _DAT_1f800324 = _DAT_1f800324 + -9;
          iVar7 = iVar7 + 1;
        } while (iVar7 < (int)(uint)(byte)(&DAT_800eb4aa)[iVar5]);
      }
    }
    else {
      FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
    }
    _DAT_1f800324 = *(short *)(iVar8 + 0x30) + 0x6e;
    _DAT_1f800328 = 0x100010;
    _DAT_1f800326 = *(short *)(iVar8 + 0x32) + 0xd;
    _DAT_1f80032e = CONCAT11(DAT_1f80032f,(&DAT_800eb4ab)[iVar5] << 4) & 0x80ff;
    _DAT_1f800330 =
         CONCAT22(0xef,*(short *)(iVar8 + 0x40) + (ushort)(byte)((&DAT_800eb4ab)[iVar5] << 4));
    FUN_800424b8(&DAT_1f800320,0x1f800344,param_2,uVar9,&DAT_1f800398);
  }
  return;
}

