/* Analysis pseudo-C, not buildable source. */

void FUN_80043cd4(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  do {
    FUN_80012c50();
    if ((!bVar1) && ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0)) {
      bVar1 = true;
    }
    if (((DAT_8009c72c & 0x8c0) != 0) && (bVar1)) {
      param_1 = 0;
    }
    param_1 = param_1 + -1;
  } while ((-1 < param_1) || (param_1 = 0, !bVar1));
  return;
}

