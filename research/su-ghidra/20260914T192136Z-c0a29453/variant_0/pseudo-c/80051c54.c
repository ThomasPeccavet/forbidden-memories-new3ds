/* Analysis pseudo-C, not buildable source. */

void FUN_80051c54(void)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  undefined *puVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  code *local_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  
  local_28[0] = (code *)PTR_FUN_80011414;
  local_28[1] = (code *)PTR_FUN_80011418;
  local_28[2] = (code *)PTR_FUN_8001141c;
  local_28[3] = (code *)PTR_FUN_80011420;
  iVar12 = 1;
  if (((int)(&DAT_801d4244)[DAT_800f5d90] >> 0x1a & 0x1fU) == 1) {
    iVar12 = 2;
  }
  switch((int)((DAT_8009c32a + 1) * 0x1000000) >> 0x18) {
  default:
    goto switchD_80051cfc_caseD_0;
  case 1:
    FUN_8005c6d0(2,0xfffff000,0xfffff000,0xfffff000);
    FUN_8005c698(0,5,0,0,0);
    FUN_8005c698(1,5,0,0,0);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 2:
    FUN_800477a4(DAT_8009c326);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 3:
    local_18 = DAT_8009c37c;
    local_14 = DAT_8009c380;
    uVar10 = 0x78;
    switch(PTR_DAT_8009c318[0xa0]) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
      FUN_8004f28c(2,10,0);
      break;
    case 2:
      puVar4 = (undefined2 *)FUN_8004f1b4(10);
      FUN_8004f3c8(2,100,(short)puVar4[1] + 0x800,0xfffffc00,0);
      local_18 = CONCAT22(0xf000,*puVar4);
      uVar10 = 0x96;
      local_14 = CONCAT22(local_14._2_2_,puVar4[2] + 0x400);
    }
    FUN_8004f92c(0,&local_18,0,uVar10);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 4:
    if (DAT_800f6b58 < 0x800) {
      FUN_8005c38c(2,3);
      DAT_800f6b58 = DAT_800f6b58 + 0x40;
      DAT_800f6b60 = DAT_800f6b60 + 0x40;
      DAT_800f6b5c = DAT_800f6b5c + 0x40;
      goto switchD_80051cfc_caseD_0;
    }
    iVar12 = FUN_8004fb18(2);
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    FUN_8005cfc4(0);
    FUN_8004f598(1);
    FUN_8004f5d8(0,0,0,0xfffffff4);
    FUN_8004f724(0,0,0x4000);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 5:
    if (((DAT_800f4f97 == '\0') || (iVar12 = FUN_8004fb24(), iVar12 == 0)) ||
       (*(short *)(iVar12 + 6) != 2)) goto switchD_80051cfc_caseD_0;
    FUN_8004f598(1);
    FUN_8004f5d8(0,0,0,0xfffffff4);
    FUN_8004f724(0,0,0x4000);
    DAT_8009c330 = 0;
    (*local_28[0])(DAT_800f4f64,0);
    DAT_800f4f8d = '\0';
    bVar2 = DAT_8009c32a + 1;
    break;
  case 6:
    puVar9 = &DAT_800f4178;
    if (DAT_800f4f8d == '\0') {
      DAT_8009c330 = 0;
      iVar12 = (*(code *)PTR_FUN_80011414)(DAT_800f4f64,0xffffffff);
      if (iVar12 != 2) goto switchD_80051cfc_caseD_0;
      DAT_800f4f8d = DAT_800f4f8d + '\x01';
    }
    if (-1 < (char)DAT_800f4f38) {
      cVar3 = DAT_800f4f38._1_1_ + '\x02';
      cVar7 = DAT_800f4f38._2_1_ + '\x02';
      DAT_800f4f38._0_1_ = (char)DAT_800f4f38 + '\x02';
LAB_800529cc:
      puVar9[0xdc1] = cVar3;
      puVar9[0xdc2] = cVar7;
      goto switchD_80051cfc_caseD_0;
    }
    if (DAT_800f4f89 != '\x04') {
      FUN_8005c38c(0,3);
    }
    FUN_8005c698(0,0,0x80,0x80,0x80);
    FUN_8005c698(1,0,0x80,0x80,0x80);
    FUN_8005ac78(0,2,1);
    DAT_8009c379 = 0;
    bVar2 = DAT_8009c32a + 1;
    break;
  case 7:
    if (DAT_800f4f89 != '\x04') {
      FUN_8005c38c(0,3);
    }
    if (DAT_800f4f84._3_1_ != '\0') goto switchD_80051cfc_caseD_0;
    cVar3 = FUN_8005bf24();
    DAT_8009c379 = DAT_8009c379 + cVar3;
    if ((DAT_8009c379 < 0x3c) || (DAT_800f5db7 == '\0')) goto switchD_80051cfc_caseD_0;
    FUN_8004f598(1);
    FUN_8004f5d8(1,0,0,0xfffffff6);
    FUN_8004f724(1,1,0x4000);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 8:
    if (DAT_800f4f89 != '\x04') {
      FUN_8005c38c(0,3);
    }
    iVar12 = FUN_8004fb24();
    if ((iVar12 == 0) || (*(short *)(iVar12 + 6) != 2)) goto switchD_80051cfc_caseD_0;
    FUN_8004f28c(1,0,0);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 9:
    if (-1 < (char)DAT_800f5d58) {
      DAT_800f5d58._0_1_ = (char)DAT_800f5d58 + '\x02';
      DAT_800f5d58._1_1_ = DAT_800f5d58._1_1_ + '\x02';
      DAT_800f5d58._2_1_ = DAT_800f5d58._2_1_ + '\x02';
      goto switchD_80051cfc_caseD_0;
    }
    FUN_8005ac78(1,2,1);
    DAT_8009c379 = 0;
    bVar2 = DAT_8009c32a + 1;
    break;
  case 10:
    if (DAT_800f5da4._3_1_ != '\0') goto switchD_80051cfc_caseD_0;
    cVar3 = FUN_8005bf24();
    DAT_8009c379 = DAT_8009c379 + cVar3;
    if (DAT_8009c379 < 0x3c) goto switchD_80051cfc_caseD_0;
    bVar2 = *(byte *)((int)&DAT_800f4e78 + DAT_800f4f76 + 2) & 0x1f;
    uVar10 = 0xffffffec;
    if (bVar2 == 1) {
      uVar11 = 0;
LAB_80052234:
      bVar1 = uVar11 < 2;
    }
    else {
      if (bVar2 < 2) {
        uVar11 = 3;
        goto LAB_80052234;
      }
      if (bVar2 == 2) {
        uVar11 = 1;
        goto LAB_80052234;
      }
      uVar11 = 3;
      if (bVar2 == 3) {
        uVar11 = 2;
        goto LAB_80052234;
      }
      bVar1 = false;
    }
    if (bVar1) {
      uVar10 = 0xfffffff6;
    }
    FUN_8004f5d8(0,uVar11,0,uVar10);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0xb:
    iVar12 = FUN_8004fb18();
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    FUN_8005d020(1,0xffffffff,0,0xffffffe2);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0xc:
    iVar8 = FUN_8005d980(1);
    if (iVar8 == 0) goto switchD_80051cfc_caseD_0;
    iVar6 = FUN_8005d720(0);
    iVar5 = FUN_8005bf24();
    iVar8 = DAT_8009c7fa - iVar6;
    if (iVar8 < 0) {
      iVar8 = iVar6 - DAT_8009c7fa;
    }
    if ((iVar5 + 2) * 8 < iVar8) goto switchD_80051cfc_caseD_0;
    FUN_80054078(0);
    DAT_8009c330 = 1;
    (*local_28[iVar12])(DAT_800f5d84,0x18e);
    DAT_800f5dad = -1;
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0xd:
    if (DAT_800f5da4._3_1_ == '\x05') {
      iVar8 = 1;
    }
    else if (DAT_800f5da4._3_1_ == '\x06') {
      iVar8 = 2;
    }
    else {
      iVar8 = 0;
      if (DAT_800f5da4._3_1_ == '\b') {
        iVar8 = 3;
      }
    }
    if ((DAT_800f5dad == -1) && (DAT_800f5da4._3_1_ == '\b')) {
      DAT_800f5dad = '\0';
    }
    if (DAT_800f5dad == '\0') {
      DAT_8009c330 = 1;
      (*local_28[iVar12])(DAT_800f5d84,0xffffffff);
    }
    if (DAT_800f4f84._2_1_ == '\x02') {
      if (DAT_800f4f84._3_1_ == '\0') {
        iVar8 = 4;
      }
    }
    else {
      iVar12 = FUN_8004f184();
      if (iVar12 == 0) {
        iVar8 = 0;
      }
    }
    if (iVar8 == 0) goto switchD_80051cfc_caseD_0;
    iVar12 = FUN_8005d3e8(1);
    iVar12 = (iVar12 * 0x1e) / 1000;
    iVar8 = FUN_8004f184();
    if (iVar8 == 2) {
      FUN_8004f190(1);
    }
    FUN_8004f92c(0,0,0,0);
    if (iVar12 < 10) {
      iVar12 = 10;
    }
    FUN_8005d020(1,0xffffffff,1,iVar12);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0xe:
    bVar2 = 0x14;
    if (DAT_800f5da4._3_1_ != '\x06') {
      if (DAT_800f5dad == '\0') {
        DAT_8009c330 = 1;
        (*local_28[iVar12])(DAT_800f5d84,0xffffffff);
      }
      iVar12 = FUN_8005d980(1);
      if ((((iVar12 == 0) || (iVar12 = FUN_8004fb18(), iVar12 == 0)) ||
          ((DAT_800f4f84 & 0xffff0000) != 0x20000)) || ((DAT_800f5da4 & 0xffff0000) != 0x20000))
      goto switchD_80051cfc_caseD_0;
      if (DAT_800f5d97 == '\0') {
        bVar2 = DAT_8009c32a + 1;
      }
      else {
        FUN_8005d1e4(0x78);
        bVar2 = 0x1e;
      }
    }
    break;
  case 0xf:
    iVar12 = FUN_8004fb18();
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    FUN_8005d020(1,0xffffffff,1,0xffffffe2);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x10:
    iVar12 = FUN_8005d980(1);
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    iVar8 = FUN_8005d720(1);
    iVar6 = FUN_8005bf24();
    iVar12 = DAT_8009c7fa - iVar8;
    if (iVar12 < 0) {
      iVar12 = iVar8 - DAT_8009c7fa;
    }
    if ((iVar6 + 2) * 8 < iVar12) goto switchD_80051cfc_caseD_0;
    FUN_80054078(1);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x11:
    if (DAT_800f4f84._3_1_ == '\x05') {
      iVar12 = 1;
    }
    else if (DAT_800f4f84._3_1_ == '\x06') {
      iVar12 = 2;
    }
    else {
      iVar12 = 0;
      if (DAT_800f4f84._3_1_ == '\b') {
        iVar12 = 3;
      }
    }
    if (DAT_800f5da4._2_1_ == '\x02') {
      if (DAT_800f5da4._3_1_ == '\0') {
        iVar12 = 4;
      }
    }
    else {
      iVar8 = FUN_8004f184();
      if (iVar8 == 0) {
        iVar12 = 0;
      }
    }
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    iVar12 = FUN_8005d3e8(0);
    iVar12 = (iVar12 * 0x1e) / 1000;
    iVar8 = FUN_8004f184();
    if (iVar8 == 2) {
      FUN_8004f190(1);
    }
    FUN_8004f92c(0,0,0,0);
    if (iVar12 < 10) {
      iVar12 = 10;
    }
    FUN_8005d020(1,0xffffffff,0,iVar12);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x12:
    bVar2 = 0x14;
    if (DAT_800f4f84._3_1_ != '\x06') {
      iVar12 = FUN_8005d980(1);
      if (((iVar12 != 0) && (iVar12 = FUN_8004fb18(), iVar12 != 0)) &&
         (((DAT_800f4f84 & 0xffff0000) == 0x20000 && ((DAT_800f5da4 & 0xffff0000) == 0x20000)))) {
        FUN_8007f520(s_WHY__8009c384);
      }
      goto switchD_80051cfc_caseD_0;
    }
    break;
  case 0x15:
    uVar11 = (uint)(DAT_800f4f84._3_1_ != '\x06');
    iVar12 = (uVar11 ^ 1) * 0xe20;
    if (((*(char *)((int)&DAT_800f4f84 + iVar12 + 2) != '\x02') ||
        (*(char *)((int)&DAT_800f4f84 + iVar12 + 3) != '\0')) ||
       ((&DAT_800f4f8e)[uVar11 * 0xe20] != '#')) goto switchD_80051cfc_caseD_0;
    if ((DAT_800f5d97 == '\0') && (DAT_800f4e70 == DAT_800f5c90)) {
      if (DAT_800f5dab == -1) {
        DAT_800f5dab = -0x80;
      }
      FUN_8005ac78(1,6,1);
    }
    FUN_8004f92c(0,0,0,0);
    iVar12 = FUN_8005d980(1);
    if (iVar12 != 0) {
      iVar12 = FUN_8005d3e8(uVar11);
      iVar12 = (iVar12 * 0x1e) / 1000;
      if (iVar12 < 10) {
        iVar12 = 10;
      }
      FUN_8005d020(1,0xffffffff,uVar11,-iVar12);
    }
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x16:
    bVar1 = DAT_800f4f84._3_1_ != '\x06';
    uVar11 = (uint)bVar1;
    if (((&DAT_800f4f8b)[uVar11 * 0xe20] != '\0') || (iVar12 = FUN_8005d980(1), iVar12 == 0))
    goto switchD_80051cfc_caseD_0;
    FUN_8005c698(uVar11,5,0x80,0x80,0x80);
    DAT_8009c330 = bVar1;
    (*local_28[3])((&DAT_800f4f64)[uVar11 * 0x388],0);
    (&DAT_800f4f8d)[uVar11 * 0xe20] = 0;
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x17:
    uVar11 = (uint)(DAT_800f4f84._3_1_ != '\x06');
    iVar12 = uVar11 * 0xe20;
    puVar9 = &DAT_800f4178 + iVar12;
    if ((&DAT_800f4f8d)[iVar12] == '\0') {
      DAT_8009c330 = DAT_800f4f84._3_1_ != '\x06';
      iVar8 = (*(code *)PTR_FUN_80011420)((&DAT_800f4f64)[uVar11 * 0x388],0xffffffff);
      if (iVar8 != 2) goto switchD_80051cfc_caseD_0;
      (&DAT_800f4f8d)[iVar12] = (&DAT_800f4f8d)[iVar12] + '\x01';
    }
    if (*(char *)(&DAT_800f4f38 + uVar11 * 0x388) != '\0') {
      *(char *)(&DAT_800f4f38 + uVar11 * 0x388) = *(char *)(&DAT_800f4f38 + uVar11 * 0x388) + -2;
      cVar3 = *(char *)((int)&DAT_800f4f38 + iVar12 + 1) + -2;
      cVar7 = *(char *)((int)&DAT_800f4f38 + iVar12 + 2) + -2;
      goto LAB_800529cc;
    }
    iVar8 = (int)DAT_8009c7fa;
    iVar12 = iVar8 + 0xc00;
    if (uVar11 == 0) {
      iVar12 = iVar8 + 0x400;
      iVar6 = iVar12;
      if (iVar12 < 0) {
        iVar6 = iVar8 + 0x13ff;
      }
    }
    else {
      iVar6 = iVar12;
      if (iVar12 < 0) {
        iVar6 = iVar8 + 0x1bff;
      }
    }
    if (0xbfe < (iVar12 + (iVar6 >> 0xc) * -0x1000) - 0x201U) goto switchD_80051cfc_caseD_0;
    iVar12 = FUN_8005d3e8(uVar11 ^ 1);
    iVar12 = (iVar12 * 0x1e) / 1000;
    if (iVar12 < 0x1e) {
      iVar12 = 0x1e;
    }
    FUN_8005d020(1,0xffffffff,uVar11 ^ 1,-iVar12);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x18:
    bVar1 = DAT_800f4f84._3_1_ == '\x06';
    iVar12 = FUN_8004fb18();
    if (((iVar12 == 0) ||
        (iVar8 = (int)DAT_8009c7f8, iVar12 = FUN_8004f1c8(bVar1,700), iVar12 + 10 < iVar8)) ||
       (iVar12 = FUN_8005d980(1), iVar12 == 0)) goto switchD_80051cfc_caseD_0;
    if ((DAT_800f4e70 == DAT_800f5c90) && (DAT_800f5d97 == '\0')) {
      DAT_8009c330 = 1;
      (*local_28[3])(DAT_800f5d84,0);
      DAT_800f5dad = '\0';
      DAT_8009c32a = 0x19;
      DAT_8009c379 = 0;
      goto switchD_80051cfc_caseD_0;
    }
    FUN_8004f724(0xffffffff,bVar1,0x4000);
    FUN_8005d118(0xffffffff,bVar1);
    FUN_8005ac78(bVar1,7,1);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x19:
    bVar1 = DAT_800f4f84._3_1_ == '\x06';
    if (*(char *)((int)&DAT_800f4f84 + (uint)bVar1 * 0xe20 + 3) == '\a')
    goto switchD_80051cfc_caseD_0;
    FUN_8004f92c(0,0,0,0);
    FUN_8005d020(1,0xffffffff,(uint)bVar1,0xffffffe2);
    DAT_8009c379 = 0x3c;
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x1a:
    bVar1 = DAT_800f4f84._3_1_ == '\x06';
    if (((&DAT_800f4f8b)[(uint)bVar1 * 0xe20] != '\0') || (iVar12 = FUN_8005d980(1), iVar12 == 0))
    goto switchD_80051cfc_caseD_0;
    cVar3 = FUN_8005bf24();
    DAT_8009c379 = DAT_8009c379 + cVar3;
    if (DAT_8009c379 < 0x3c) goto switchD_80051cfc_caseD_0;
    FUN_8005c698((uint)bVar1,5,0x80,0x80,0x80);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x1b:
    bVar1 = DAT_800f4f84._3_1_ == '\x06';
    if (((DAT_800f4e70 == DAT_800f5c90) && (DAT_800f5d97 == '\0')) && (DAT_800f5dad == '\0')) {
      DAT_8009c330 = 1;
      iVar12 = (*(code *)PTR_FUN_80011420)(DAT_800f5d84,0xffffffff);
      if (iVar12 != 2) goto switchD_80051cfc_caseD_0;
      DAT_800f5dad = DAT_800f5dad + '\x01';
    }
    puVar9 = &DAT_800f4178 + (uint)bVar1 * 0xe20;
    cVar3 = *(char *)(&DAT_800f4f38 + (uint)bVar1 * 0x388);
    if (cVar3 != '\0') {
LAB_80052ee0:
      puVar9[0xdc0] = cVar3 + -2;
      puVar9[0xdc1] = puVar9[0xdc1] + -2;
      puVar9[0xdc2] = puVar9[0xdc2] + -2;
      goto switchD_80051cfc_caseD_0;
    }
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x1c:
    iVar12 = FUN_8005d980(1);
    bVar2 = 0x28;
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    break;
  case 0x1f:
    if (DAT_800f5dad == '\0') {
      DAT_8009c330 = 1;
      iVar12 = (*local_28[iVar12])(DAT_800f5d84,0xfffffffe);
      if (iVar12 == 2) {
        DAT_800f5dad = DAT_800f5dad + '\x01';
      }
      goto switchD_80051cfc_caseD_0;
    }
    iVar12 = FUN_8005d980(1);
    if (iVar12 == 0) goto switchD_80051cfc_caseD_0;
    FUN_8005c698(1,5,0x80,0x80,0x80);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x20:
    if ((char)DAT_800f5d58 != '\0') {
      DAT_800f5d58._1_1_ = DAT_800f5d58._1_1_ + -2;
      DAT_800f5d58._2_1_ = DAT_800f5d58._2_1_ + -2;
      DAT_800f5d58._0_1_ = (char)DAT_800f5d58 + -2;
      goto switchD_80051cfc_caseD_0;
    }
    iVar8 = DAT_8009c7fa + 0xc00;
    iVar12 = iVar8;
    if (iVar8 < 0) {
      iVar12 = DAT_8009c7fa + 0x1bff;
    }
    if (0xbfe < (iVar8 + (iVar12 >> 0xc) * -0x1000) - 0x201U) goto switchD_80051cfc_caseD_0;
    iVar12 = FUN_8005d3e8(0);
    iVar12 = (iVar12 * 0x1e) / 1000;
    if (iVar12 < 0x1e) {
      iVar12 = 0x1e;
    }
    FUN_8005d020(1,0xffffffff,0,-iVar12);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x21:
    iVar12 = FUN_8004fb18();
    if ((iVar12 == 0) || (iVar12 = FUN_8005d980(1), iVar12 == 0)) goto switchD_80051cfc_caseD_0;
    FUN_8005c698(0,5,0x80,0x80,0x80);
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x22:
    puVar9 = &DAT_800f4178;
    cVar3 = (char)DAT_800f4f38;
    if ((char)DAT_800f4f38 != '\0') goto LAB_80052ee0;
    bVar2 = 0x28;
    break;
  case 0x29:
    FUN_8005c38c(2,3);
    FUN_80015820();
    bVar2 = DAT_8009c32a + 1;
    break;
  case 0x2a:
    FUN_8005c38c(2,3);
    if ((DAT_800eb24e & 0x80) != 0) goto switchD_80051cfc_caseD_0;
    FUN_80047acc();
    bVar2 = 0xfe;
  }
  DAT_8009c32a = bVar2;
switchD_80051cfc_caseD_0:
  FUN_8005d290(1);
  return;
}

