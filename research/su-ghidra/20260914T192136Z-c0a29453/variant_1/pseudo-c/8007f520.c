/* Analysis pseudo-C, not buildable source. */

/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_8007f520(char *param_1,char *param_2,char *param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char cVar8;
  char ***pppcVar9;
  char ***pppcVar10;
  int iVar11;
  char *pcVar12;
  char *local_res0;
  char *local_res4;
  char *local_res8;
  undefined4 local_resc;
  undefined1 local_2a [2];
  char **local_28 [2];
  
  local_28[0] = &local_res4;
  if (((int)param_1 < 0) || (DAT_80095038 <= (int)param_1)) {
    local_res0 = DAT_8009503c;
    pcVar12 = param_1;
    if (*(int *)(&DAT_80094edc + (int)DAT_8009503c * 0x30) == 0) {
      return 0xffffffff;
    }
  }
  else {
    local_28[0] = &local_res8;
    pcVar12 = param_2;
    local_res0 = param_1;
  }
  iVar2 = (int)local_res0 * 0x30;
  if (*(int *)(&DAT_80094ed4 + iVar2) <= *(int *)(&DAT_80094ee0 + iVar2)) {
    return 0xffffffff;
  }
  cVar8 = *pcVar12;
  local_res4 = param_2;
  local_res8 = param_3;
  local_resc = param_4;
  do {
    if (cVar8 == '\0') {
      *(undefined1 *)(*(int *)(&DAT_80094edc + iVar2) + *(int *)(&DAT_80094ee0 + iVar2)) = 0;
      return *(undefined4 *)(&DAT_80094ee0 + iVar2);
    }
    if (cVar8 == '%') {
      pcVar12 = pcVar12 + 1;
      cVar8 = *pcVar12;
      iVar5 = (int)cVar8;
      iVar11 = 0;
      if (iVar5 == 0x25) goto LAB_8007f628;
      bVar1 = iVar5 != 0x30;
      while (iVar5 - 0x30U < 10) {
        iVar11 = iVar11 * 10 + -0x30 + iVar5;
        pcVar12 = pcVar12 + 1;
        iVar5 = (int)*pcVar12;
      }
      if (iVar11 < 1) {
        iVar11 = 1;
      }
      pppcVar10 = local_28;
      switch(iVar5) {
      case 0x58:
      case 0x78:
        param_2 = (char *)0x0;
        pcVar6 = *local_28[0];
        local_28[0] = local_28[0] + 1;
        do {
          do {
            pppcVar10 = (char ***)((int)pppcVar10 + -1);
            uVar3 = (uint)pcVar6 & 0xf;
            pcVar6 = (char *)((uint)pcVar6 >> 4);
            param_2 = param_2 + 1;
            *(undefined *)pppcVar10 = PTR_s_0123456789ABCDEF_80095a44[uVar3];
          } while (param_2 == (char *)0x0);
        } while (pcVar6 != (char *)0x0);
        if (bVar1) break;
        if ((int)param_2 < iVar11) {
          do {
            pppcVar10 = (char ***)((int)pppcVar10 + -1);
            param_2 = param_2 + 1;
            *(char *)pppcVar10 = '0';
          } while ((int)param_2 < iVar11);
          bVar1 = false;
          goto LAB_8007f808;
        }
        goto joined_r0x8007f850;
      case 99:
        pppcVar10 = (char ***)(local_2a + 1);
        param_2 = (char *)0x1;
        local_2a[1] = *(undefined1 *)local_28[0];
        local_28[0] = local_28[0] + 1;
        break;
      case 100:
        pcVar6 = *local_28[0];
        local_28[0] = local_28[0] + 1;
        if ((int)pcVar6 < 0) {
          pcVar6 = (char *)-(int)pcVar6;
          cVar8 = '-';
        }
        else {
          cVar8 = '\0';
        }
        param_2 = (char *)0x0;
        do {
          do {
            pppcVar9 = pppcVar10;
            pcVar7 = param_2;
            pppcVar10 = (char ***)((int)pppcVar9 + -1);
            param_2 = pcVar7 + 1;
            pcVar4 = (char *)((uint)pcVar6 / 10);
            *(char *)pppcVar10 = (char)pcVar6 + (char)pcVar4 * -10 + '0';
            pcVar6 = pcVar4;
          } while (param_2 == (char *)0x0);
        } while (pcVar4 != (char *)0x0);
        bVar1 = (int)param_2 < iVar11;
        if (cVar8 != '\0') {
          pppcVar10 = (char ***)((int)pppcVar9 + -2);
          *(char *)pppcVar10 = cVar8;
          param_2 = pcVar7 + 2;
          break;
        }
        goto LAB_8007f808;
      case 0x73:
        pppcVar10 = (char ***)*local_28[0];
        local_28[0] = local_28[0] + 1;
        param_2 = (char *)FUN_8008f948(pppcVar10);
      }
      bVar1 = (int)param_2 < iVar11;
LAB_8007f808:
      if (bVar1) {
        do {
          iVar5 = *(int *)(&DAT_80094ee0 + iVar2);
          *(undefined1 *)(*(int *)(&DAT_80094edc + iVar2) + iVar5) = 0x20;
          iVar5 = iVar5 + 1;
          *(int *)(&DAT_80094ee0 + iVar2) = iVar5;
          iVar11 = iVar11 + -1;
          if (*(int *)(&DAT_80094ed4 + iVar2) <= iVar5) {
            return 0xffffffff;
          }
        } while ((int)param_2 < iVar11);
      }
joined_r0x8007f850:
      while (param_2 = param_2 + -1, param_2 != (char *)0xffffffff) {
        iVar5 = *(int *)(&DAT_80094ee0 + iVar2);
        *(char *)(*(int *)(&DAT_80094edc + iVar2) + iVar5) = *(char *)pppcVar10;
        iVar5 = iVar5 + 1;
        *(int *)(&DAT_80094ee0 + iVar2) = iVar5;
        pppcVar10 = (char ***)((int)pppcVar10 + 1);
        if (*(int *)(&DAT_80094ed4 + iVar2) <= iVar5) {
          return 0xffffffff;
        }
      }
    }
    else {
LAB_8007f628:
      iVar5 = *(int *)(&DAT_80094ee0 + iVar2);
      *(char *)(*(int *)(&DAT_80094edc + iVar2) + iVar5) = cVar8;
      iVar5 = iVar5 + 1;
      *(int *)(&DAT_80094ee0 + iVar2) = iVar5;
      if (*(int *)(&DAT_80094ed4 + iVar2) <= iVar5) {
        return 0xffffffff;
      }
    }
    pcVar12 = pcVar12 + 1;
    cVar8 = *pcVar12;
  } while( true );
}

