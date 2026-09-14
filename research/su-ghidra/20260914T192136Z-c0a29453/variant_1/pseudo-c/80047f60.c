/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80047f60(ushort param_1)

{
  ushort *puVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)param_1;
  if ((*(int *)(uVar3 * 8 + *(int *)(DAT_8009c7e0 + 0x448) + 4) != 0) &&
     (*(ushort *)(DAT_8009c7e0 + 0x442) != uVar3)) {
    FUN_80047ef8();
    FUN_80047acc();
    iVar2 = DAT_8009c7e0;
    puVar1 = (ushort *)(DAT_8009c7e0 + 0x40);
    *(ushort *)(DAT_8009c7e0 + 0x442) = param_1;
    *(ushort *)(iVar2 + 0x40) = *puVar1 | 2;
    FUN_80047c18(uVar3);
  }
  return 1;
}

