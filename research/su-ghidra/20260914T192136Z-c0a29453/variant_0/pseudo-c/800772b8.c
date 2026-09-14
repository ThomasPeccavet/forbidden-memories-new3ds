/* Analysis pseudo-C, not buildable source. */

bool FUN_800772b8(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_2 == 5) {
    uVar1 = 0;
    uVar2 = 0x20;
  }
  else {
    uVar1 = 0;
    if (param_2 == 6) {
      param_1 = param_1 + 0x800;
      uVar1 = 0x100;
      uVar2 = 0x20;
    }
    else {
      uVar2 = 0x40;
    }
  }
  FUN_80075a54(param_1,uVar1,uVar2);
  return (*(ushort *)(DAT_80093fb8 + 0x1ae) & 0x800) != 0;
}

