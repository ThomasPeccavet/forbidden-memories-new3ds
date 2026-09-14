/* Analysis pseudo-C, not buildable source. */

int FUN_8008111c(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  *DAT_80095bbc = *DAT_80095bbc | 0x8000000;
  *DAT_80095bb8 = 0;
  *DAT_80095bb0 = param_1 + param_2 * 4 + -4;
  *DAT_80095bb4 = param_2;
  *DAT_80095bb8 = 0x11000002;
  FUN_80082168();
  uVar1 = *DAT_80095bb8;
  while( true ) {
    if ((uVar1 & 0x1000000) == 0) {
      return param_2;
    }
    iVar2 = FUN_8008219c();
    if (iVar2 != 0) break;
    uVar1 = *DAT_80095bb8;
  }
  return -1;
}

