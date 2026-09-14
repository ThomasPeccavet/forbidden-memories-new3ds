/* Analysis pseudo-C, not buildable source. */

void FUN_80021950(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined2 *puVar3;
  int iVar4;
  
  pbVar2 = &DAT_801d024f + param_1;
  bVar1 = *pbVar2;
  *pbVar2 = bVar1 + 1;
  if (0xfa < (byte)(bVar1 + 1)) {
    *pbVar2 = 0xfa;
  }
  iVar4 = 0xe;
  puVar3 = &DAT_801d07d8;
  do {
    iVar4 = iVar4 + -1;
    puVar3[1] = *puVar3;
    puVar3 = puVar3 + -1;
  } while (-1 < iVar4);
  DAT_801d07bc = (short)param_1;
  return;
}

