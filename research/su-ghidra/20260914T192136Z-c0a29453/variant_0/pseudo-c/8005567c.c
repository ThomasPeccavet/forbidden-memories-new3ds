/* Analysis pseudo-C, not buildable source. */

void FUN_8005567c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_8009c7fc < 0x801) {
    iVar4 = -4;
  }
  else {
    iVar4 = 0;
    if ((-200 < DAT_800f6c38) && (DAT_800f6c2c < DAT_800f6c38)) {
      if (DAT_800f6c38 < -100) {
        iVar4 = -(((-200 - DAT_800f6c38) * 0x1000) / 100);
      }
      else {
        iVar4 = 0x1000;
      }
    }
    iVar1 = iVar4 * -0xd5 + 0xf80000;
    if (iVar1 < 0) {
      iVar1 = iVar4 * -0xd5 + 0xf80fff;
    }
    iVar3 = (iVar1 >> 0xc) + -0x10;
    iVar2 = (int)DAT_8009c7fc;
    iVar1 = (iVar1 >> 0xc) + 0x10;
    iVar4 = iVar1 - iVar2;
    if (iVar1 < iVar2) {
      if (iVar4 < -1) {
        iVar4 = -1;
      }
    }
    else if (iVar2 < 0xeab) {
      iVar4 = 0xeab - iVar2;
    }
    else {
      iVar4 = iVar3 - iVar2;
      if (iVar3 <= iVar2) {
        return;
      }
      if (4 < iVar4) {
        iVar4 = 4;
      }
    }
  }
  FUN_8005b5cc(1,0,iVar4,0,0);
  return;
}

