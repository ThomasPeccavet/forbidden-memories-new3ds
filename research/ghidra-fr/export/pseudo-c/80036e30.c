/* Analysis pseudo-C, not buildable source. */

uint FUN_80036e30(int param_1)

{
  undefined4 *puVar1;
  byte *pbVar2;
  
  puVar1 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar1;
  *puVar1 = pbVar2 + 4;
  return (uint)pbVar2[3] << 0x18 | (uint)pbVar2[2] << 0x10 | (uint)pbVar2[1] << 8 | (uint)*pbVar2;
}

