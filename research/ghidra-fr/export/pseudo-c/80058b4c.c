/* Analysis pseudo-C, not buildable source. */

void FUN_80058b4c(uint param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;
  bool bVar4;
  undefined1 uVar5;
  char cVar6;
  short sVar7;
  int iVar8;
  undefined *puVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  undefined4 uVar13;
  char cVar14;
  undefined4 uVar15;
  
  iVar8 = param_1 * 0xe20;
  uVar13 = *(undefined4 *)(&DAT_800f4f60 + iVar8);
  uVar15 = (&DAT_800f4f64)[param_1 * 0x388];
  if ((&DAT_800f4f97)[iVar8] == '\0') {
    return;
  }
  DAT_8009c330 = (undefined1)param_1;
  if (-1 < (int)(&DAT_800f4e88)[param_1 * 0x388]) {
    puVar9 = PTR_DAT_8001000c;
    if (param_1 != 0) {
      puVar9 = PTR_DAT_80010010;
    }
    FUN_8004f1a8(1);
    (*(code *)(puVar9 + 4))(uVar13,0xffffffff);
    FUN_8004f1a8(0);
  }
  if (*(char *)((int)&DAT_800f4f84 + iVar8 + 2) == '\x06') {
    if (((uint)(byte)(&DAT_800f4d6d)[iVar8] == (byte)(&DAT_800f4f76)[iVar8] + 3) ||
       (uVar5 = 2, (&DAT_800f4f70)[param_1 * 0x710] == 0x309)) {
      uVar5 = 7;
    }
    *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = uVar5;
  }
  cVar14 = *(char *)((int)&DAT_800f4f84 + iVar8 + 2);
  if (cVar14 == '\x02') {
    return;
  }
  if (*(int *)(&DAT_800f4178 + (uint)(byte)(&DAT_800f4f76)[iVar8] * 4 + iVar8 + 0xd08) < 0) {
    if ((uint)(byte)(&DAT_800f4d6d)[iVar8] == (byte)(&DAT_800f4f76)[iVar8] + 3) {
      if (*(ushort *)(&DAT_800f4178 + (uint)(byte)(&DAT_800f4d6d)[iVar8] * 0x76 + iVar8 + 0x7c4) >>
          1 <= (ushort)(&DAT_800f4f7e)[param_1 * 0x710] >> 4) {
        uVar10 = param_1 ^ 1;
        if ((&DAT_800f4f77)[uVar10 * 0xe20] == '\0') {
          uVar2 = (&DAT_800f4e70)[param_1 * 0x710];
          uVar13 = 5;
          if ((ushort)(&DAT_800f4e70)[uVar10 * 0x710] < uVar2) {
            uVar13 = 6;
          }
          if ((uVar2 == (&DAT_800f4e70)[uVar10 * 0x710]) && (param_1 != 0)) {
            uVar13 = 6;
          }
        }
        else {
          uVar13 = 8;
          if ((ushort)(&DAT_800f4e72)[uVar10 * 0x710] < (ushort)(&DAT_800f4e70)[param_1 * 0x710]) {
            uVar13 = 6;
          }
        }
        FUN_8005ac78(param_1 ^ 1,uVar13,1);
        *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = 2;
      }
    }
    else if (cVar14 == '\b') {
      *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = 2;
    }
    uVar5 = 8;
    if (*(char *)((int)&DAT_800f4f84 + iVar8 + 2) != '\a') {
      return;
    }
LAB_80059268:
    *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = uVar5;
    return;
  }
  puVar9 = PTR_DAT_80010014;
  if (param_1 != 0) {
    puVar9 = PTR_DAT_80010018;
  }
  if (*(char *)((int)&DAT_800f4f84 + iVar8 + 2) == '\a') {
    FUN_8004f1a8(1);
    (*(code *)(puVar9 + 4))
              (uVar15,*(int *)(&DAT_800f4178 +
                              (uint)(byte)(&DAT_800f4f76)[iVar8] * 4 + iVar8 + 0xd08) % 1000);
    FUN_8004f1a8(0);
    *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = 8;
    *(undefined2 *)(&DAT_800f4f80 + iVar8) = 0;
  }
  if ((((((uint)(byte)(&DAT_800f4d6d)[iVar8] != (byte)(&DAT_800f4f76)[iVar8] + 3) &&
        ((&DAT_800f4f70)[param_1 * 0x710] != 0x309)) &&
       (cVar14 = *(char *)((int)&DAT_800f4f84 + iVar8 + 2), cVar14 != '\0')) &&
      ((cVar14 != '\x03' && (cVar14 != '\x01')))) && ((cVar14 != '\x04' && (cVar14 != '\x05')))) {
    return;
  }
  uVar10 = param_1 ^ 1;
  iVar11 = uVar10 * 0xe20;
  if ((&DAT_800f4f77)[iVar11] == '\0') {
    uVar2 = (&DAT_800f4e70)[param_1 * 0x710];
    uVar12 = 5;
    if ((ushort)(&DAT_800f4e70)[uVar10 * 0x710] < uVar2) {
      uVar12 = 6;
    }
    if ((uVar2 == (&DAT_800f4e70)[uVar10 * 0x710]) && (uVar12 = uVar12 | 0x80, param_1 != 0)) {
      uVar12 = 6;
    }
  }
  else {
    uVar12 = 8;
    if ((ushort)(&DAT_800f4e72)[uVar10 * 0x710] < (ushort)(&DAT_800f4e70)[param_1 * 0x710]) {
      uVar12 = 6;
    }
  }
  FUN_8004f1a8(1);
  uVar5 = (*(code *)(puVar9 + 4))(uVar15,0xffffffff);
  *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = uVar5;
  FUN_8004f1a8(0);
  switch(*(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2)) {
  case 0:
    FUN_8007f520(s_CONTINUE_800114a0);
    break;
  case 1:
  case 4:
switchD_80058e48_caseD_1:
    sVar7 = FUN_8005bf24();
    uVar12 = param_1 ^ 1;
    bVar1 = *(byte *)((int)&DAT_800f4f84 + iVar8 + 1);
    if ((&DAT_800f4f77)[uVar12 * 0xe20] == '\0') {
      uVar2 = (&DAT_800f4e70)[param_1 * 0x710];
      cVar14 = '\x05';
      if ((ushort)(&DAT_800f4e70)[uVar12 * 0x710] < uVar2) {
        cVar14 = '\x06';
      }
      if ((uVar2 == (&DAT_800f4e70)[uVar12 * 0x710]) && (param_1 != 0)) {
        cVar14 = '\x06';
      }
    }
    else {
      cVar14 = '\b';
      if ((ushort)(&DAT_800f4e72)[uVar12 * 0x710] < (ushort)(&DAT_800f4e70)[param_1 * 0x710]) {
        cVar14 = '\x06';
      }
    }
    bVar4 = false;
    if (*(char *)((int)&DAT_800f4f84 + iVar8 + 2) == '\x01') {
      FUN_8007f520(&DAT_8009c3d0);
    }
    if (((*(char *)((int)&DAT_800f4f84 + iVar8 + 2) == '\x04') &&
        (FUN_8007f520(s_OUCH_8009c3d8), *(char *)((int)&DAT_800f4f84 + iVar8 + 2) == '\x04')) &&
       (cVar14 == '\x06')) {
      cVar6 = *(char *)((int)&DAT_800f4f84 + iVar11 + 3);
      if (cVar6 != '\x06') {
        cVar14 = '\x05';
        goto LAB_80059008;
      }
    }
    else {
LAB_80059008:
      cVar6 = *(char *)((int)&DAT_800f4f84 + iVar11 + 3);
    }
    if (cVar6 == cVar14) {
      if ((((&DAT_800f4f8e)[iVar11] != '#') && (0x9f < (ushort)(&DAT_800f4f7e)[uVar10 * 0x710])) &&
         (iVar8 = FUN_8008f708(), (iVar8 >> 8 & 3U) != 0)) {
        (&DAT_800f4f7e)[uVar10 * 0x710] =
             (&DAT_800f4f7e)[uVar10 * 0x710] - (ushort)bVar1 * (sVar7 + 1);
        uVar3 = (&DAT_800f4f7e)[uVar10 * 0x710];
        iVar8 = 0;
        if ((&DAT_800f4f93)[iVar11] != '\0') {
          do {
            FUN_80050d8c(&DAT_800f4178 + iVar11,iVar8,(&DAT_800f4d6d)[iVar11],uVar3);
            iVar8 = iVar8 + 1;
          } while (iVar8 < (int)(uint)(byte)(&DAT_800f4f93)[iVar11]);
        }
        iVar8 = FUN_8008f708();
        if ((iVar8 >> 8 & 1U) != 0) {
          bVar4 = true;
        }
      }
    }
    else {
      FUN_8005ac78(param_1 ^ 1,cVar14,1);
      bVar4 = true;
    }
    if (((DAT_8009c324 == '\x0f') && (bVar4)) && (cVar14 == '\b')) {
      uVar13 = 4;
      if (((int)(&DAT_801d4244)[(ushort)(&DAT_800f4f70)[uVar10 * 0x710]] >> 0x1a & 0x1fU) == 1) {
        uVar13 = 3;
      }
      FUN_80048ae8(uVar13,0xff,0);
    }
    break;
  case 2:
    FUN_8007f520(s_TERM_8009c3e0);
    break;
  case 3:
    FUN_8007f520(s_STONE_8009c3c8);
    if (uVar12 == 6) {
      (&DAT_800f4f8b)[iVar11] = 0x80;
      uVar13 = 6;
    }
    else {
      if ((uVar12 & 0x80) == 0) goto switchD_80058e48_caseD_1;
      (&DAT_800f4f8b)[iVar11] = 0xff;
      uVar13 = 5;
    }
    goto LAB_80058edc;
  case 5:
    FUN_8007f520(s_BACK_8009c3c0);
    if (*(char *)((int)&DAT_800f4f84 + iVar11 + 3) != '\x05') {
      return;
    }
    if ((ushort)(&DAT_800f4f7e)[uVar10 * 0x710] < 0x60) {
      return;
    }
    uVar13 = 1;
LAB_80058edc:
    FUN_8005ac78(param_1 ^ 1,uVar13,1);
    break;
  default:
    FUN_8007f520(s_WHY__8009c384);
    uVar5 = 2;
    goto LAB_80059268;
  }
  return;
}

