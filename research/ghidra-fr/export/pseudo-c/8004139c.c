/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8004139c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  sVar1 = DAT_800f11ca;
joined_r0x800413dc:
  do {
    iVar2 = (int)sVar1;
    if (iVar2 < 0) {
      return;
    }
    iVar3 = iVar2 * 0x70;
    sVar1 = *(short *)(&DAT_800f1212 + iVar3);
    if (*(code **)(&DAT_800f1234 + iVar3) != (code *)0x0) {
      (**(code **)(&DAT_800f1234 + iVar3))(&DAT_800f1210 + iVar3);
    }
  } while (((&DAT_800f1218)[iVar2 * 0x38] & 0xc0) != 0xc0);
  _DAT_1f80034c = *(undefined4 *)(&DAT_800f1238 + iVar3);
  uVar4 = *(uint *)(&DAT_800f1214 + iVar3);
  _DAT_1f800358 = *(undefined4 *)(&DAT_800f1244 + iVar3);
  _DAT_1f800364 = *(undefined4 *)(&DAT_800f1250 + iVar3);
  _DAT_1f800370 = *(undefined4 *)(&DAT_800f125c + iVar3);
  _DAT_1f800354 = *(undefined4 *)(&DAT_800f1248 + iVar3);
  _DAT_1f800360 = *(undefined4 *)(&DAT_800f1254 + iVar3);
  _DAT_1f80036c = *(undefined4 *)(&DAT_800f1260 + iVar3);
  _DAT_1f800350 = *(undefined2 *)(&DAT_800f1240 + iVar3);
  _DAT_1f80035c = *(undefined2 *)(&DAT_800f124c + iVar3);
  _DAT_1f800368 = *(undefined2 *)(&DAT_800f1258 + iVar3);
  _DAT_1f800374 = *(undefined2 *)(&DAT_800f1264 + iVar3);
  DAT_1f800347 = 0xc;
  _DAT_1f800348 = (undefined3)*(undefined4 *)(&DAT_800f123c + iVar3);
  _DAT_1f800348 = CONCAT13(0x3c,_DAT_1f800348);
  if (((&DAT_800f1218)[iVar2 * 0x38] & 8) == 0) {
    _DAT_1f800366 = (short)((uint)_DAT_1f800364 >> 0x10);
    _DAT_1f80034e = (short)((uint)_DAT_1f80034c >> 0x10);
    _DAT_1f800372 = (short)((uint)_DAT_1f800370 >> 0x10);
    _DAT_1f80035a = (short)((uint)_DAT_1f800358 >> 0x10);
    _DAT_1f80034c = CONCAT22(_DAT_1f80034e - DAT_8009c4c2,_DAT_1f80034c - DAT_8009c4c0);
    _DAT_1f800358 = CONCAT22(_DAT_1f80035a - DAT_8009c4c2,_DAT_1f800358 - DAT_8009c4c0);
    _DAT_1f800364 = CONCAT22(_DAT_1f800366 - DAT_8009c4c2,_DAT_1f800364 - DAT_8009c4c0);
    _DAT_1f800370 = CONCAT22(_DAT_1f800372 - DAT_8009c4c2,_DAT_1f800370 - DAT_8009c4c0);
  }
  if (((&DAT_800f1218)[iVar2 * 0x38] & 4) != 0) goto code_r0x8004155c;
  goto LAB_800415a0;
code_r0x8004155c:
  iVar2 = FUN_800421ac(*(undefined4 *)(&DAT_800f1230 + iVar3),
                       (int)_DAT_1f80034c + (int)*(short *)(&DAT_800f1228 + iVar3),
                       (int)_DAT_1f80034e + (int)*(short *)(&DAT_800f122a + iVar3),&DAT_1f800398);
  if (0 < iVar2) {
    uVar4 = uVar4 | 0x4000000;
LAB_800415a0:
    FUN_800424b8(uVar4,0x1f800344,
                 *(undefined4 *)(&DAT_8009c858 + (uint)(byte)(&DAT_800f1227)[iVar3] * 4),
                 *(ushort *)(&DAT_800f1224 + iVar3) | 0x50000,&DAT_1f800398);
    if ((&DAT_800f1282)[iVar3] != '\0') {
      _DAT_1f80034c = *(undefined4 *)(&DAT_800f1268 + iVar3);
      _DAT_1f800358 = *(undefined4 *)(&DAT_800f1274 + iVar3);
      _DAT_1f800354 = *(undefined4 *)(&DAT_800f1278 + iVar3);
      _DAT_1f800350 = *(undefined2 *)(&DAT_800f1270 + iVar3);
      _DAT_1f80035c = *(undefined2 *)(&DAT_800f127c + iVar3);
      DAT_1f800347 = 0xc;
      _DAT_1f800348 = (undefined3)*(undefined4 *)(&DAT_800f126c + iVar3);
      _DAT_1f800348 = CONCAT13(0x3c,_DAT_1f800348);
      FUN_800424b8(uVar4,0x1f800344,
                   *(undefined4 *)(&DAT_8009c858 + (uint)(byte)(&DAT_800f1227)[iVar3] * 4),
                   *(ushort *)(&DAT_800f1224 + iVar3) | 0x50000,&DAT_1f800398);
    }
  }
  goto joined_r0x800413dc;
}

