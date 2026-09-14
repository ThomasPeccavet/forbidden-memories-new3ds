/* Analysis pseudo-C, not buildable source. */

void FUN_80075a54(undefined4 param_1,undefined2 param_2,int param_3)

{
  *(undefined2 *)(DAT_80093fb8 + 0x1a6) = param_2;
  FUN_80076030();
  *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) | 0x30;
  FUN_80076030();
  FUN_80076008();
  *DAT_80093fbc = param_1;
  *DAT_80093fc0 = param_3 << 0x10 | 0x10;
  DAT_80094008 = 1;
  *DAT_80093fc4 = 0x1000200;
  return;
}

