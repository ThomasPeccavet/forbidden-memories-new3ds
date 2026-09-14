/* Analysis pseudo-C, not buildable source. */

int FUN_80026cf4(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  param_2 = (uint)DAT_8009c504 * 0xf + param_2;
  puVar1 = &DAT_801a7ad8 + param_2 * 7;
  psVar2 = (short *)(&DAT_801a7ae4 + param_2 * 0x1c);
  do {
    if (((psVar2[5] & 0x8000U) != 0) &&
       ((int)((int)(&DAT_801d4244)[*psVar2 + -1] >> 0x1a & 0x1fU) < param_3)) {
      *param_1 = puVar1;
      param_1 = param_1 + 1;
      iVar4 = iVar4 + 1;
    }
    iVar3 = iVar3 + 1;
    psVar2 = psVar2 + 0xe;
    puVar1 = puVar1 + 7;
  } while (iVar3 < 5);
  *param_1 = 0;
  return iVar4;
}

