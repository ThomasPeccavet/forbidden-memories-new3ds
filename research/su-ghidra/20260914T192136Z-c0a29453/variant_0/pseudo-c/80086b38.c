/* Analysis pseudo-C, not buildable source. */

int FUN_80086b38(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_10;
  undefined1 auStack_c [4];
  
  if (-1 < param_1) {
    uVar2 = param_1 + (param_1 >> 0xc) * -0x1000;
    if (0x3ff < uVar2) {
      if (0x3ff < uVar2 - 0x400) {
        uVar3 = uVar2 - 0x800;
        if (0x3ff < uVar3) {
          if (0x3ff < uVar2 - 0xc00) {
            return param_2;
          }
          uVar3 = 0xfff - uVar2;
        }
        FUN_80086978(uVar3,&local_10,auStack_c);
        return -local_10;
      }
      uVar2 = 0x7ff - uVar2;
    }
    FUN_80086978(uVar2,&local_10,auStack_c);
    return local_10;
  }
  param_1 = -param_1;
  iVar1 = param_1;
  if (param_1 < 0) {
    iVar1 = param_1 + 0xfff;
  }
  uVar2 = param_1 + (iVar1 >> 0xc) * -0x1000;
  if (uVar2 < 0x400) {
LAB_80086b84:
    FUN_80086978(uVar2,&local_10,auStack_c);
    return -local_10;
  }
  if (uVar2 - 0x400 < 0x400) {
    uVar2 = 0x7ff - uVar2;
    goto LAB_80086b84;
  }
  uVar3 = uVar2 - 0x800;
  if (0x3ff < uVar3) {
    if (0x3ff < uVar2 - 0xc00) goto LAB_80086bd8;
    uVar3 = 0xfff - uVar2;
  }
  FUN_80086978(uVar3,&local_10,auStack_c);
  param_3 = -local_10;
LAB_80086bd8:
  return -param_3;
}

