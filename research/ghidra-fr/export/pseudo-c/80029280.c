/* Analysis pseudo-C, not buildable source. */

void FUN_80029280(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = '\x02';
  if (-1 < param_2) {
    cVar1 = *(char *)(param_1 + 0x6a);
  }
  if (cVar1 != *(char *)(param_1 + 0x69)) {
    FUN_80040734(param_1,cVar1);
    FUN_80042090(param_1);
    DAT_8009c794 = 1;
  }
  return;
}

