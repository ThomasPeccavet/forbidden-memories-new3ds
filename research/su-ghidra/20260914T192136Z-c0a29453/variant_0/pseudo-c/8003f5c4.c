/* Analysis pseudo-C, not buildable source. */

undefined1 FUN_8003f5c4(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = FUN_80042ec8();
  if (iVar1 == 0) {
    FUN_800434a8(param_1);
  }
  iVar1 = (int)*(short *)(param_1 + 0x60);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x40;
    if (iVar1 < 0) goto LAB_8003f638;
    *(undefined1 *)(param_1 + 0x6c) = 0;
  }
  else {
    iVar1 = iVar1 + -0x40;
    if (0 < iVar1) goto LAB_8003f638;
    *(undefined1 *)(param_1 + 0x6c) = 0;
  }
  iVar1 = 0;
LAB_8003f638:
  *(short *)(param_1 + 0x60) = (short)iVar1;
  FUN_80043560(param_1,param_2,param_3);
  if (-1 < param_4) {
    FUN_80039910(&DAT_800f0850 + param_4 * 100,(int)*(short *)(param_1 + 0x30),
                 (int)*(short *)(param_1 + 0x32));
  }
  return *(undefined1 *)(param_1 + 0x6c);
}

