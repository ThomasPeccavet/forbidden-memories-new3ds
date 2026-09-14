/* Analysis pseudo-C, not buildable source. */

void FUN_80012f70(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_80015400();
  iVar2 = 0;
  FUN_80041674();
  puVar1 = &DAT_8009c898;
  do {
    if ((code *)*puVar1 != (code *)0x0) {
      (*(code *)*puVar1)();
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < 4);
  if (DAT_8009c450 != (code *)0x0) {
    (*DAT_8009c450)();
  }
  if (((DAT_8009c410 < DAT_8009c44c) || (DAT_8009c420 < DAT_8009c438)) ||
     (_gp_1 = _gp_1 + -1, _gp_1 < 0)) {
    _gp_1 = 0x3c;
    DAT_8009c410 = DAT_8009c44c;
    DAT_8009c420 = DAT_8009c438;
  }
  FUN_80014978(0);
  FUN_800135f0();
  return;
}

