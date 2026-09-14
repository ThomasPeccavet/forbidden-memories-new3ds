/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80012cb8(void)

{
  if ((DAT_8009c440 & 0x8000) == 0) {
    FUN_8007fc64(0);
  }
  do {
  } while ((int)DAT_8009c428 < (int)(uint)DAT_8009c424);
  DAT_8009c454 = (byte)DAT_8009c428;
  if ((DAT_8009c428 & 0xff) != 0) {
    DAT_8009c454 = 1;
  }
  _DAT_8009c43c = DAT_8009c454 + 1;
  DAT_8009c333 = 2;
  if (DAT_8009c334 == '\0') {
    DAT_8009c333 = (undefined1)_DAT_8009c43c;
  }
  DAT_8009c334 = 0;
  DAT_8009c428 = 0xffffffff;
  FUN_800746b8(0);
  DAT_8009c42c = DAT_8009c42c + 1;
  return;
}

