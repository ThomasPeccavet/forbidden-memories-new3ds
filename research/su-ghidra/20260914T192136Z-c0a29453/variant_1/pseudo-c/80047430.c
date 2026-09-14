/* Analysis pseudo-C, not buildable source. */

void FUN_80047430(ushort param_1)

{
  if (*(byte *)(DAT_8009c7e0 + 0x48) != param_1) {
    *(char *)(DAT_8009c7e0 + 0x48) = (char)param_1;
    if (param_1 == 0) {
      FUN_80049a6c();
    }
    else {
      FUN_80049a7c();
    }
    FUN_8004527c((int)*(short *)(DAT_8009c7e0 + 0x510));
  }
  return;
}

