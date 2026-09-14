/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800408bc(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  int unaff_gp;
  
  sVar1 = DAT_800f11c2;
joined_r0x800408e4:
  do {
    iVar4 = (int)sVar1;
    if (iVar4 < 0) {
      return;
    }
    iVar9 = iVar4 * 0x70;
    sVar1 = *(short *)(&DAT_800f1212 + iVar9);
    do {
      if (*(code **)(&DAT_800f1234 + iVar9) != (code *)0x0) {
        (**(code **)(&DAT_800f1234 + iVar9))(&DAT_800f1210 + iVar9);
      }
      if (((&DAT_800f1218)[iVar4 * 0x38] & 0xc0) != 0xc0) goto joined_r0x800408e4;
      _DAT_1f800320 = *(uint *)(&DAT_800f1214 + iVar9);
      _DAT_1f800334 = *(undefined4 *)(&DAT_800f121c + iVar9);
      _DAT_1f800324 = *(undefined4 *)(&DAT_800f1240 + iVar9);
      _DAT_1f800328 = *(undefined4 *)(&DAT_800f124c + iVar9);
      _DAT_1f800330 = *(undefined4 *)(&DAT_800f1250 + iVar9);
      _DAT_1f80032e = *(undefined2 *)(&DAT_800f126c + iVar9);
      uVar11 = *(undefined4 *)(&DAT_8009c858 + (uint)(byte)(&DAT_800f1227)[iVar9] * 4);
      _DAT_1f80032c = (ushort)(byte)(&DAT_800f1276)[iVar9];
      uVar10 = *(ushort *)(&DAT_800f1224 + iVar9) | 0x10000;
      if (((&DAT_800f1218)[iVar4 * 0x38] & 8) == 0) {
        _DAT_1f800326 = (short)((uint)_DAT_1f800324 >> 0x10);
        _DAT_1f800324 = CONCAT22(_DAT_1f800326 - DAT_8009c4c2,_DAT_1f800324 - DAT_8009c4c0);
      }
      sVar5 = _DAT_1f800324;
      sVar6 = _DAT_1f800326;
      if (((&DAT_800f1218)[iVar4 * 0x38] & 4) == 0) {
        if ((_DAT_1f800320 & 0x8000000) != 0) goto LAB_80040b04;
        _DAT_1f800340 = (uint)(byte)(&DAT_800f1232)[iVar9] * 0x1680;
        _DAT_1f80033c = *(undefined4 *)(&DAT_800f1254 + iVar9);
        uVar8 = *(undefined4 *)(&DAT_800f1258 + iVar9);
        _DAT_1f800338 = (short)uVar8;
        _DAT_1f80033a = (short)((uint)uVar8 >> 0x10);
        _DAT_1f800324 = CONCAT22(_DAT_1f800326 + _DAT_1f80033a,_DAT_1f800324 + _DAT_1f800338);
        uVar3 = *(ushort *)(&DAT_800f1224 + iVar9);
        uVar10 = 0x30000;
        _DAT_1f800338 = uVar8;
        goto LAB_80040afc;
      }
      sVar2 = *(short *)(&DAT_800f1228 + iVar9);
      *(undefined4 *)(unaff_gp + 0x4fc) = 0;
      iVar7 = FUN_800422c0(&DAT_800f1210 + iVar9,(int)sVar5 + (int)sVar2,
                           (int)sVar6 + (int)*(short *)(&DAT_800f122a + iVar9),&DAT_1f800398);
      if (iVar7 < 1) goto joined_r0x800408e4;
    } while (*(int *)(unaff_gp + 0x4fc) != 0);
    DAT_1f800347 = 9;
    _DAT_1f800348 = CONCAT13(0x2c,(int3)_DAT_1f800334);
    if ((_DAT_1f800320 & 0x40000000) != 0) {
      FUN_80082da8(0x1f800344,1);
    }
    uVar3 = *(ushort *)(&DAT_800f1224 + iVar9);
    uVar10 = 0xf0000;
LAB_80040afc:
    uVar10 = uVar3 | uVar10;
LAB_80040b04:
    FUN_800424b8(&DAT_1f800320,0x1f800344,uVar11,uVar10,&DAT_1f800398);
  } while( true );
}

