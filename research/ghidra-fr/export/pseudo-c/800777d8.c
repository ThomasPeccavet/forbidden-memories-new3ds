/* Analysis pseudo-C, not buildable source. */

int FUN_800777d8(int param_1)

{
  int iVar1;
  
  if ((DAT_80093f48 != 1) && (DAT_80093fec != 1)) {
    iVar1 = FUN_80073dc8(DAT_80093f40);
    if (param_1 == 1) {
      while (iVar1 == 0) {
        iVar1 = FUN_80073dc8(DAT_80093f40);
      }
    }
    else if (iVar1 != 1) {
      return iVar1;
    }
    DAT_80093fec = 1;
  }
  return 1;
}

