/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8003ad68) */

void FUN_8003ad20(int param_1)

{
  int iVar1;
  int iVar2;
  short sVar3;
  
  iVar1 = FUN_8003a2ac();
  if (iVar1 == 0) {
    iVar1 = 0x400 / (int)*(short *)(param_1 + 0x44);
    if (*(short *)(param_1 + 0x44) == 0) {
      trap(0x1c00);
    }
    *(undefined2 *)(param_1 + 0x48) = 0x400;
    *(short *)(param_1 + 0x4a) = (short)iVar1;
    if (-1 < iVar1) {
      *(undefined2 *)(param_1 + 0x48) = 0;
    }
    *(short *)(param_1 + 0x44) = *(short *)(param_1 + 0x40) - *(short *)(param_1 + 0x34);
    *(short *)(param_1 + 0x46) = *(short *)(param_1 + 0x42) - *(short *)(param_1 + 0x36);
  }
  sVar3 = *(short *)(param_1 + 0x48) + *(short *)(param_1 + 0x4a);
  *(short *)(param_1 + 0x48) = sVar3;
  if ((ushort)(sVar3 - 1U) < 0x3ff) {
    iVar2 = FUN_800866f8((int)sVar3);
    iVar1 = iVar2 * *(short *)(param_1 + 0x44);
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xfff;
    }
    iVar2 = iVar2 * *(short *)(param_1 + 0x46);
    iVar1 = iVar1 >> 0xc;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xfff;
    }
    iVar2 = iVar2 >> 0xc;
    if (*(short *)(param_1 + 0x4a) < 0) {
      iVar1 = *(short *)(param_1 + 0x44) - iVar1;
      iVar2 = *(short *)(param_1 + 0x46) - iVar2;
    }
    FUN_8003acec(param_1,(int)(((uint)*(ushort *)(param_1 + 0x40) - iVar1) * 0x10000) >> 0x10,
                 (int)(((uint)*(ushort *)(param_1 + 0x42) - iVar2) * 0x10000) >> 0x10);
  }
  else {
    FUN_8003acec(param_1,(int)*(short *)(param_1 + 0x40),(int)*(short *)(param_1 + 0x42));
    *(undefined1 *)(param_1 + 0x33) = 0;
  }
  return;
}

