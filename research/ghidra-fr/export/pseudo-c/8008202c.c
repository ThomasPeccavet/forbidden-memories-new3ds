/* Analysis pseudo-C, not buildable source. */

uint FUN_8008202c(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    FUN_80082168();
    do {
      if (DAT_80095bc0 == DAT_80095bc4) {
        while (((*DAT_80095bac & 0x1000000) != 0 || ((*DAT_80095ba0 & 0x4000000) == 0))) {
          iVar1 = FUN_8008219c();
          if (iVar1 != 0) {
            return 0xffffffff;
          }
        }
        return 0;
      }
      FUN_80081c90();
      iVar1 = FUN_8008219c();
    } while (iVar1 == 0);
    return 0xffffffff;
  }
  uVar2 = DAT_80095bc0 - DAT_80095bc4 & 0x3f;
  if (uVar2 != 0) {
    FUN_80081c90();
  }
  if (((*DAT_80095bac & 0x1000000) == 0) && ((*DAT_80095ba0 & 0x4000000) != 0)) {
    return uVar2;
  }
  if (uVar2 != 0) {
    return uVar2;
  }
  return 1;
}

