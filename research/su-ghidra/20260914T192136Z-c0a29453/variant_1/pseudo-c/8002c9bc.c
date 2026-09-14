/* Analysis pseudo-C, not buildable source. */

ushort FUN_8002c9bc(undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  int *piVar9;
  ushort *puVar10;
  int local_28 [4];
  int local_18 [6];
  
  piVar9 = local_28;
  piVar3 = local_28;
  puVar10 = (ushort *)&DAT_801799d8;
  while( true ) {
    if (*puVar10 == 0) {
      return 0;
    }
    if (*puVar10 == param_2) break;
    puVar10 = puVar10 + 5;
  }
  iVar6 = 5;
  if (DAT_8009c504 != '\0') {
    iVar6 = 0x14;
  }
  puVar5 = &DAT_801a7ad8 + iVar6 * 7;
  iVar6 = 0;
  piVar2 = local_18;
  do {
    *piVar2 = 0;
    if ((*(ushort *)((int)puVar5 + 0x16) & 0x8000) != 0) {
      *piVar2 = (int)puVar5;
    }
    piVar2 = piVar2 + 1;
    iVar6 = iVar6 + 1;
    puVar5 = puVar5 + 7;
  } while (iVar6 < 5);
  iVar6 = 0;
  puVar8 = puVar10;
  do {
    puVar8 = puVar8 + 1;
    iVar7 = 0;
    piVar2 = local_18;
    while ((iVar4 = *piVar2, iVar4 == 0 || ((int)*(short *)(iVar4 + 0xc) != (uint)*puVar8))) {
      iVar7 = iVar7 + 1;
      piVar2 = piVar2 + 1;
      if (4 < iVar7) {
        return 0;
      }
    }
    *piVar9 = iVar4;
    piVar9 = piVar9 + 1;
    iVar6 = iVar6 + 1;
    *piVar2 = 0;
  } while (iVar6 < 3);
  if (param_1 != (undefined4 *)0x0) {
    iVar6 = 0;
    puVar5 = param_1;
    do {
      puVar1 = (undefined4 *)*piVar3;
      piVar3 = piVar3 + 1;
      iVar6 = iVar6 + 1;
      *puVar5 = *puVar1;
      puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    param_1[3] = 0;
  }
  return puVar10[4];
}

