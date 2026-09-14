/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800495c8(uint param_1)

{
  int *piVar1;
  int iVar2;
  byte *pbVar3;
  
  if ((uint)**(ushort **)(DAT_8009c7e0 + 0x1564) != (int)(param_1 << 0x10) >> 0x14) {
    FUN_80046750();
    FUN_800494a0();
    FUN_80078588(0);
    iVar2 = DAT_8009c7e0;
    piVar1 = (int *)(DAT_8009c7e0 + 0x1560);
    *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) | 2;
    pbVar3 = (byte *)(((param_1 & 0xff0) >> 1) + *piVar1);
    FUN_80047660(*(undefined4 *)(pbVar3 + 4),*(undefined4 *)(iVar2 + 0x1564),
                 *(undefined2 *)(pbVar3 + 2),(uint)*pbVar3 << 0xb,(uint)pbVar3[1] << 0xb,0x20);
    **(undefined2 **)(DAT_8009c7e0 + 0x1564) = 0xffff;
  }
  return 0;
}

