/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8008f368(void)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 unaff_retaddr;
  
  bVar1 = DAT_1f801040;
  uVar2 = unaff_retaddr;
  if ((DAT_8009b23c != 0) && (uVar2 = unaff_retaddr, (_DAT_1f801070 & 0x80) != 0)) {
    if (DAT_8009b230 == 0) {
      DAT_1f801040 = 0;
      *DAT_8009b234 = bVar1;
    }
    else {
      bVar1 = *DAT_8009b234;
      DAT_1f801040 = bVar1;
    }
    DAT_8009b234 = DAT_8009b234 + 1;
    _DAT_1f801070 = 0xffffff7f;
    _DAT_1f80104a = _DAT_1f80104a | 0x10;
    *DAT_8009b238 = *DAT_8009b238 ^ bVar1;
    DAT_8009b23c = DAT_8009b23c + -1;
    DAT_8009b1ec = DAT_8009b1ec + 1;
    uVar2 = DAT_8009b22c;
    if (DAT_8009b240 == 0) {
                    /* WARNING: Could not recover jumptable at 0x8008f4d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      Status = Status & 0xfffffff0 | (Status & 0x3c) >> 2;
      (**(code **)(*_DAT_00000108 + 0x88))();
      return;
    }
  }
  DAT_8009b22c = uVar2;
  return;
}

