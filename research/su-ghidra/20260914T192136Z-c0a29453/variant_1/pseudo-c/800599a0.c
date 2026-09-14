/* Analysis pseudo-C, not buildable source. */

void FUN_800599a0(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined *puVar9;
  int *piVar10;
  int iVar11;
  char cVar12;
  undefined *puVar13;
  int iVar14;
  undefined4 uVar15;
  
  iVar4 = param_1 * 0xe20;
  iVar5 = FUN_800746b8(1);
  cVar3 = (&DAT_800f4f8c)[iVar4];
  if (cVar3 == '\0') {
    return;
  }
  if (cVar3 == -1) {
    return;
  }
  switch(cVar3) {
  case '\x01':
    piVar10 = (int *)PTR_FUN_80010000;
    if ((param_1 != 0) && (piVar10 = (int *)PTR_FUN_80010004, param_1 != 1)) {
      piVar10 = (int *)PTR_DAT_80010008;
    }
    iVar8 = 0xc000;
    if (*piVar10 != 0) {
      iVar8 = *piVar10;
    }
    FUN_8004fc2c(param_1,piVar10,iVar8,0xffffffff);
    break;
  case '\x02':
    FUN_800508b0(param_1);
    break;
  case '\x03':
    FUN_80050a68(param_1);
    break;
  case '\x04':
    iVar8 = param_1 * 0xe20;
    puVar9 = &DAT_800f4178 + iVar8;
    iVar14 = 0;
    if (param_1 < 2) {
      iVar11 = 0;
      puVar13 = puVar9;
      if ((byte)(&DAT_800f4f93)[iVar8] != 0) {
        do {
          if (*(short *)(puVar13 + 0x33c) != -1) {
            iVar6 = iVar11;
            if (iVar11 < 0) {
              iVar6 = iVar11 + 7;
            }
            if (((int)(uint)(byte)puVar9[(iVar6 >> 3) + 0xbec] >>
                 (iVar11 + (iVar6 >> 3) * -8 & 0x1fU) & 1U) == 0) {
              iVar14 = iVar14 + 0xc;
            }
            else {
              iVar14 = iVar14 + 0x14;
            }
          }
          iVar11 = iVar11 + 1;
          puVar13 = puVar13 + 2;
        } while (iVar11 < (int)(uint)(byte)(&DAT_800f4f93)[iVar8]);
      }
    }
    *(int *)(&DAT_800f4f68 + iVar8) = *(int *)(&DAT_800f4f58 + iVar8) + iVar14;
    *(uint *)(&DAT_800f4f6c + iVar8) =
         *(int *)(&DAT_800f4f58 + iVar8) + iVar14 + (uint)*(ushort *)(&DAT_800f4f7a + iVar8) * 4;
    if (param_1 == 1) {
      uVar15 = 0x800;
    }
    else {
      uVar15 = 0;
    }
    FUN_8005d5cc(puVar9,0,0,0,uVar15);
    break;
  case '\x05':
    param_1 = param_1 * 0xe20;
    piVar10 = (int *)(&DAT_800f4358 + param_1);
    iVar8 = 0;
    if ((&DAT_800f4f93)[param_1] != '\0') {
      do {
        *(undefined2 *)(*piVar10 + 8) = 0xffff;
        *(undefined2 *)(*piVar10 + 0x16) = *(undefined2 *)(*piVar10 + 0x18);
        *(undefined2 *)(*piVar10 + 10) = 0xffff;
        *(undefined1 *)(*piVar10 + 0xc) = *(undefined1 *)(*piVar10 + 0x1a);
        *(undefined2 *)(*piVar10 + 0x10) = 0;
        iVar8 = iVar8 + 1;
        *(undefined1 *)(*piVar10 + 0xd) = 0x10;
        piVar10 = piVar10 + 1;
      } while (iVar8 < (int)(uint)(byte)(&DAT_800f4f93)[param_1]);
    }
    break;
  case '\x06':
    (&DAT_800f4f97)[iVar4] = 1;
    FUN_8005c1e4(param_1);
    (&DAT_800f4f97)[iVar4] = 0;
    break;
  case '\a':
    uVar7 = (uint)*(byte *)((int)&DAT_800f4f84 + param_1 * 0xe20 + 1);
    bVar1 = (&DAT_800f4f8e)[param_1 * 0xe20];
    iVar8 = uVar7 * 2;
    if (bVar1 == 0x3c) {
      iVar8 = uVar7 * -2;
LAB_80059d00:
      FUN_8005d570(param_1,iVar8);
    }
    else if (bVar1 < 0x3d) {
      if (bVar1 == 0x23) {
        iVar8 = 0;
        goto LAB_80059d00;
      }
    }
    else if (bVar1 == 0x3e) goto LAB_80059d00;
    if (1 < param_1) {
      (&DAT_800f4f97)[iVar4] = 1;
    }
    break;
  case '\b':
    FUN_8005b444(param_1,*(undefined1 *)(&DAT_800f4f84 + param_1 * 0x388),
                 *(undefined2 *)(&DAT_800f4f82 + iVar4));
    break;
  case '\t':
    iVar8 = param_1 * 0xe20;
    uVar15 = *(undefined4 *)(&DAT_800f4f60 + iVar8);
    DAT_8009c330 = (undefined1)param_1;
    if (-1 < (int)(&DAT_800f4e88)[param_1 * 0x388]) {
      puVar9 = PTR_DAT_8001000c;
      if (param_1 != 0) {
        puVar9 = PTR_DAT_80010010;
      }
      FUN_8004f1a8(1);
      (*(code *)(puVar9 + 4))(uVar15,(int)(&DAT_800f4e88)[param_1 * 0x388] % 1000);
      FUN_8004f1a8(0);
    }
    cVar3 = (&DAT_800f4d6d)[iVar8];
    *(undefined1 *)((int)&DAT_800f4f84 + iVar8 + 2) = 6;
    uVar2 = (&DAT_800f4f7e)[param_1 * 0x710];
    iVar14 = 0;
    puVar9 = &DAT_800f4178 + iVar8;
    if ((&DAT_800f4f93)[iVar8] != '\0') {
      do {
        cVar12 = (&DAT_800f4d6d)[iVar8];
        if (cVar3 != '\0') {
          *(char *)(*(int *)(puVar9 + 0x1e0) + 0xc) = cVar3;
          cVar12 = cVar3;
        }
        FUN_80050d8c(&DAT_800f4178 + iVar8,iVar14,cVar12,uVar2);
        iVar14 = iVar14 + 1;
        puVar9 = puVar9 + 4;
      } while (iVar14 < (int)(uint)(byte)(&DAT_800f4f93)[iVar8]);
    }
    if (cVar3 != '\0') {
      (&DAT_800f4d6d)[iVar8] = cVar3;
    }
    break;
  case '\n':
    if ((&DAT_800f4f95)[iVar4] == '\0') {
      FUN_80049198(param_1,&DAT_801a8000 + param_1 * 0x200);
    }
    break;
  case '\v':
    if ((&DAT_800f4f95)[iVar4] == '\0') {
      (&DAT_800f4f96)[iVar4] = 1;
    }
    (&DAT_800f4f97)[iVar4] = 1;
  }
  iVar8 = FUN_800746b8(1);
  FUN_8008fa78(s_LoadModelDO__d___03X_800114c0,(&DAT_800f4f8c)[iVar4],iVar8 - iVar5);
  cVar3 = -1;
  if ((&DAT_800f4f97)[iVar4] == '\0') {
    cVar3 = (&DAT_800f4f8c)[iVar4] + '\x01';
  }
  (&DAT_800f4f8c)[iVar4] = cVar3;
  return;
}

