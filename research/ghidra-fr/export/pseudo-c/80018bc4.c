/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80018c0c) */

void FUN_80018bc4(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = FUN_80042ec8();
  if (iVar2 == 0) {
    if (*(short *)(param_1 + 0x60) == 0) {
      trap(0x1c00);
    }
    *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x30) + -0x140;
    *(short *)(param_1 + 0x2c) = (short)(0x400 / (int)*(short *)(param_1 + 0x60));
    FUN_800434a8(param_1);
    *(undefined2 *)(param_1 + 0x60) = 0xfc00;
  }
  FUN_80043560(param_1,(int)*(short *)(param_1 + 0x28),(int)*(short *)(param_1 + 0x32),
               (int)*(short *)(param_1 + 0x60));
  uVar1 = *(short *)(param_1 + 0x60) + *(short *)(param_1 + 0x2c);
  *(ushort *)(param_1 + 0x60) = uVar1;
  if (-1 < (int)((uint)uVar1 << 0x10)) {
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined2 *)(param_1 + 0x30) = *(undefined2 *)(param_1 + 0x28);
  }
  return;
}

