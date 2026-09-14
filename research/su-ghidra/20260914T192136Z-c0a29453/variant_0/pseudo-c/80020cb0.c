/* Analysis pseudo-C, not buildable source. */

void FUN_80020cb0(int param_1)

{
  ushort uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar1 = *(short *)(param_1 + 0x28) - 2;
  *(ushort *)(param_1 + 0x28) = uVar1;
  if ((int)((uint)uVar1 << 0x10) < 1) {
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x2c);
  }
  else {
    if ((DAT_8009c42c & 1) != 0) {
      uVar3 = FUN_80040350();
      iVar4 = FUN_800403d0(uVar3,2);
      if (iVar4 != 0) {
        FUN_80042bd8(iVar4,(int)*(short *)(param_1 + 0x30),(int)*(short *)(param_1 + 0x32),0,
                     *(undefined1 *)(param_1 + 0x68),*(undefined1 *)(param_1 + 0x69),0x11,9,
                     &DAT_801af000);
        *(short *)(iVar4 + 0x40) = *(short *)(param_1 + 0x40) + 0x80;
        *(ushort *)(iVar4 + 8) = *(ushort *)(iVar4 + 8) | 0x28;
        *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x50000000;
        FUN_80042c1c(iVar4,(int)((*(byte *)(param_1 + 0x16) - 1) * 0x1000000) >> 0x18);
        *(undefined2 *)(iVar4 + 0x60) = 8;
        *(code **)(iVar4 + 0x24) = FUN_80042ef0;
      }
    }
    sVar2 = *(short *)(param_1 + 0x2a) + 0x30;
    *(short *)(param_1 + 0x2a) = sVar2;
    iVar4 = FUN_800866f8((int)sVar2);
    iVar4 = iVar4 * *(short *)(param_1 + 0x28);
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x2c) + (short)(iVar4 >> 0xc);
    iVar4 = FUN_80086628((int)*(short *)(param_1 + 0x2a));
    iVar4 = iVar4 * *(short *)(param_1 + 0x28);
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    *(short *)(param_1 + 0x32) = *(short *)(param_1 + 0x2e) + (short)(iVar4 >> 0xc);
  }
  return;
}

