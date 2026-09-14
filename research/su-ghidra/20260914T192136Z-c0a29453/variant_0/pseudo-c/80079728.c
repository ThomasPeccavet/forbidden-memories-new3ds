/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80079728(void)

{
  byte bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  byte local_20;
  byte local_18 [8];
  
  *DAT_80094bd4 = 1;
  local_20 = *DAT_80094bd8 & 7;
  uVar7 = 0;
  if (local_20 == 0) {
LAB_80079c74:
    uVar2 = 0;
  }
  else {
    while (iVar5 = 0, local_20 != (*DAT_80094bd8 & 7)) {
      local_20 = *DAT_80094bd8 & 7;
    }
    do {
      pbVar3 = local_18 + iVar5;
      iVar6 = iVar5;
      if ((*DAT_80094bd4 & 0x20) == 0) break;
      iVar5 = iVar5 + 1;
      *pbVar3 = *DAT_80094be0;
      iVar6 = iVar5;
    } while (iVar5 < 8);
    for (; iVar5 < 8; iVar5 = iVar5 + 1) {
      local_18[iVar5] = 0;
    }
    *DAT_80094bd4 = 1;
    *DAT_80094bd8 = 7;
    *DAT_80094be4 = 7;
    if ((local_20 != 3) || (*(int *)(&DAT_80094ad4 + (uint)DAT_8009492d * 4) != 0)) {
      if (((DAT_8009491c & 0x10) == 0) && ((local_18[0] & 0x10) != 0)) {
        DAT_80094924 = DAT_80094924 + 1;
      }
      DAT_8009491c = (uint)local_18[0];
      DAT_80094920 = (uint)local_18[1];
      uVar7 = DAT_8009491c & 0x1d;
    }
    if (((local_20 == 5) && (2 < DAT_80094918)) &&
       (FUN_8008fa78(s_DiskError__80011bf4), 2 < DAT_80094918)) {
      FUN_8008fa78(s_com__s_code___02x__02x__80011c00,(&PTR_s_CdlSync_80094934)[DAT_8009492d],
                   DAT_8009491c,DAT_80094920);
    }
    switch(local_20) {
    case 1:
      if ((uVar7 != 0) && (iVar6 == 1)) {
        uVar7 = 0;
      }
      DAT_80094bed = 1;
      if (uVar7 != 0) {
        DAT_80094bed = 5;
      }
      pbVar3 = &DAT_800f7138;
      pbVar4 = local_18;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      *DAT_80094bd4 = 0;
      uVar2 = 4;
      *DAT_80094bd8 = 0;
      break;
    case 2:
      DAT_80094bec = 2;
      if (uVar7 != 0) {
        DAT_80094bec = 5;
      }
      pbVar3 = &DAT_800f7130;
      pbVar4 = local_18;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      uVar2 = 2;
      break;
    case 3:
      if (uVar7 == 0) {
        if (*(int *)(&DAT_800949d4 + (uint)DAT_8009492d * 4) == 0) {
          DAT_80094bec = 2;
          pbVar3 = &DAT_800f7130;
          pbVar4 = local_18;
          iVar5 = 7;
          do {
            bVar1 = *pbVar4;
            pbVar4 = pbVar4 + 1;
            iVar5 = iVar5 + -1;
            *pbVar3 = bVar1;
            pbVar3 = pbVar3 + 1;
          } while (iVar5 != -1);
          uVar2 = 2;
        }
        else {
          DAT_80094bec = 3;
          pbVar3 = &DAT_800f7130;
          pbVar4 = local_18;
          iVar5 = 7;
          do {
            bVar1 = *pbVar4;
            pbVar4 = pbVar4 + 1;
            iVar5 = iVar5 + -1;
            *pbVar3 = bVar1;
            pbVar3 = pbVar3 + 1;
          } while (iVar5 != -1);
          uVar2 = 1;
        }
      }
      else {
        DAT_80094bec = 5;
        pbVar3 = &DAT_800f7130;
        pbVar4 = local_18;
        iVar5 = 7;
        do {
          bVar1 = *pbVar4;
          pbVar4 = pbVar4 + 1;
          iVar5 = iVar5 + -1;
          *pbVar3 = bVar1;
          pbVar3 = pbVar3 + 1;
        } while (iVar5 != -1);
        uVar2 = 2;
      }
      break;
    case 4:
      pbVar3 = &DAT_800f7140;
      DAT_80094bee = 4;
      pbVar4 = local_18;
      DAT_80094bed = 4;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      pbVar3 = &DAT_800f7138;
      pbVar4 = local_18;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      uVar2 = 4;
      break;
    case 5:
      pbVar3 = &DAT_800f7130;
      DAT_80094bed = 5;
      pbVar4 = local_18;
      DAT_80094bec = 5;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      pbVar3 = &DAT_800f7138;
      pbVar4 = local_18;
      iVar5 = 7;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
        *pbVar3 = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (iVar5 != -1);
      uVar2 = 6;
      break;
    default:
      FUN_80090cf8(s_CDROM__unknown_intr_80011c1c);
      FUN_8008fa78(s___d__80011c30,local_20);
      goto LAB_80079c74;
    }
  }
  return uVar2;
}

