/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80015400(void)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  
  FUN_8001522c(&DAT_800eb248);
  uVar1 = DAT_8009c85c;
  if (((DAT_800eb24e & 0x80) != 0) || ((DAT_8009c4b8 != '\0' && (DAT_800eb24c != 0xff)))) {
    _DAT_1f8003c0 = 0x60000000;
    _DAT_1f8003c8 = 0x1000140;
    _DAT_1f8003c4 = 0;
    if ((DAT_800eb24e & 1) != 0) {
      _DAT_1f8003c8 = 0x80140;
      iVar3 = 0;
      do {
        DAT_1f8003cc = -1 - (&DAT_800eb252)[iVar3];
        DAT_1f8003cd = DAT_1f8003cc;
        DAT_1f8003ce = DAT_1f8003cc;
        FUN_800841c8(&DAT_1f8003c0,uVar1,4);
        iVar3 = iVar3 + 1;
        _DAT_1f8003c4 = CONCAT22(_DAT_1f8003c6 + 8,_DAT_1f8003c4);
      } while (iVar3 < 0x20);
      if ((DAT_800eb24e & 2) == 0) {
        return;
      }
    }
    cVar2 = '\x04';
    if (((DAT_800eb24e & 2) != 0) && (cVar2 = DAT_8009c4c4, DAT_8009c4c4 == '\0')) {
      cVar2 = '?';
    }
    DAT_1f8003cc = -1 - DAT_800eb24c;
    DAT_1f8003cd = DAT_1f8003cc;
    DAT_1f8003ce = DAT_1f8003cc;
    if ((DAT_800eb24e & 0x10) != 0) {
      iVar3 = (uint)(byte)DAT_800eb248 - (uint)DAT_800eb24c;
      _DAT_1f8003c0 = 0x50000000;
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      DAT_1f8003cc = (char)iVar3;
      iVar3 = (uint)DAT_800eb248._1_1_ - (uint)DAT_800eb24c;
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      DAT_1f8003cd = (char)iVar3;
      iVar3 = (uint)DAT_800eb248._2_1_ - (uint)DAT_800eb24c;
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      DAT_1f8003ce = (char)iVar3;
    }
    FUN_800841c8(&DAT_1f8003c0,uVar1,cVar2);
  }
  return;
}

