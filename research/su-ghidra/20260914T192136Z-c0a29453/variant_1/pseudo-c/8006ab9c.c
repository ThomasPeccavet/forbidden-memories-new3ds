/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8006ab9c(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined2 uVar2;
  byte *pbVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  byte abStack_38 [8];
  byte abStack_30 [8];
  
  pbVar3 = &DAT_80092214;
  uVar6 = 0;
  bVar1 = *(byte *)(param_1 + 0x6a);
  uVar2 = *(undefined2 *)(param_1 + 0x14);
  _DAT_1f800320 = *(undefined4 *)(param_1 + 4);
  _DAT_1f80032c = 0xb;
  _DAT_1f800328 = 0x100010;
  _DAT_1f800324 = *(short *)(param_1 + 0x30) + 0x22;
  _DAT_1f800332 = 0xfb;
  _DAT_1f800326 = *(short *)(param_1 + 0x32) + -0x18;
  do {
    _DAT_1f800334 = 0x202020;
    if (uVar6 == *(byte *)(param_1 + 0x69)) {
      _DAT_1f800334 = 0x808080;
    }
    DAT_1f80032e = (*pbVar3 & 0xf) * '\b' + -0x80;
    DAT_1f80032f = *pbVar3 & 0xf0;
    uVar6 = uVar6 + 1;
    _DAT_1f800330 = (pbVar3[1] & 0xf0) + 0x280;
    FUN_80084978(&DAT_1f800320,param_2,uVar2);
    _DAT_1f800324 = _DAT_1f800324 + 0x14;
    pbVar3 = pbVar3 + 2;
  } while ((int)uVar6 < 6);
  if ((&DAT_801a8008)[(uint)bVar1 * 0xe] != 0) {
    puVar8 = (ushort *)(&DAT_801a800a + (uint)bVar1 * 0x1c);
    iVar7 = 0;
    _DAT_1f800320 = *(undefined4 *)(param_1 + 4);
    _DAT_1f800328 = 0x80008;
    _DAT_1f800324 = *(short *)(param_1 + 0x30) + 0x24;
    _DAT_1f800326 = *(short *)(param_1 + 0x32);
    _DAT_1f80032c = 10;
    _DAT_1f800330 = 0x280;
    _DAT_1f800332 = 0xc0;
    DAT_1f80032e = -0x80;
    DAT_1f80032f = 0x40;
    do {
      if (((*puVar8 & 0xfff) != 0) &&
         (puVar5 = &DAT_801d4244 + ((*puVar8 & 0xfff) - 1), ((int)*puVar5 >> 0x1a & 0x1fU) < 0x14))
      {
        _DAT_1f800334 = 0x808080;
        _DAT_1f800324 = *(short *)(param_1 + 0x30) + 0x24;
        if ((*puVar8 & 0x8000) != 0) {
          _DAT_1f800334 = 0x404040;
        }
        iVar4 = 3;
        FUN_80035ce8((*puVar5 & 0x1ff) * 10,4,abStack_38);
        FUN_80035ce8(((int)*puVar5 >> 9 & 0x1ffU) * 10,4,abStack_30);
        do {
          if (abStack_38[iVar4] < 10) {
            DAT_1f80032e = abStack_38[iVar4] * '\b' + -0x80;
            FUN_80084978(&DAT_1f800320,param_2,uVar2);
          }
          if (abStack_30[iVar4] < 10) {
            _DAT_1f800326 = _DAT_1f800326 + 8;
            DAT_1f80032e = abStack_30[iVar4] * '\b' + -0x80;
            FUN_80084978(&DAT_1f800320,param_2,uVar2);
            _DAT_1f800326 = _DAT_1f800326 + -8;
          }
          iVar4 = iVar4 + -1;
          _DAT_1f800324 = _DAT_1f800324 + 8;
        } while (-1 < iVar4);
      }
      iVar7 = iVar7 + 1;
      _DAT_1f800326 = _DAT_1f800326 + 0x16;
      puVar8 = puVar8 + 1;
    } while (iVar7 < 8);
  }
  return;
}

