/* Analysis pseudo-C, not buildable source. */

void FUN_8002fbb8(void)

{
  int iVar1;
  
  iVar1 = FUN_8002e650();
  if (iVar1 == 0) {
    DAT_8009c640 = *DAT_8009c624;
    DAT_8009c624 = DAT_8009c624 + 1;
  }
  DAT_8009c640 = DAT_8009c640 - 1;
  if ((int)((uint)DAT_8009c640 << 0x10) < 1) {
    DAT_8009c610 = 0;
  }
  return;
}

