/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80016418(void)

{
  int *piVar1;
  int iVar2;
  
  FUN_80087858((int)DAT_800f11ee);
  FUN_80087838(0xa0,0x6c);
  FUN_80087818(0,0,0);
  FUN_80086798(0x28a,800,(int)DAT_800f11ee);
  FUN_8005721c(2);
  if ((DAT_8009c68c & 2) != 0) {
    DAT_8009c694 = DAT_8009c694 + 1;
    if (DAT_8009c69c <= DAT_8009c694) {
      DAT_8009c68c = DAT_8009c68c & 0xfffffffc;
    }
    DAT_8009c690 = DAT_8009c698;
  }
  piVar1 = &DAT_801a7b64;
  iVar2 = 0;
  DAT_1f800143 = 9;
  DAT_1f800144 = 0xff;
  DAT_1f800145 = 0xff;
  DAT_1f800146 = 0xff;
  _DAT_1f800156 = 0x5f;
  _DAT_1f80014e = 0x3829;
  DAT_1f800164 = 0xaf;
  DAT_1f800154 = 0xaf;
  DAT_1f800165 = 0x37;
  DAT_1f80015d = 0x37;
  DAT_1f800147 = 0x2e;
  DAT_1f80015c = 0x80;
  DAT_1f80014c = 0x80;
  DAT_1f800155 = 0;
  DAT_1f80014d = 0;
  _DAT_1f80019a = 0x9e;
  _DAT_1f80018e = 0x3868;
  DAT_1f800199 = 0x80;
  DAT_1f80018d = 0x80;
  DAT_1f8001b1 = 0xbc;
  DAT_1f8001a5 = 0xbc;
  _DAT_1f8000c0 = 0x808080;
  do {
    if ((*(ushort *)((int)piVar1 + 0x16) & 0x8000) != 0) {
      if (*piVar1 != 0) {
        if ((*(ushort *)((int)piVar1 + 0x16) & 0x400) == 0) {
          _DAT_1f8000c0 = *(undefined4 *)(*piVar1 + 0xc);
          FUN_80015e10(piVar1,0x1f800180,&DAT_1f800140,&DAT_1f8000c0);
        }
        else {
          FUN_80015d18(piVar1);
        }
      }
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 7;
  } while (iVar2 < 10);
  piVar1 = &DAT_801a7d08;
  iVar2 = 0;
  do {
    if ((*(ushort *)((int)piVar1 + 0x16) & 0x8000) != 0) {
      if (*piVar1 != 0) {
        if ((*(ushort *)((int)piVar1 + 0x16) & 0x400) == 0) {
          _DAT_1f8000c0 = *(undefined4 *)(*piVar1 + 0xc);
          FUN_80015e10(piVar1,0x1f800180,&DAT_1f800140,&DAT_1f8000c0);
        }
        else {
          FUN_80015d18(piVar1);
        }
      }
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 7;
  } while (iVar2 < 10);
  FUN_80087838(0,0);
  return;
}

