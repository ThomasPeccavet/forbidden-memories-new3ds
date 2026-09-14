/* Analysis pseudo-C, not buildable source. */

void FUN_8004f838(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  int unaff_gp;
  
  if ((*(char *)(unaff_gp + 0x7b) != '\x01') || (*(char *)(unaff_gp + 0x7c) != '\x01')) {
    cVar1 = *(char *)(unaff_gp + 0x7a);
    if (-1 < cVar1) {
      *(char *)(unaff_gp + 0x7a) = *(char *)(unaff_gp + 0x7a) + '\x01';
    }
    bVar2 = '\0' < cVar1;
    while (param_1 != 0) {
      FUN_8004f92c(bVar2,param_2,param_3,param_4);
      if (param_2 != 0) {
        param_2 = param_2 + 8;
      }
      if (param_3 != 0) {
        param_3 = param_3 + 8;
      }
      if ((param_2 == 0) || (*(short *)(param_2 + 6) == 0)) {
        if (param_3 == 0) {
          return;
        }
        if (*(short *)(param_3 + 6) == 0) {
          return;
        }
      }
      if (0 < param_1) {
        param_1 = param_1 + -1;
      }
      bVar2 = true;
    }
  }
  return;
}

