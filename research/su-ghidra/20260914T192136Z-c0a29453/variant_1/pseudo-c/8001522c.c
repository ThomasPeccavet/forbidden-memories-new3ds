/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8001522c(undefined1 *param_1)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if ((DAT_800eb24e & 0x80) != 0) {
    if ((DAT_8009c4b8 & 0x80) == 0) {
      FUN_80015c18();
    }
    uVar4 = (uint)(byte)param_1[4];
    uVar3 = (uint)(byte)param_1[5];
    if (uVar4 == uVar3) {
      bVar2 = DAT_800eb24e & 0x7f;
      DAT_800eb24e = DAT_800eb24e & 0x79;
      if (uVar4 == 0xff) {
        FUN_80015c18();
        DAT_8009c4c4 = 0;
        DAT_8009c4c5 = 0;
        DAT_8009c4bb = DAT_8009c4be;
        DAT_8009c4ba = DAT_8009c4bd;
        DAT_8009c4b9 = DAT_8009c4bc;
        bVar2 = DAT_800eb24e;
      }
      DAT_800eb24e = bVar2;
      if (uVar4 == 0) {
        if ((DAT_800eb24e & 2) == 0) {
          FUN_80015c28();
        }
        else {
          if ((DAT_800eb24e & 4) == 0) {
            return;
          }
          DAT_8009c4b8 = 0x80;
        }
        DAT_8009c4bb = DAT_8009c4be;
        DAT_8009c4ba = DAT_8009c4bd;
        DAT_8009c4b9 = DAT_8009c4bc;
        if (((DAT_800eb24e & 0x10) != 0) && ((DAT_800eb24e & 0x20) != 0)) {
          DAT_8009c4bb = *param_1;
          DAT_8009c4ba = param_1[1];
          DAT_8009c4b9 = param_1[2];
          DAT_800eb24e = DAT_800eb24e & 0xdf;
          FUN_80015c18();
          DAT_800eb24e = DAT_800eb24e | 0x80;
        }
      }
    }
    else if ((DAT_800eb24e & 1) == 0) {
      if (uVar4 < uVar3) {
        iVar5 = uVar4 + (uint)(byte)param_1[7] * _DAT_8009c43c;
        bVar1 = iVar5 < (int)uVar3;
      }
      else {
        iVar5 = uVar4 - (uint)(byte)param_1[7] * _DAT_8009c43c;
        bVar1 = (int)uVar3 < iVar5;
      }
      DAT_800eb24c = (byte)iVar5;
      if (!bVar1) {
        DAT_800eb24c = param_1[5];
      }
    }
    else {
      FUN_800150f4();
    }
  }
  return;
}

