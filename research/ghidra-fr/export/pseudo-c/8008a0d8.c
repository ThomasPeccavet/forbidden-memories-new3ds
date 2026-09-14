/* Analysis pseudo-C, not buildable source. */

void FUN_8008a0d8(int param_1,int *param_2,int *param_3)

{
  uint *puVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  int *piVar11;
  
  *param_3 = *(int *)(param_1 + 4);
  piVar10 = *(int **)(param_1 + 4);
  param_3[1] = (int)param_2;
  param_3[2] = 0xe - *param_2;
  iVar4 = param_2[2];
  param_3[4] = DAT_800ff5c4;
  param_3[3] = iVar4;
  do {
    *param_3 = (int)piVar10;
    piVar11 = (int *)*piVar10;
    *param_3 = (int)(piVar10 + 1);
    puVar7 = (uint *)piVar10[1];
    uVar8 = 0;
    if (*puVar7 != 0) {
      puVar6 = (uint *)(param_3 + 5);
      puVar5 = puVar7;
      do {
        puVar1 = puVar5 + 1;
        puVar5 = puVar5 + 1;
        uVar8 = uVar8 + 1;
        *puVar6 = *puVar1;
        puVar6 = puVar6 + 1;
      } while (uVar8 < *puVar7);
    }
    iVar4 = *param_3;
    uVar8 = 0;
    *param_3 = iVar4 + 4;
    uVar9 = *(uint *)(iVar4 + 4);
    *param_3 = iVar4 + 8;
    if (uVar9 != 0) {
      do {
        pcVar2 = *(code **)*param_3;
        *param_3 = (int)((undefined4 *)*param_3 + 1);
        iVar3 = (*pcVar2)(param_3);
        iVar4 = DAT_800ff5c4;
        uVar8 = uVar8 + 1;
        *param_3 = iVar3;
        param_3[4] = iVar4;
      } while (uVar8 < uVar9);
    }
    piVar10 = piVar11;
  } while (piVar11 != (int *)0xffffffff);
  return;
}

