/* Analysis pseudo-C, not buildable source. */

int FUN_8007ba34(undefined1 param_1,undefined4 *param_2,undefined1 param_3,int param_4,int param_5,
                int param_6)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  undefined1 local_78;
  undefined4 uStack_77;
  int local_70 [18];
  
  iVar5 = 0;
  puVar4 = &local_78;
  do {
    *puVar4 = 0;
    *(undefined4 *)(puVar4 + 8) = 0;
    *(undefined4 *)(puVar4 + 0xc) = 0;
    iVar5 = iVar5 + 1;
    puVar4 = puVar4 + 0x10;
  } while (iVar5 < 5);
  if (param_6 != 0) {
    local_78 = 9;
  }
  uVar6 = (uint)(param_6 != 0);
  iVar7 = uVar6 + 1;
  (&local_78)[uVar6 * 0x10] = 0xe;
  *(undefined1 *)(&uStack_77 + uVar6 * 4) = param_1;
  local_70[uVar6 * 4] = (int)(&uStack_77 + uVar6 * 4);
  iVar5 = FUN_8007eca8(param_2);
  if (iVar5 < 0) {
switchD_8007bb30_caseD_4:
    iVar7 = 0;
  }
  else {
    (&local_78)[iVar7 * 0x10] = 2;
    (&uStack_77)[iVar7 * 4] = *param_2;
    local_70[iVar7 * 4] = (int)(&uStack_77 + iVar7 * 4);
    iVar5 = uVar6 + 2;
    switch(param_3) {
    case 3:
    case 6:
    case 0x1b:
      puVar4 = &local_78;
      puVar4[iVar5 * 0x10] = param_3;
      local_70[iVar5 * 4 + 1] = param_4;
      iVar5 = uVar6 + 3;
      if (8 < DAT_800f7270 + iVar5) {
        return 0;
      }
      iVar7 = DAT_80094c98 + 1;
      if (iVar7 == 0) {
        iVar7 = DAT_80094c98 + 2;
      }
      iVar9 = 0;
      DAT_80094c98 = iVar7;
      if (iVar5 != 0) {
        piVar8 = local_70 + 1;
        do {
          piVar1 = (int *)FUN_8007afa4();
          if (piVar1 == (int *)0x0) {
            return 0;
          }
          *piVar1 = iVar7;
          *(undefined1 *)(piVar1 + 1) = *puVar4;
          if (piVar8[-1] == 0) {
            piVar1[3] = 0;
          }
          else {
            FUN_8007d2bc((int)piVar1 + 5,puVar4 + 1);
            piVar1[3] = (int)piVar1 + 5;
          }
          iVar2 = *piVar8;
          piVar8 = piVar8 + 4;
          puVar4 = puVar4 + 0x10;
          iVar9 = iVar9 + 1;
          piVar1[5] = param_5;
          piVar1[4] = iVar2;
          uVar3 = FUN_80074a54(0);
          DAT_800f7270 = DAT_800f7270 + 1;
          FUN_80074a54(uVar3);
        } while (iVar9 < iVar5);
      }
      break;
    default:
      goto switchD_8007bb30_caseD_4;
    case 0x15:
    case 0x16:
      puVar4 = &local_78;
      puVar4[iVar5 * 0x10] = param_3;
      local_70[iVar5 * 4 + 1] = param_4;
      iVar5 = uVar6 + 3;
      if (8 < DAT_800f7270 + iVar5) {
        return 0;
      }
      iVar7 = DAT_80094c98 + 1;
      if (iVar7 == 0) {
        iVar7 = DAT_80094c98 + 2;
      }
      iVar9 = 0;
      DAT_80094c98 = iVar7;
      if (iVar5 != 0) {
        piVar8 = local_70 + 1;
        do {
          piVar1 = (int *)FUN_8007afa4();
          if (piVar1 == (int *)0x0) {
            return 0;
          }
          *piVar1 = iVar7;
          *(undefined1 *)(piVar1 + 1) = *puVar4;
          if (piVar8[-1] == 0) {
            piVar1[3] = 0;
          }
          else {
            FUN_8007d2bc((int)piVar1 + 5,puVar4 + 1);
            piVar1[3] = (int)piVar1 + 5;
          }
          iVar2 = *piVar8;
          piVar8 = piVar8 + 4;
          puVar4 = puVar4 + 0x10;
          iVar9 = iVar9 + 1;
          piVar1[5] = param_5;
          piVar1[4] = iVar2;
          uVar3 = FUN_80074a54(0);
          DAT_800f7270 = DAT_800f7270 + 1;
          FUN_80074a54(uVar3);
        } while (iVar9 < iVar5);
      }
    }
    iVar5 = FUN_8007c484(0);
    if ((iVar5 == 1) && ((&DAT_800f71a8)[DAT_800f726c * 6] == iVar7)) {
      FUN_8007b21c();
    }
  }
  return iVar7;
}

