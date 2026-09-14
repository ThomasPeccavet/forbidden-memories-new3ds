/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007c548(byte param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_8007a668();
  DAT_80094cb4 = param_1;
  if (param_2 == 0) {
    DAT_80094cbc = (undefined1 *)0x0;
  }
  else {
    FUN_8007d2bc(&DAT_80094cb5,param_2);
    DAT_80094cbc = &DAT_80094cb5;
  }
  if (*(int *)(&DAT_80094d04 + (uint)DAT_80094cb4 * 4) == 0) {
    DAT_80094cf4 = 0x1e;
  }
  else {
    DAT_80094cf4 = *(int *)(&DAT_80094d04 + (uint)DAT_80094cb4 * 4) * 0x3c;
  }
  DAT_80094cf8 = 0;
  if (DAT_80094cb4 == 8) {
    if (DAT_80094ce7 != 1) {
      DAT_80094cb4 = 1;
    }
  }
  else if (DAT_80094cb4 < 9) {
    if ((DAT_80094cb4 == 7) && (DAT_80094ce7 == 1)) {
      DAT_80094cb4 = DAT_80094ce7;
    }
  }
  else if (((DAT_80094cb4 == 9) && (DAT_80094d00 != '\0')) && (DAT_80094d01 == 9)) {
    DAT_80094cb4 = 1;
  }
  if (DAT_80094cb4 == 1) {
    DAT_80094cbc = (undefined1 *)0x0;
    if (DAT_80094d08 == 0) {
      DAT_80094cf4 = 0x1e;
    }
    else {
      DAT_80094cf4 = DAT_80094d08 * 0x3c;
    }
  }
  iVar1 = FUN_8007a1d4(DAT_80094cb4,DAT_80094cbc,0,1);
  uVar2 = 0;
  if (iVar1 == 0) {
    uVar2 = 1;
    DAT_80094cdc = DAT_80094cb4;
    if (DAT_80094cb4 != 1) {
      DAT_80094d01 = DAT_80094cb4;
      DAT_80094d00 = '\0';
      uVar2 = 1;
    }
  }
  else {
    DAT_80094cf8 = 0;
    DAT_80094cf4 = 0;
  }
  return uVar2;
}

