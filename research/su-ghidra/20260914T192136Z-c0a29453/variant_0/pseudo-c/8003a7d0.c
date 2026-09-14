/* Analysis pseudo-C, not buildable source. */

void FUN_8003a7d0(int param_1,uint param_2,char param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  if (param_2 == 0) {
    iVar3 = 2;
    piVar4 = (int *)(param_1 + 8);
    do {
      iVar2 = *piVar4;
      if (iVar2 != 0) {
        *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0x8fffffff | 0x40000000;
        FUN_80042c1c(iVar2,(int)param_3);
        *(undefined4 *)(iVar2 + 0xc) = 0x808080;
        *(short *)(iVar2 + 0x42) = *(short *)(iVar2 + 0x42) + -1;
      }
      iVar3 = iVar3 + -1;
      piVar4 = piVar4 + -1;
    } while (-1 < iVar3);
  }
  else {
    iVar3 = 2;
    piVar4 = (int *)(param_1 + 8);
    do {
      iVar2 = *piVar4;
      if (iVar2 != 0) {
        *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) & 0x8fffffff | param_2;
        FUN_80042c1c(iVar2,(int)param_3);
        sVar1 = 0xfd;
        if (param_2 != 0x60000000) {
          sVar1 = *(short *)(iVar2 + 0x42) + 1;
        }
        *(short *)(iVar2 + 0x42) = sVar1;
      }
      iVar3 = iVar3 + -1;
      piVar4 = piVar4 + -1;
    } while (-1 < iVar3);
  }
  return;
}

