/* Analysis pseudo-C, not buildable source. */

void FUN_8007e3e4(char param_1,byte *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_28 [16];
  
  if (DAT_80094e48 == -1) {
    uVar1 = FUN_8007c4bc();
    DAT_80094e48 = FUN_8007eca8(uVar1);
  }
  if (param_1 == '\x01') {
    uVar2 = FUN_8007c4ac();
    if ((uVar2 & 0x20) == 0) {
      if ((DAT_80094e50 != (code *)0x0) && (DAT_80094e4c < DAT_80094e48)) {
        (*DAT_80094e50)(1,param_2,auStack_28);
        DAT_80094e4c = DAT_80094e48;
      }
    }
    else {
      uVar1 = FUN_8007ee38(0);
      FUN_8007e968(auStack_28,3);
      FUN_8007ee38(uVar1);
      iVar3 = FUN_8007eca8(auStack_28);
      if (iVar3 != DAT_80094e48) goto LAB_8007e5e0;
      if ((DAT_80094e50 != (code *)0x0) && (DAT_80094e4c < iVar3)) {
        (*DAT_80094e50)(1,param_2,auStack_28);
        DAT_80094e4c = iVar3;
      }
    }
    DAT_80094e48 = DAT_80094e48 + 1;
  }
  else {
    if (param_1 == '\x04') {
      if (DAT_80094e50 != (code *)0x0) {
        (*DAT_80094e50)(4,param_2,auStack_28);
      }
      goto LAB_8007e5e4;
    }
    if ((*param_2 & 0x10) != 0) {
      if (DAT_80094e64 == 1) {
        FUN_8007edf8(0);
        return;
      }
      FUN_8007edf8(DAT_80094e5c);
      FUN_8007ee18(DAT_80094e60);
      DAT_80094e68 = 0;
      if (DAT_80094e50 == (code *)0x0) {
        DAT_80094e68 = 0;
        return;
      }
      (*DAT_80094e50)(param_1,param_2,auStack_28);
      return;
    }
    iVar3 = FUN_8007c058();
    if ((iVar3 != 0) || ((*param_2 & 0xa0) != 0)) goto LAB_8007e5e4;
LAB_8007e5e0:
    DAT_80094e54 = 1;
  }
LAB_8007e5e4:
  if (DAT_80094e54 == 1) {
    if ((DAT_80094e58 < 1) && (DAT_80094e58 != -1)) {
      if (DAT_80094e68 == 1) {
        FUN_8007edf8(DAT_80094e5c);
        FUN_8007ee18(DAT_80094e60);
        FUN_8007b78c(9,0,0,0xffffffff);
      }
      DAT_80094e68 = 0;
      if (DAT_80094e50 != (code *)0x0) {
        (*DAT_80094e50)(5,param_2,auStack_28);
      }
    }
    else {
      FUN_8007e778();
      if (0 < DAT_80094e58) {
        DAT_80094e58 = DAT_80094e58 + -1;
      }
    }
    DAT_80094e54 = 0;
  }
  return;
}

