/* Analysis pseudo-C, not buildable source. */

void FUN_80032490(int param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  int *piVar3;
  
  iVar1 = 0;
  piVar3 = &DAT_801d4244 + param_2 + -1;
  psVar2 = (short *)(param_1 + 0x2d58);
  do {
    if (*(char *)((int)psVar2 + 5) == '\0') {
      *(undefined1 *)((int)psVar2 + 5) = 1;
      psVar2[-2] = (short)param_2;
      *(byte *)(psVar2 + 1) = (byte)(*piVar3 >> 0x1a) & 0x1f;
      psVar2[-1] = ((ushort)*piVar3 & 0x1ff) * 10;
      *psVar2 = ((ushort)(*piVar3 >> 9) & 0x1ff) * 10;
      FUN_80033144(param_1 + 0x2d50);
      FUN_800323f0(param_1);
      return;
    }
    iVar1 = iVar1 + 1;
    psVar2 = psVar2 + 8;
  } while (iVar1 < 0x28);
  return;
}

