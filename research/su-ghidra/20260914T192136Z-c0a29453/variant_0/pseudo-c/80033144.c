/* Analysis pseudo-C, not buildable source. */

void FUN_80033144(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar8 = DAT_8009c684;
  iVar9 = (int)*(short *)((int)param_1 + 0x2d42);
  switch(*(undefined1 *)((int)param_1 + 0x2d45)) {
  case 1:
    if (*(char *)((int)param_1 + 0x2d47) == '\0') {
      iVar8 = 0;
      puVar6 = param_1;
      if (0 < iVar9) {
        do {
          iVar8 = iVar8 + 1;
          *puVar6 = (int)(short)puVar6[1];
          puVar6 = puVar6 + 4;
        } while (iVar8 < iVar9);
      }
    }
    else {
      iVar8 = 0;
      if (0 < iVar9) {
        puVar3 = param_1 + 1;
        puVar6 = param_1;
        do {
          *puVar6 = 0xffff;
          if (*(char *)((int)puVar3 + 9) != '\0') {
            *puVar6 = (int)(short)*puVar3;
          }
          iVar8 = iVar8 + 1;
          puVar3 = puVar3 + 4;
          puVar6 = puVar6 + 4;
        } while (iVar8 < iVar9);
      }
    }
    break;
  case 2:
    iVar8 = 0;
    puVar6 = param_1;
    if (0 < iVar9) {
      do {
        *puVar6 = 0xffffffff;
        if (*(char *)((int)puVar6 + 0xd) != '\0') {
          *puVar6 = 0;
        }
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
    break;
  case 3:
    iVar8 = 0;
    if (0 < iVar9) {
      puVar3 = param_1 + 1;
      puVar6 = param_1;
      do {
        *puVar6 = 0;
        if (*(char *)((int)puVar3 + 9) != '\0') {
          uVar4 = (&DAT_801d4244)[(short)*puVar3 + -1] & 0x1ff;
          uVar1 = (int)(&DAT_801d4244)[(short)*puVar3 + -1] >> 9 & 0x1ff;
          uVar2 = uVar1;
          if (uVar1 * 10 <= uVar4 * 10) {
            uVar2 = uVar4;
            uVar4 = uVar1;
          }
          *puVar6 = uVar2 * 0xa0000 | uVar4 * 0x28 | 1;
        }
        puVar3 = puVar3 + 4;
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
    puVar5 = &LAB_8003305c;
    goto LAB_80033584;
  case 4:
    iVar8 = 0;
    if (0 < iVar9) {
      puVar3 = param_1 + 1;
      puVar6 = param_1;
      do {
        *puVar6 = 0;
        if (*(char *)((int)puVar3 + 9) != '\0') {
          *puVar6 = ((&DAT_801d4244)[(short)*puVar3 + -1] & 0x1ff) * 0xa0000 |
                    ((int)(&DAT_801d4244)[(short)*puVar3 + -1] >> 9 & 0x1ffU) * 0x28 | 1;
        }
        puVar3 = puVar3 + 4;
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
    puVar5 = &LAB_8003305c;
    goto LAB_80033584;
  case 5:
    iVar8 = 0;
    if (0 < iVar9) {
      puVar3 = param_1 + 1;
      puVar6 = param_1;
      do {
        *puVar6 = 0;
        if (*(char *)((int)puVar3 + 9) != '\0') {
          *puVar6 = ((int)(&DAT_801d4244)[(short)*puVar3 + -1] >> 9 & 0x1ffU) * 0xa0000 |
                    ((&DAT_801d4244)[(short)*puVar3 + -1] & 0x1ff) * 0x28 | 1;
        }
        puVar3 = puVar3 + 4;
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
    puVar5 = &LAB_8003305c;
    goto LAB_80033584;
  case 6:
    iVar8 = 0;
    if (0 < iVar9) {
      puVar3 = param_1 + 1;
      puVar6 = param_1;
      do {
        *puVar6 = 0xffffffff;
        if (*(char *)((int)puVar3 + 9) != '\0') {
          *puVar6 = (int)(&DAT_801d4244)[(short)*puVar3 + -1] >> 0x1a & 0x1f;
        }
        puVar3 = puVar3 + 4;
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
    break;
  default:
    goto switchD_80033194_caseD_7;
  case 8:
    iVar7 = 0;
    if (0 < iVar9) {
      puVar3 = param_1 + 1;
      puVar6 = param_1;
      do {
        *puVar6 = 0xffffffff;
        if (*(char *)((int)puVar3 + 9) != '\0') {
          *puVar6 = 0x100;
          uVar2 = (uint)*(byte *)(iVar8 + (short)*puVar3 + 0x606a);
          if (uVar2 != 0) {
            *puVar6 = uVar2;
          }
        }
        puVar3 = puVar3 + 4;
        iVar7 = iVar7 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar7 < iVar9);
    }
    break;
  case 9:
    iVar9 = (int)(short)param_1[0xb50];
    iVar8 = 0;
    puVar6 = param_1;
    if (0 < iVar9) {
      do {
        *puVar6 = 0xffffffff;
        if (*(char *)((int)puVar6 + 0xd) != '\0') {
          uVar2 = FUN_80035dfc(0x1000);
          *puVar6 = uVar2;
        }
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar8 < iVar9);
    }
  }
  puVar5 = &LAB_800330d0;
LAB_80033584:
  FUN_8008f578(param_1,iVar9,0x10,puVar5);
switchD_80033194_caseD_7:
  FUN_800321d8(param_1,9);
  return;
}

