/* Analysis pseudo-C, not buildable source. */

void FUN_80184324(int param_1,int param_2,int param_3)

{
  short *psVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = &DAT_80184828;
  do {
    psVar1 = (short *)(puVar2 + param_1 * 0xb48);
    if (*psVar1 == param_2) {
      if (0xfa < (uint)(ushort)psVar1[1] + param_3) {
        return;
      }
      psVar1[1] = (short)((uint)(ushort)psVar1[1] + param_3);
      return;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 4;
  } while (iVar3 < 0x2d2);
  return;
}

