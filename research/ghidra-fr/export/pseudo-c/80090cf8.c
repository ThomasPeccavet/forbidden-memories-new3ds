/* Analysis pseudo-C, not buildable source. */

void FUN_80090cf8(char *param_1)

{
  char cVar1;
  
  if (param_1 == (char *)0x0) {
    param_1 = &DAT_8001286c;
  }
  while( true ) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    if (cVar1 == '\0') break;
    FUN_800901a8((int)cVar1);
  }
  FUN_800902a4();
  return;
}

