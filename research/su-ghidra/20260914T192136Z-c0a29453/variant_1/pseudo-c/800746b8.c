/* Analysis pseudo-C, not buildable source. */

uint FUN_800746b8(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  do {
  } while (*DAT_80092db4 != *DAT_80092db4);
  uVar3 = *DAT_80092db4 - DAT_80092db8 & 0xffff;
  uVar1 = DAT_80093ee8;
  if ((-1 < param_1) && (uVar1 = uVar3, param_1 != 1)) {
    uVar3 = DAT_80092dbc;
    if (0 < param_1) {
      uVar3 = (DAT_80092dbc - 1) + param_1;
    }
    iVar2 = 0;
    if (0 < param_1) {
      iVar2 = param_1 + -1;
    }
    FUN_80074830(uVar3,iVar2);
    uVar3 = *DAT_80092db0;
    FUN_80074830(DAT_80093ee8 + 1,1);
    if (((uVar3 & 0x400000) != 0) && (-1 < (int)(uVar3 ^ *DAT_80092db0))) {
      do {
      } while (((uVar3 ^ *DAT_80092db0) & 0x80000000) == 0);
    }
    DAT_80092dbc = DAT_80093ee8;
    do {
      DAT_80092db8 = *DAT_80092db4;
    } while (DAT_80092db8 != *DAT_80092db4);
  }
  return uVar1;
}

