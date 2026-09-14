/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8003afd8(int *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_8003a2ac();
  if (iVar2 == 0) {
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) | 0x10;
    iVar2 = (int)*(char *)(*param_1 + 0x16);
    uVar1 = *(undefined1 *)(*param_1 + 0x67);
    FUN_8003a7d0(param_1,0x50000000,iVar2);
    FUN_8003a57c(param_1,param_1 + 3,uVar1);
    FUN_8003a7d0(param_1 + 3,0x60000000,iVar2 + -1);
    *(undefined2 *)(param_1 + 0x10) = 0x80;
  }
  iVar2 = (uint)*(ushort *)(param_1 + 0x10) + _DAT_8009c43c * -8;
  *(short *)(param_1 + 0x10) = (short)iVar2;
  uVar3 = iVar2 * 0x10000 >> 0x10;
  if ((int)uVar3 < 1) {
    *(undefined1 *)((int)param_1 + 0x33) = 0;
    FUN_8003a320(param_1 + 3);
    FUN_8003a364(param_1);
  }
  else {
    uVar3 = uVar3 | uVar3 << 8 | uVar3 << 0x10;
    iVar2 = 2;
    param_1 = param_1 + 2;
    do {
      if (*param_1 != 0) {
        *(uint *)(*param_1 + 0xc) = uVar3;
      }
      if (param_1[3] != 0) {
        *(uint *)(param_1[3] + 0xc) = uVar3;
      }
      iVar2 = iVar2 + -1;
      param_1 = param_1 + -1;
    } while (-1 < iVar2);
  }
  return;
}

