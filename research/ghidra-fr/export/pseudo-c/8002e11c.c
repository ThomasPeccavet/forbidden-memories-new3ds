/* Analysis pseudo-C, not buildable source. */

void FUN_8002e11c(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0x10) {
    if (DAT_8009c44b == '\x01') {
      param_2 = 0x42;
    }
    else if (DAT_8009c44b == '\x02') {
      param_2 = 0x44;
    }
    else if (DAT_8009c44b == '\x03') {
      param_2 = 0x46;
    }
    else if (DAT_8009c44b == '\x04') {
      param_2 = 0x48;
    }
  }
  else if (param_2 == 0x11) {
    if (DAT_8009c44b == '\x01') {
      param_2 = 0x43;
    }
    else if (DAT_8009c44b == '\x02') {
      param_2 = 0x45;
    }
    else if (DAT_8009c44b == '\x03') {
      param_2 = 0x47;
    }
    else if (DAT_8009c44b == '\x04') {
      param_2 = 0x49;
    }
  }
  if (param_1 != 0) {
    *(short *)(param_1 + 0x3c) = (short)param_2;
  }
  iVar1 = (int)param_2 >> 8;
  if (iVar1 == 1) {
    iVar2 = 0x51;
    iVar1 = 0x672;
  }
  else if (iVar1 < 2) {
    iVar2 = 0x21;
    if (iVar1 != 0) {
      return;
    }
    iVar1 = 0;
  }
  else {
    iVar2 = 0x71;
    if (iVar1 != 2) {
      return;
    }
    iVar1 = 0x13bc;
  }
  iVar1 = FUN_80014e08(0,0,iVar1 + (((int)param_2 >> 4 & 0xfU) * 10 + (param_2 & 0xf)) * iVar2 +
                           0x29e8,iVar2,&LAB_8002dfe8,0,0);
  *(int *)(iVar1 + 0x38) = iVar2 + -1;
  DAT_8009c460 = *(uint *)(iVar1 + 0x2c) | 0x10;
  return;
}

