/* Analysis pseudo-C, not buildable source. */

void FUN_800391ec(int param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x28);
  if (iVar5 == 0) {
    uVar2 = FUN_80040390();
    iVar5 = FUN_800403d0(uVar2,6);
    uVar1 = *(undefined1 *)(param_1 + 0x57);
    *(undefined2 *)(iVar5 + 0x40) = 0x280;
    *(undefined2 *)(iVar5 + 0x42) = 0xc0;
    *(undefined1 *)(iVar5 + 0x66) = 10;
    *(code **)(iVar5 + 0x4c) = FUN_80036298;
    *(undefined1 *)(iVar5 + 0x67) = uVar1;
    *(ushort *)(iVar5 + 8) = *(ushort *)(iVar5 + 8) | 8;
    *(int *)(param_1 + 0x28) = iVar5;
  }
  FUN_80042c48(iVar5);
  FUN_80042c1c(iVar5,(int)*(char *)(param_1 + 0x59));
  *(undefined2 *)(iVar5 + 0x30) = *(undefined2 *)(param_1 + 0x3c);
  *(undefined2 *)(iVar5 + 0x32) = *(undefined2 *)(param_1 + 0x40);
  *(undefined2 *)(iVar5 + 0x3c) = *(undefined2 *)(param_1 + 0x3e);
  *(undefined2 *)(iVar5 + 0x3e) = *(undefined2 *)(param_1 + 0x42);
  iVar3 = (uint)*(ushort *)(param_1 + 0x3e) << 0x10;
  uVar4 = (undefined2)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  *(undefined2 *)(iVar5 + 0x18) = uVar4;
  *(undefined2 *)(iVar5 + 0x48) = uVar4;
  iVar3 = (uint)*(ushort *)(param_1 + 0x42) << 0x10;
  uVar4 = (undefined2)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  *(undefined2 *)(iVar5 + 0x1a) = uVar4;
  *(undefined2 *)(iVar5 + 0x4a) = uVar4;
  if ((*(ushort *)(param_1 + 0x34) & 0x40) != 0) {
    if (*(int *)(param_1 + 0x2c) != 0) {
      FUN_80040690();
    }
    uVar2 = FUN_80040350();
    iVar5 = FUN_800403d0(uVar2,4);
    FUN_80042b0c(iVar5,1);
    *(int *)(param_1 + 0x2c) = iVar5;
    *(uint *)(iVar5 + 4) = *(uint *)(iVar5 + 4) | 0x60000000;
    FUN_80042c48(iVar5);
    FUN_80042c1c(iVar5,(int)((*(byte *)(param_1 + 0x59) - 1) * 0x1000000) >> 0x18);
    *(undefined4 *)(iVar5 + 0x54) = 0xa0a0a0;
    *(undefined4 *)(iVar5 + 0x4c) = 0xa0a0a0;
    *(undefined4 *)(iVar5 + 0x34) = 0xa0a0a0;
    *(undefined4 *)(iVar5 + 0x2c) = 0xa0a0a0;
    *(undefined4 *)(iVar5 + 0x44) = 0x808080;
    *(undefined4 *)(iVar5 + 0x3c) = 0x808080;
    FUN_80039148(param_1);
  }
  return;
}

