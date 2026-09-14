/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80015e10(int *param_1,int param_2,int param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 in_zero;
  undefined4 extraout_at;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  char cVar5;
  short sVar6;
  ushort uVar7;
  int iVar8;
  
  iVar8 = *param_1;
  if ((*(ushort *)(iVar8 + 8) & 0x40) != 0) {
    _DAT_1f800380 = 0;
    _DAT_1f800382 = 0x1000;
    _DAT_1f800384 = 0;
    *param_4 = *(undefined4 *)(iVar8 + 0xc);
    sVar6 = (ushort)*(byte *)(iVar8 + 0x21) * 0x10;
    _DAT_1f8003a4 = CONCAT22(DAT_1f8003a4_2,(ushort)*(byte *)(iVar8 + 0x22) << 4);
    if ('\x0e' < (char)param_1[6]) {
      sVar6 = sVar6 + 0x800;
    }
    _DAT_1f8003a0 = CONCAT22(sVar6,(ushort)*(byte *)(iVar8 + 0x20) << 4);
    _DAT_1f8002d4 = (int)*(short *)(iVar8 + 0x30);
    _DAT_1f8002d8 = (int)*(short *)(iVar8 + 0x32);
    _DAT_1f8002dc = (int)*(short *)(iVar8 + 0x34);
    iVar4 = _DAT_1f8002d8 + 0xff;
    if (iVar4 < 0) {
      iVar4 = 0;
    }
    uVar2 = (undefined1)iVar4;
    *(undefined1 *)(param_3 + 6) = uVar2;
    *(undefined1 *)(param_3 + 5) = uVar2;
    *(undefined1 *)(param_3 + 4) = uVar2;
    FUN_80088bd8(&DAT_1f8003a0,0x1f8002c0);
    _DAT_1f800320 = (int)*(short *)(iVar8 + 0x44);
    _DAT_1f800324 = 0x1000;
    _DAT_1f800328 = (int)*(short *)(iVar8 + 0x46);
    FUN_800875f8(0x1f8002c0,&DAT_1f800320);
    _DAT_1f800310 = 0xffe7;
    _DAT_1f800300 = 0xffe7;
    _DAT_1f800318 = 0x1a;
    _DAT_1f800308 = 0x1a;
    _DAT_1f80030c = 0x1d;
    _DAT_1f800304 = 0x1d;
    _DAT_1f80031c = 0xffe2;
    _DAT_1f800314 = 0xffe2;
    _DAT_1f80031a = 0;
    _DAT_1f800312 = 0;
    _DAT_1f80030a = 0;
    _DAT_1f800302 = 0;
    FUN_80085558(0x1f8002c0);
    FUN_80089c48(&DAT_1f800300,&DAT_1f8003a0,&DAT_1f8003e0);
    FUN_80089c48(&DAT_1f800308,&DAT_1f8003a8,&DAT_1f8003e0);
    FUN_80089c48(&DAT_1f800310,&DAT_1f8003b0,&DAT_1f8003e0);
    FUN_80089c48(&DAT_1f800318,&DAT_1f8003b8,&DAT_1f8003e0);
    _DAT_1f8003c0 = _DAT_1f8003a0;
    _DAT_1f8003c4 = _DAT_1f8003a4;
    _DAT_1f8003c8 = _DAT_1f8003a8;
    _DAT_1f8003cc = _DAT_1f8003ac;
    _DAT_1f8003d0 = _DAT_1f8003b0;
    _DAT_1f8003d4 = _DAT_1f8003b4;
    _DAT_1f8003d8 = _DAT_1f8003b8;
    _DAT_1f8003dc = _DAT_1f8003bc;
    FUN_80085588(0x1f8002c0);
    FUN_80085558(&DAT_800ff4d0);
    _DAT_1f8003f0 =
         FUN_80087bf8(&DAT_1f8003a0,&DAT_1f800380,param_4,param_2 + 8,param_2 + 4,&DAT_1f8003e0);
    _DAT_1f8003f4 =
         FUN_80087bf8(&DAT_1f8003a8,&DAT_1f800380,param_4,param_2 + 0x14,param_2 + 0x10,
                      &DAT_1f8003e4);
    _DAT_1f8003f8 =
         FUN_80087bf8(&DAT_1f8003b0,&DAT_1f800380,param_4,param_2 + 0x20,param_2 + 0x1c,
                      &DAT_1f8003e8);
    _DAT_1f8003fc =
         FUN_80087bf8(&DAT_1f8003b8,&DAT_1f800380,param_4,param_2 + 0x2c,param_2 + 0x28,
                      &DAT_1f8003ec);
    if (-1 < (int)(_DAT_1f8003e0 | _DAT_1f8003e4 | _DAT_1f8003e8 | _DAT_1f8003ec)) {
      uVar2 = *(undefined1 *)(iVar8 + 0x5c);
      *(undefined1 *)(param_2 + 0x24) = uVar2;
      *(undefined1 *)(param_2 + 0xc) = uVar2;
      uVar2 = *(undefined1 *)(iVar8 + 0x5d);
      *(undefined1 *)(param_2 + 0x19) = uVar2;
      *(undefined1 *)(param_2 + 0xd) = uVar2;
      iVar4 = FUN_80087928(*(undefined4 *)(param_2 + 8),*(undefined4 *)(param_2 + 0x14),
                           *(undefined4 *)(param_2 + 0x20));
      if (iVar4 < 1) {
        *(undefined1 *)(param_2 + 0x24) = 0x38;
        *(undefined1 *)(param_2 + 0xc) = 0x38;
        *(undefined1 *)(param_2 + 0x19) = 0x80;
        *(undefined1 *)(param_2 + 0xd) = 0x80;
      }
      cVar3 = *(char *)(param_2 + 0xc) + '4';
      cVar5 = *(char *)(param_2 + 0xd) + '<';
      *(char *)(param_2 + 0x30) = cVar3;
      *(char *)(param_2 + 0x18) = cVar3;
      *(char *)(param_2 + 0x31) = cVar5;
      *(char *)(param_2 + 0x25) = cVar5;
      sVar6 = *(short *)(iVar8 + 0x42);
      *(undefined1 *)(param_2 + 3) = 0xc;
      *(undefined1 *)(param_2 + 7) = 0x3c;
      *(ushort *)(param_2 + 0xe) = (sVar6 + 0xe1) * 0x40 | 0x28;
      FUN_80082da8(param_2,0);
      uVar7 = *(ushort *)(param_2 + 0x1a) & 0xff9f;
      *(ushort *)(param_2 + 0x1a) = uVar7;
      *(ushort *)(param_2 + 0x1a) =
           uVar7 | (ushort)((uint)*(undefined4 *)(iVar8 + 4) >> 0x17) & 0x60;
      if ((*(uint *)(iVar8 + 4) & 0x40000000) != 0) {
        FUN_80082da8(param_2,1);
        *(undefined1 *)(param_3 + 4) = *(undefined1 *)(iVar8 + 0xc);
        *(undefined1 *)(param_3 + 5) = *(undefined1 *)(iVar8 + 0xd);
        *(undefined1 *)(param_3 + 6) = *(undefined1 *)(iVar8 + 0xe);
      }
      iVar8 = _DAT_1f8003f0 + _DAT_1f8003f4 + _DAT_1f8003f8 + _DAT_1f8003fc;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 3;
      }
      _DAT_1f8003e0 = iVar8 >> 4;
      FUN_800842a8(param_2,DAT_8009c860,_DAT_1f8003e0 & 0xffff);
      _DAT_1f8003d8 = _DAT_1f8003d8 & 0xffff;
      _DAT_1f8003d0 = _DAT_1f8003d0 & 0xffff;
      _DAT_1f8003c8 = _DAT_1f8003c8 & 0xffff;
      _DAT_1f8003c0 = _DAT_1f8003c0 & 0xffff;
      setCopReg(2,in_zero,_DAT_1f8003c0);
      setCopReg(2,extraout_at,_DAT_1f8003c4);
      copFunction(2,0x180001);
      uVar1 = getCopReg(2,0xe);
      *(undefined4 *)(param_3 + 8) = uVar1;
      setCopReg(2,in_zero,_DAT_1f8003c8);
      setCopReg(2,extraout_at,_DAT_1f8003cc);
      copFunction(2,0x180001);
      uVar1 = getCopReg(2,0xe);
      *(undefined4 *)(param_3 + 0x10) = uVar1;
      setCopReg(2,in_zero,_DAT_1f8003d0);
      setCopReg(2,extraout_at,_DAT_1f8003d4);
      copFunction(2,0x180001);
      uVar1 = getCopReg(2,0xe);
      *(undefined4 *)(param_3 + 0x18) = uVar1;
      setCopReg(2,in_zero,_DAT_1f8003d8);
      setCopReg(2,extraout_at,_DAT_1f8003dc);
      copFunction(2,0x180001);
      uVar1 = getCopReg(2,0xe);
      *(undefined4 *)(param_3 + 0x20) = uVar1;
      FUN_800842a8(param_3,DAT_8009c860,0xfff);
    }
  }
  return;
}

