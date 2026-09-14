/* Analysis pseudo-C, not buildable source. */

void FUN_80041fbc(int param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)(*(int *)(param_1 + 0x50) + (uint)*(ushort *)(param_1 + 0x58));
  bVar1 = *pbVar4;
  while( true ) {
    if (bVar1 < 0xf0) {
      *(ushort *)(param_1 + 0x5a) = (ushort)bVar1;
      uVar2 = *(ushort *)(pbVar4 + 1);
      *(short *)(param_1 + 0x58) = *(short *)(param_1 + 0x58) + 3;
      *(uint *)(param_1 + 0x4c) = *(int *)(param_1 + 0x54) + (uint)uVar2;
      return;
    }
    iVar3 = (*(code *)(&PTR_LAB_80092418)[bVar1 ^ 0xff])(param_1);
    if (iVar3 == -1) break;
    pbVar4 = (byte *)(*(int *)(param_1 + 0x50) + (uint)*(ushort *)(param_1 + 0x58));
    bVar1 = *pbVar4;
  }
  return;
}

