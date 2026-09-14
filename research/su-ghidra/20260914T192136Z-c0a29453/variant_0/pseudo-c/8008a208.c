/* Analysis pseudo-C, not buildable source. */

void FUN_8008a208(int param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar3 = *(uint *)(param_1 + 4);
  if ((uVar3 & 1) == 0) {
    *(uint *)(param_1 + 4) = uVar3 | 1;
    iVar6 = 0;
    piVar1 = (int *)(param_1 + *(int *)(param_1 + 8) * 4);
    *(int *)(param_1 + 8) = (int)piVar1;
    iVar7 = *piVar1;
    piVar1 = piVar1 + 1;
    if (0 < iVar7) {
      do {
        iVar5 = *piVar1;
        piVar1 = piVar1 + 1;
        iVar4 = 0;
        if (0 < iVar5) {
          do {
            if (*piVar1 < 0) {
              *piVar1 = param_1 + *piVar1 * 4;
            }
            iVar4 = iVar4 + 1;
            piVar1 = piVar1 + 1;
          } while (iVar4 < iVar5);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar7);
    }
    iVar7 = *(int *)(param_1 + 0xc);
    piVar1 = (int *)(param_1 + 0x10);
    iVar6 = 0;
    if (0 < iVar7) {
      do {
        if (*piVar1 != 0) {
          piVar2 = (int *)(param_1 + *piVar1 * 4);
          *piVar1 = (int)piVar2;
          iVar4 = *piVar2;
          while (iVar4 != -1) {
            if ((piVar2[2] & 0x80000000U) == 0) goto LAB_8008a384;
            *piVar2 = param_1 + *piVar2 * 4;
            piVar2[1] = param_1 + piVar2[1] * 4;
            piVar2[2] = piVar2[2] & 0x7fffffff;
            piVar2 = (int *)*piVar2;
            iVar4 = *piVar2;
          }
          if ((piVar2[2] & 0x80000000U) != 0) {
            piVar2[1] = param_1 + piVar2[1] * 4;
            piVar2[2] = piVar2[2] & 0x7fffffff;
          }
        }
LAB_8008a384:
        iVar6 = iVar6 + 1;
        piVar1 = piVar1 + 1;
      } while (iVar6 < iVar7);
    }
  }
  return;
}

