/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8003d500(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  iVar3 = 0;
  _DAT_1f800000 = *(undefined4 *)(param_1 + 4);
  _DAT_1f800008 = 0x200020;
  _DAT_1f800014 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f80000c = 0xb;
  _DAT_1f800012 = 0xfc;
  uVar1 = *(undefined2 *)(param_1 + 0x14);
  _DAT_1f80000e = 0x3030;
  do {
    iVar2 = 0;
    _DAT_1f800004 = (short)(uVar4 << 5);
    DAT_1f80000e = 0x30;
    _DAT_1f800006 = (undefined2)iVar3;
    _DAT_1f800010 = 0x340;
    do {
      FUN_80084978(0x1f800000,param_2,uVar1);
      iVar2 = iVar2 + 0x40;
      _DAT_1f800004 = _DAT_1f800004 + 0x40;
    } while (iVar2 < 0x140);
    iVar2 = 0;
    _DAT_1f800004 = (short)((uVar4 ^ 1) << 5);
    _DAT_1f80000e = CONCAT11(DAT_1f80000f,0x50);
    _DAT_1f800010 = 0x350;
    do {
      FUN_80084978(0x1f800000,param_2,uVar1);
      iVar2 = iVar2 + 0x40;
      _DAT_1f800004 = _DAT_1f800004 + 0x40;
    } while (iVar2 < 0x140);
    iVar3 = iVar3 + 0x20;
    uVar4 = uVar4 ^ 1;
  } while (iVar3 < 0x100);
  return;
}

