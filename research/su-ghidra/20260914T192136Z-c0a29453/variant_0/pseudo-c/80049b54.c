/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80049b54(int param_1,short param_2,undefined4 param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = DAT_8009c7d8;
  *(undefined4 *)(DAT_8009c7d8 + 0x818) = 0;
  iVar2 = DAT_8009c7d8;
  if ((param_2 != -1) || (uVar3 = 0xffffffff, *(short *)(iVar4 + 0x4a4) == -1)) {
    *(undefined2 *)(DAT_8009c7d8 + 0x4a4) = 0;
    *(int *)(iVar2 + 0x4a8) = param_1;
    iVar4 = (uint)*(ushort *)(param_1 + 0x12) * 0x200 + 0xa20;
    *(int *)(iVar2 + 0x4ac) = iVar4;
    *(int *)(iVar2 + 0x4b4) = *(int *)(param_1 + 0xc) - iVar4;
    *(undefined1 *)(iVar2 + 0x4bc) = *(undefined1 *)(param_1 + 0x18);
    uVar1 = *(undefined1 *)(param_1 + 0x19);
    uVar3 = 0;
    *(undefined4 *)(iVar2 + 0x4b8) = param_3;
    *(undefined1 *)(iVar2 + 0x4bf) = uVar1;
  }
  return uVar3;
}

