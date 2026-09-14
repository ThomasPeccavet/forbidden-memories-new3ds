/* Analysis pseudo-C, not buildable source. */

int FUN_80086628(uint param_1)

{
  int iVar1;
  
  if ((int)param_1 < 0) {
    iVar1 = FUN_80086664(-param_1 & 0xfff);
    iVar1 = -iVar1;
  }
  else {
    iVar1 = FUN_80086664(param_1 & 0xfff);
  }
  return iVar1;
}

