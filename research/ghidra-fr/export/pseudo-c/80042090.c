/* Analysis pseudo-C, not buildable source. */

void FUN_80042090(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(ushort *)(param_1 + 8);
  if ((uVar1 & 0x10) == 0) {
    iVar2 = *(int *)(param_1 + 0x54);
    *(ushort *)(param_1 + 8) = uVar1 | 0x10;
    *(undefined2 *)(param_1 + 0x58) = 0;
    *(undefined2 *)(param_1 + 0x5a) = 1;
    uVar1 = *(ushort *)
             (iVar2 + (uint)*(ushort *)
                             (iVar2 + (uint)*(ushort *)(iVar2 + (uint)*(byte *)(param_1 + 0x67) * 2)
                             + (uint)*(byte *)(param_1 + 0x68) * 2) +
             (uint)*(byte *)(param_1 + 0x69) * 2);
    uVar3 = *(uint *)(param_1 + 4) & 0xff7fffff;
    *(uint *)(param_1 + 4) = uVar3;
    *(uint *)(param_1 + 0x50) = iVar2 + (uint)uVar1;
    if ((*(ushort *)(param_1 + 8) & 0x100) != 0) {
      *(uint *)(param_1 + 4) = uVar3 | 0x800000;
    }
  }
  else {
    if ((uVar1 & 3) != 0) {
      return;
    }
    if (*(short *)(param_1 + 0x5a) == 0) {
      return;
    }
    iVar2 = (uint)*(ushort *)(param_1 + 0x5a) - (uint)DAT_8009c43c;
    *(short *)(param_1 + 0x5a) = (short)iVar2;
    if (0 < iVar2 * 0x10000) {
      return;
    }
  }
  FUN_80041fbc(param_1);
  return;
}

