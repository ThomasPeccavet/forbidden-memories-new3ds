/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8001eda4(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    if ((*(ushort *)(param_1 + 0x16) & 0x200) == 0) {
      uVar2 = (int)(&DAT_801d4244)[*(short *)(param_1 + 0xc) + -1] >> 0x16;
    }
    else {
      uVar2 = (int)(&DAT_801d4244)[*(short *)(param_1 + 0xc) + -1] >> 0x12;
    }
    if ((*(ushort *)(param_2 + 0x16) & 0x200) == 0) {
      uVar3 = (int)(&DAT_801d4244)[*(short *)(param_2 + 0xc) + -1] >> 0x16;
    }
    else {
      uVar3 = (int)(&DAT_801d4244)[*(short *)(param_2 + 0xc) + -1] >> 0x12;
    }
    uVar1 = FUN_8002cd54(uVar2 & 0xf,uVar3 & 0xf);
  }
  return uVar1;
}

