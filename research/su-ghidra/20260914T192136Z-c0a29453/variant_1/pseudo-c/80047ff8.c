/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80047ff8(short param_1)

{
  ushort *puVar1;
  int iVar2;
  
  iVar2 = DAT_8009c7e0;
  if (*(short *)(DAT_8009c7e0 + 0x442) != param_1) {
    puVar1 = (ushort *)(DAT_8009c7e0 + 0x40);
    *(short *)(DAT_8009c7e0 + 0x442) = param_1;
    *(ushort *)(iVar2 + 0x40) = *puVar1 | 2;
    FUN_80047c18(param_1);
  }
  return 1;
}

