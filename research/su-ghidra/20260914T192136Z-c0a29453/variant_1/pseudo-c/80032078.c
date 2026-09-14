/* Analysis pseudo-C, not buildable source. */

void FUN_80032078(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_8009c6b8 = *(ushort *)(param_1 + (*(short *)(param_1 + 0x2d3c) + param_2) * 0x10 + 4);
  uVar2 = 0;
  if ((*(char *)(param_1 + (*(short *)(param_1 + 0x2d3c) + param_2) * 0x10 + 0xd) != '\0') &&
     (uVar2 = 6,
     0x13 < (*(int *)(&DAT_801d4240 + ((int)((uint)DAT_8009c6b8 << 0x10) >> 0xe)) >> 0x1a & 0x1fU)))
  {
    uVar2 = 7;
  }
  iVar1 = FUN_80036184(*(byte *)(param_1 + 0x2d47) + 1,uVar2,0x22,0x2c,0x120,0xe0);
  *(short *)(iVar1 + 0x3a) = (short)param_2 * 0x16;
  *(ushort *)(*(int *)(iVar1 + 0x28) + 8) = *(ushort *)(*(int *)(iVar1 + 0x28) + 8) & 0xfff7;
  if ((*(byte *)(param_1 + (*(short *)(param_1 + 0x2d3c) + param_2) * 0x10 + 0xd) & 0x80) != 0) {
    *(undefined1 *)(iVar1 + 0x54) = 4;
  }
  if (*(char *)(param_1 + 0x2d47) != '\0') {
    *(short *)(iVar1 + 0x3c) = *(short *)(iVar1 + 0x3c) + 0x160;
  }
  if (param_2 != 0) {
    *(ushort *)(iVar1 + 0x34) = *(ushort *)(iVar1 + 0x34) | 0x80;
  }
  FUN_800399f0();
  return;
}

