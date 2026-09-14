/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80031b58(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  short *psVar7;
  int iVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  
  _DAT_1f800020 = *(undefined4 *)(param_1 + 4);
  _DAT_1f80002c = 10;
  _DAT_1f80006c = 0xb;
  _DAT_1f800034 = 0x808080;
  _DAT_1f800028 = 0x80008;
  _DAT_1f800068 = 0x100010;
  _DAT_1f800030 = 0x280;
  _DAT_1f800032 = 0xc0;
  uVar5 = (uint)*(byte *)(param_1 + 0x67);
  iVar4 = DAT_8009c684 + uVar5 * 0x2d4c + 4;
  sVar3 = *(short *)(iVar4 + 0x2d3c);
  _DAT_1f800066 = (*(short *)(param_1 + 0x32) - DAT_8009c4c2) + 0x11;
  sVar9 = *(short *)(param_1 + 0x30) - DAT_8009c4c0;
  if (uVar5 == 0) {
    _DAT_1f800064 = sVar9 + 0x88;
    uVar1 = *(undefined1 *)(iVar4 + 0x2d45);
    puVar6 = &DAT_80092214;
  }
  else {
    _DAT_1f800064 = sVar9 + 0x6a;
    uVar1 = *(undefined1 *)(iVar4 + 0x2d45);
    puVar6 = &DAT_80092214 + uVar5 * 0x10;
  }
  iVar11 = 0;
  _DAT_1f800060 = _DAT_1f800020;
  FUN_80031a68(&DAT_1f800060,param_2,puVar6,uVar1);
  sVar10 = 0x2c;
  psVar7 = (short *)(iVar4 + sVar3 * 0x10 + 6);
  _DAT_1f800070 = 0xc50280;
  _DAT_1f800068 = 0x100008;
  DAT_1f80006f = 0;
  _DAT_1f80006c = 10;
  do {
    _DAT_1f800024 = sVar9 + 4;
    _DAT_1f800026 = sVar10;
    _DAT_1f800064 = _DAT_1f800024;
    _DAT_1f800066 = sVar10;
    if (*(char *)((int)psVar7 + 7) != '\0') {
      _DAT_1f800034 = 0x808080;
      _DAT_1f800074 = 0x808080;
      iVar8 = (int)psVar7[-1];
      if ((*(byte *)((int)psVar7 + 7) & 0x80) != 0) {
        _DAT_1f800034 = 0x404040;
        _DAT_1f800074 = 0x404040;
      }
      if (uVar5 == 0) {
        _DAT_1f800070 = CONCAT22(0xc5,_DAT_1f800070);
        if (*(char *)(DAT_8009c684 + iVar8 + 0x606a) != '\0') {
          _DAT_1f800028 = 0x18;
          _DAT_1f80002e = 0x68e8;
          _DAT_1f80002c = 0xb;
          _DAT_1f800030 = 0x310;
          _DAT_1f800032 = 0xfa;
          _DAT_1f800026 = sVar10 + 10;
          FUN_80084978(&DAT_1f800020,param_2,0);
          _DAT_1f800030 = 0x280;
          _DAT_1f80002c = 10;
          _DAT_1f800028 = CONCAT22(_DAT_1f80002a,8);
          _DAT_1f800032 = 0xc0;
          _DAT_1f800070 = CONCAT22(0xc1,_DAT_1f800070);
          _DAT_1f800026 = _DAT_1f800026 + -10;
          _DAT_1f800066 = _DAT_1f800066 + -4;
        }
      }
      else {
        _DAT_1f800070 = CONCAT22(0xc2,_DAT_1f800070);
        _DAT_1f800024 = sVar9 + 0x11;
        _DAT_1f800064 = _DAT_1f800024;
        FUN_80035da0(*(short *)(iVar4 + 0x2d3c) + iVar11 + 1,2,0x1f800000);
        FUN_800319dc(&DAT_1f800060,param_2,0x1f800000,2);
        _DAT_1f800070 = CONCAT22(0xc5,_DAT_1f800070);
        _DAT_1f800024 = _DAT_1f800024 + 4;
        _DAT_1f800064 = _DAT_1f800064 + 4;
      }
      FUN_80035da0(iVar8,3,0x1f800000);
      FUN_800319dc(&DAT_1f800060,param_2,0x1f800000,3);
      _DAT_1f800024 = _DAT_1f800064 + 0x88;
      if (*(byte *)(psVar7 + 2) < 0x14) {
        _DAT_1f800032 = 199;
        _DAT_1f80002e = 0x40f8;
        FUN_80084978(&DAT_1f800020,param_2,0);
        _DAT_1f80002e = 0x48f8;
        _DAT_1f800026 = _DAT_1f800026 + 8;
        FUN_80084978(&DAT_1f800020,param_2,0);
        _DAT_1f800032 = 0xc0;
        _DAT_1f800024 = _DAT_1f800024 + 8;
        FUN_80035ce8((int)psVar7[1],4,0x1f800000);
        FUN_80031948(&DAT_1f800020,param_2,0x1f800000,4);
        _DAT_1f800024 = _DAT_1f800024 + -0x20;
        _DAT_1f800026 = _DAT_1f800026 + -8;
        FUN_80035ce8((int)*psVar7,4,0x1f800000);
        FUN_80031948(&DAT_1f800020,param_2,0x1f800000,4);
      }
      if (uVar5 == 0) {
        _DAT_1f800024 = sVar9 + 0x107;
        _DAT_1f800032 = 0xc0;
        _DAT_1f800026 = _DAT_1f800026 + 8;
        FUN_80035ce8(*(undefined1 *)(DAT_8009c684 + iVar8 + 0x5d97),3,0x1f800000);
        FUN_80031948(&DAT_1f800020,param_2,0x1f800000,3);
        bVar2 = *(byte *)(DAT_8009c684 + iVar8 + 0x5ac4);
        if ((2 < bVar2) || ((iVar8 - 0x11U < 5 && (bVar2 != 0)))) {
          _DAT_1f800034 = 0x2020ff;
        }
        _DAT_1f800024 = sVar9 + 0x122;
        FUN_80035ce8(bVar2,2,0x1f800000);
        FUN_80031948(&DAT_1f800020,param_2,0x1f800000,2);
        _DAT_1f800034 = 0x808080;
        _DAT_1f800026 = _DAT_1f800026 + -8;
      }
    }
    psVar7 = psVar7 + 8;
    iVar11 = iVar11 + 1;
    sVar10 = sVar10 + 0x16;
  } while (iVar11 < 9);
  return;
}

