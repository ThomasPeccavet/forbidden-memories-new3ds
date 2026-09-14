/* Analysis pseudo-C, not buildable source. */

int FUN_800868a8(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auStack_10 [4];
  int local_c;
  
  if (param_1 < 0) {
    param_1 = -param_1;
  }
  iVar1 = param_1;
  if (param_1 < 0) {
    iVar1 = param_1 + 0xfff;
  }
  uVar2 = param_1 + (iVar1 >> 0xc) * -0x1000;
  if (uVar2 < 0x400) {
    FUN_80086978(uVar2,auStack_10,&local_c);
  }
  else {
    if (uVar2 - 0x400 < 0x400) {
      uVar3 = 0x7ff - uVar2;
    }
    else {
      uVar3 = uVar2 - 0x800;
      if (0x3ff < uVar3) {
        if (0x3ff < uVar2 - 0xc00) {
          return 0;
        }
        FUN_80086978(0xfff - uVar2,auStack_10,&local_c);
        return local_c;
      }
    }
    FUN_80086978(uVar3,auStack_10,&local_c);
    local_c = -local_c;
  }
  return local_c;
}

