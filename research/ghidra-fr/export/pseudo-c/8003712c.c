/* Analysis pseudo-C, not buildable source. */

void FUN_8003712c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    uVar1 = FUN_80040390();
    iVar2 = FUN_800403d0(uVar1,4);
    FUN_80042b0c(iVar2,1);
    FUN_80042c48(iVar2);
    FUN_80042c1c(iVar2,(int)((*(byte *)(*(int *)(param_1 + 0x28) + 0x16) + 1) * 0x1000000) >> 0x18);
    *(int *)(param_1 + 0x30) = iVar2;
    *(undefined4 *)(iVar2 + 0x54) = 0x2000;
    *(undefined4 *)(iVar2 + 0x4c) = 0x2000;
    *(undefined4 *)(iVar2 + 0x34) = 0x2000;
    *(undefined4 *)(iVar2 + 0x2c) = 0x2000;
    *(undefined4 *)(iVar2 + 0x44) = 0xc000;
    *(undefined4 *)(iVar2 + 0x3c) = 0xc000;
    *(undefined1 **)(iVar2 + 0x24) = &LAB_80037094;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x50000000;
    FUN_80036ef0(param_1);
  }
  if ((*(ushort *)(param_1 + 0x34) & 8) != 0) {
    return;
  }
  if ((int)(char)DAT_8009c6e0 == 0) {
    iVar2 = FUN_80036f7c(param_1);
    if (iVar2 != 0) {
      return;
    }
    if ((DAT_8009c72c & 0xc0) == 0) {
      return;
    }
  }
  else {
    if ((DAT_8009c6e0 & 0x40) != 0) {
      DAT_8009c6d0 = DAT_8009c6e0 & 7;
      DAT_8009c6e0 = DAT_8009c6e0 & 0xbf;
      FUN_80036ef0(param_1);
      return;
    }
    if (((int)(char)DAT_8009c6e0 & 0x80U) == 0) {
      return;
    }
    DAT_8009c6e0 = 0;
  }
  if (((uint)DAT_8009c6a8 & 1 << ((int)(char)DAT_8009c6d0 & 0x1fU)) == 0) {
    FUN_80040204(9);
  }
  else {
    *(undefined1 *)(param_1 + 0x51) = 0;
    FUN_80040204(7);
    if ((DAT_8009c6c8 & 0x40) == 0) {
      FUN_80040690(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x51) = 3;
    }
  }
  return;
}

