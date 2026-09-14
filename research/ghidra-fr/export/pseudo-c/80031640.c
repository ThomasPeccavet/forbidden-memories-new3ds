/* Analysis pseudo-C, not buildable source. */

void FUN_80031640(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar3 = FUN_80042ec8();
  if (iVar3 == 0) {
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined2 *)(param_1 + 0x60) = 0;
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xf7ffffff;
    *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
    FUN_80040204(10);
  }
  if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
    if ((*(byte *)(param_1 + 0x6c) & 0x20) == 0) {
      FUN_80042da8(param_1);
      uVar1 = *(short *)(param_1 + 0x60) - 1;
      *(ushort *)(param_1 + 0x60) = uVar1;
      if ((int)((uint)uVar1 << 0x10) < 1) {
        *(undefined2 *)(param_1 + 0x60) = 8;
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x18);
        *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x20;
      }
    }
    else {
      uVar1 = *(short *)(param_1 + 0x60) - 1;
      *(ushort *)(param_1 + 0x60) = uVar1;
      uVar2 = (undefined2)((int)((uint)uVar1 << 0x10) >> 7);
      *(undefined2 *)(param_1 + 0x46) = uVar2;
      *(undefined2 *)(param_1 + 0x44) = uVar2;
      if (*(short *)(param_1 + 0x60) == 0) {
        FUN_80040690(param_1);
      }
    }
  }
  else {
    uVar1 = *(short *)(param_1 + 0x60) + 1;
    *(ushort *)(param_1 + 0x60) = uVar1;
    uVar2 = (undefined2)((int)((uint)uVar1 << 0x10) >> 7);
    *(undefined2 *)(param_1 + 0x46) = uVar2;
    *(undefined2 *)(param_1 + 0x44) = uVar2;
    if (7 < *(short *)(param_1 + 0x60)) {
      FUN_80042d08(param_1);
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) & 0xbf;
      *(undefined2 *)(param_1 + 0x60) = 0xc;
      *(short *)(param_1 + 0x36) =
           (short)((((int)*(short *)(param_1 + 0x18) - (int)*(short *)(param_1 + 0x30)) * 0x100) /
                  0xc);
      *(short *)(param_1 + 0x38) =
           (short)((((int)*(short *)(param_1 + 0x1a) - (int)*(short *)(param_1 + 0x32)) * 0x100) /
                  0xc);
    }
  }
  return;
}

