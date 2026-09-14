/* Analysis pseudo-C, not buildable source. */

void FUN_8002cb88(int *param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  if ((int)param_2 < 0) {
    piVar3 = &DAT_801a7b64;
    piVar2 = &DAT_801a7d08;
    iVar4 = 0;
    do {
      if ((*(ushort *)((int)piVar3 + 0x16) & 0x8000) != 0) {
        *param_1 = *piVar3;
        param_1 = param_1 + 1;
      }
      if ((*(ushort *)((int)piVar2 + 0x16) & 0x8000) != 0) {
        *param_1 = *piVar2;
        param_1 = param_1 + 1;
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 7;
      piVar2 = piVar2 + 7;
    } while (iVar4 < 10);
    *param_1 = 0;
  }
  else {
    iVar4 = 0x14;
    if (DAT_8009c504 != '\0') {
      iVar4 = 5;
    }
    piVar2 = &DAT_801a7ad8 + iVar4 * 7;
    iVar4 = 0;
    if ((int)param_2 < 0x15) {
      do {
        if (((*(ushort *)((int)piVar2 + 0x16) & 0x8000) != 0) &&
           (((int)param_2 < 0 || (*(byte *)(*piVar2 + 0x68) == param_2)))) {
          *param_1 = *piVar2;
          param_1 = param_1 + 1;
        }
        iVar4 = iVar4 + 1;
        piVar2 = piVar2 + 7;
      } while (iVar4 < 5);
      *param_1 = 0;
    }
    else {
      do {
        if (((*(ushort *)((int)piVar2 + 0x16) & 0x8000) != 0) &&
           (uVar1 = FUN_80016fe4(piVar2), (int)param_2 <= (int)(uVar1 & 0xffff))) {
          *param_1 = *piVar2;
          param_1 = param_1 + 1;
        }
        iVar4 = iVar4 + 1;
        piVar2 = piVar2 + 7;
      } while (iVar4 < 5);
      *param_1 = 0;
    }
  }
  return;
}

