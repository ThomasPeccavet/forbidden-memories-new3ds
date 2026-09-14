/* Analysis pseudo-C, not buildable source. */

void FUN_80072278(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int local_30 [5];
  int local_1c [5];
  
  iVar1 = FUN_80070bb8();
  iVar9 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  uVar8 = 1;
  iVar7 = 0;
  iVar4 = 0;
  do {
    iVar3 = 0;
    iVar2 = iVar4;
    do {
      *(undefined4 *)((int)local_30 + iVar2) = 0;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 4;
    } while (iVar3 < 5);
    iVar7 = iVar7 + 1;
    iVar4 = iVar4 + 0x14;
  } while (iVar7 < 2);
  iVar4 = 0;
  while( true ) {
    iVar2 = 0;
    piVar5 = local_30;
    puVar6 = &DAT_801ab00c;
    iVar7 = iVar2;
    do {
      if ((*piVar5 == 0) && ((short)(&DAT_801ab002)[iVar7 * 6] < (short)puVar6[1])) {
        iVar7 = iVar2 + 1;
      }
      puVar6 = puVar6 + 6;
      iVar2 = iVar2 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar2 < 5);
    if (iVar7 != 0) {
      local_30[iVar7 + -1] = 1;
    }
    iVar3 = 0;
    iVar2 = 0;
    puVar6 = &DAT_801ab2a0;
    piVar5 = local_30;
    do {
      if ((piVar5[5] == 0) &&
         (((iVar9 == 0 || ((puVar6[3] & 0x1000) == 0)) &&
          ((short)(&DAT_801ab002)[iVar3 * 6] < (short)puVar6[1])))) {
        iVar3 = iVar2 + 0x38;
      }
      puVar6 = puVar6 + 6;
      iVar2 = iVar2 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar2 < 5);
    if (iVar3 == 0) goto LAB_80072454;
    local_1c[iVar3 + -0x38] = 1;
    if ((short)(&DAT_801ab002)[iVar7 * 6] <= (short)(&DAT_801ab002)[iVar3 * 6]) break;
    iVar4 = iVar4 + 1;
    if (4 < iVar4) {
LAB_80072454:
      if (iVar4 == 0) {
        uVar8 = 0;
      }
      *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = uVar8;
      return;
    }
  }
  uVar8 = 0;
  goto LAB_80072454;
}

