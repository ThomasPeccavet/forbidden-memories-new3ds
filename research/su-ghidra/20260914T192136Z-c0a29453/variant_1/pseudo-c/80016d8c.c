/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80016d8c(int param_1)

{
  int iVar1;
  
  FUN_80016cf8(&DAT_800eb278);
  FUN_80016cf8(&DAT_800eb298);
  iVar1 = *(int *)(param_1 + 0x50);
  _DAT_1f800330 = 0xe10280;
  _DAT_1f800320 = 0x9000000;
  _DAT_1f80032c = 0x1e;
  _DAT_1f80032e = 0x5800;
  _DAT_1f800328 = 0x80008;
  _DAT_1f800334 = 0x808080;
  if (DAT_8009c504 == '\0') {
    _DAT_1f800334 = 0x404040;
  }
  _DAT_1f800324 = *(short *)(iVar1 + 0x30) + -3;
  _DAT_1f800326 = *(short *)(iVar1 + 0x32) + -0xd;
  FUN_80016c48(iVar1,&DAT_1f800320,(int)DAT_800eb2aa,4);
  _DAT_1f800324 = *(short *)(iVar1 + 0x30) + 0xe;
  _DAT_1f800326 = *(short *)(iVar1 + 0x32) + -5;
  FUN_80016c48(iVar1,&DAT_1f800320,0x28 - DAT_800eb2b0,2);
  _DAT_1f800334 = 0x808080;
  if (DAT_8009c504 != '\0') {
    _DAT_1f800334 = 0x404040;
  }
  _DAT_1f800324 = *(short *)(iVar1 + 0x30) + -3;
  _DAT_1f800326 = *(short *)(iVar1 + 0x32) + 0xd;
  FUN_80016c48(iVar1,&DAT_1f800320,(int)DAT_800eb28a,4);
  _DAT_1f800324 = *(short *)(iVar1 + 0x30) + 0xe;
  _DAT_1f800326 = *(short *)(iVar1 + 0x32) + 5;
  FUN_80016c48(iVar1,&DAT_1f800320,0x28 - DAT_800eb290,2);
  return;
}

