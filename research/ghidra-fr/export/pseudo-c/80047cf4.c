/* Analysis pseudo-C, not buildable source. */

void FUN_80047cf4(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_8009c7e0;
  iVar2 = 0x100000;
  if (param_1 != 0) {
    iVar2 = 0x100000 << (param_1 & 0x1f);
  }
  *(int *)(DAT_8009c7e0 + 0x3c4) = iVar2;
  iVar2 = iVar1 + param_1 * 2;
  *(undefined4 *)(iVar1 + 0x3c8) = 3;
  *(short *)(iVar1 + 0x3cc) =
       (short)((uint)*(ushort *)(iVar2 + 0x414) * (uint)*(byte *)(iVar1 + param_1 + 0x424) >> 8);
  *(short *)(iVar1 + 0x3ce) =
       (short)((uint)*(ushort *)(iVar2 + 0x41c) * (uint)*(byte *)(iVar1 + param_1 + 0x424) >> 8);
  FUN_800779e8(iVar1 + 0x3c4);
  return;
}

