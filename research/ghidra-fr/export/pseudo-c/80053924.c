/* Analysis pseudo-C, not buildable source. */

void FUN_80053924(void)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  
  FUN_8005cbf4(1);
  bVar2 = DAT_8009c32a;
  switch((int)((DAT_8009c32a + 1) * 0x1000000) >> 0x18) {
  case 0:
    FUN_80014d38(1,s_M__mrgSU_SU_mrg_80011424,0x6e7,0x10,0,0,PTR_DAT_80010030);
    FUN_80013700();
    DAT_8009c395 = '\0';
    DAT_8009c394 = '\0';
    DAT_8009c337 = 0;
    DAT_800f4f97 = '\0';
    DAT_800f5db7 = 0;
    FUN_8005c698(0,2,0,0,0);
    FUN_8005c698(1,2,0,0,0);
    FUN_80180420();
    FUN_80180004(0);
    FUN_80049824(PTR_DAT_80010034);
    FUN_800477a4(0x7330);
    DAT_8009c32a = DAT_8009c32a + 1;
    goto switchD_80053978_default;
  case 1:
    uVar6 = (uint)DAT_8009c337;
    iVar5 = uVar6 * 0xe20;
    if ((&DAT_800f4f97)[iVar5] == '\0') {
      FUN_800536d8();
      if ((&DAT_800f4f97)[(uint)DAT_8009c337 * 0xe20] != '\0') {
        FUN_8005d020(1,0xffffffff,(uint)DAT_8009c337,0x1e);
      }
      goto switchD_80053978_default;
    }
    if (((&DAT_800f4f8d)[iVar5] & 3) == 0) {
      iVar4 = FUN_8008f708();
      uVar10 = (iVar4 >> 8) % 0x18 + 8;
      iVar4 = FUN_8008f708();
      uVar9 = (iVar4 >> 8) % 0x18 + 8;
      iVar4 = FUN_8008f708();
      bVar2 = *(byte *)(&DAT_800f4f38 + uVar6 * 0x388);
      uVar7 = (iVar4 >> 8) % 0x18 + 8;
      if (bVar2 != uVar10) {
        cVar1 = '\x01';
        if ((int)uVar10 <= (int)(uint)bVar2) {
          cVar1 = -1;
        }
        *(byte *)(&DAT_800f4f38 + uVar6 * 0x388) = bVar2 + cVar1;
      }
      bVar2 = *(byte *)((int)&DAT_800f4f38 + iVar5 + 1);
      if (bVar2 != uVar9) {
        cVar1 = '\x01';
        if ((int)uVar9 <= (int)(uint)bVar2) {
          cVar1 = -1;
        }
        *(byte *)((int)&DAT_800f4f38 + iVar5 + 1) = bVar2 + cVar1;
      }
      bVar2 = *(byte *)((int)&DAT_800f4f38 + iVar5 + 2);
      if (bVar2 != uVar7) {
        cVar1 = '\x01';
        if ((int)uVar7 <= (int)(uint)bVar2) {
          cVar1 = -1;
        }
        *(byte *)((int)&DAT_800f4f38 + iVar5 + 2) = bVar2 + cVar1;
      }
    }
    if (DAT_8009c395 == '\0') {
      FUN_800536d8(DAT_8009c337 ^ 1);
    }
    if (*(char *)((int)&DAT_800f4f84 + (uint)DAT_8009c337 * 0xe20 + 3) != '\0')
    goto switchD_80053978_default;
    iVar5 = -1;
    bVar2 = DAT_8009c32a;
    if ((uint)(byte)(&DAT_800f4f8d)[(uint)DAT_8009c337 * 0xe20] % 0x1e == 0) {
      switch((byte)(&DAT_800f4f8d)[(uint)DAT_8009c337 * 0xe20] / 0x1e) {
      case 0:
      case 2:
      case 4:
        iVar5 = 1;
        break;
      case 1:
        iVar5 = 2;
        break;
      case 3:
        iVar5 = 7;
      }
      if (iVar5 < 0) {
        bVar2 = 2;
        if ((DAT_8009c395 == '\0') &&
           (bVar2 = DAT_8009c32a, (&DAT_800f4f97)[(DAT_8009c337 ^ 1) * 0xe20] != '\0')) {
          FUN_8005d020(1,0xffffffff,DAT_8009c337 ^ 1,0x5a);
          bVar2 = DAT_8009c32a + 1;
        }
      }
      else {
        FUN_8005ac78(DAT_8009c337,iVar5,1);
        bVar2 = DAT_8009c32a;
      }
    }
    break;
  case 2:
    uVar6 = (uint)DAT_8009c337;
    iVar5 = uVar6 * 0xe20;
    if (((&DAT_800f4f8d)[iVar5] & 3) == 0) {
      pcVar8 = (char *)(&DAT_800f4f38 + uVar6 * 0x388);
      iVar4 = (uVar6 ^ 1) * 0xe20;
      if (*pcVar8 != '\0') {
        *pcVar8 = *pcVar8 + -1;
      }
      cVar1 = *(char *)((int)&DAT_800f4f38 + iVar5 + 1);
      if (cVar1 != '\0') {
        *(char *)((int)&DAT_800f4f38 + iVar5 + 1) = cVar1 + -1;
      }
      cVar1 = *(char *)((int)&DAT_800f4f38 + iVar5 + 2);
      if (cVar1 != '\0') {
        *(char *)((int)&DAT_800f4f38 + iVar5 + 2) = cVar1 + -1;
      }
      bVar2 = *(byte *)(&DAT_800f4f38 + (uVar6 ^ 1) * 0x388);
      if (bVar2 < 8) {
        *(byte *)(&DAT_800f4f38 + (uVar6 ^ 1) * 0x388) = bVar2 + 1;
      }
      bVar2 = *(byte *)((int)&DAT_800f4f38 + iVar4 + 1);
      if (bVar2 < 8) {
        *(byte *)((int)&DAT_800f4f38 + iVar4 + 1) = bVar2 + 1;
      }
      bVar2 = *(byte *)((int)&DAT_800f4f38 + iVar4 + 2);
      if (bVar2 < 8) {
        *(byte *)((int)&DAT_800f4f38 + iVar4 + 2) = bVar2 + 1;
      }
      bVar2 = DAT_8009c32a;
      if (((*pcVar8 == '\0') && (*(char *)((int)&DAT_800f4f38 + iVar5 + 1) == '\0')) &&
         (*(char *)((int)&DAT_800f4f38 + iVar5 + 2) == '\0')) {
        (&DAT_800f4f97)[(uint)DAT_8009c337 * 0xe20] = 0;
        DAT_8009c32a = 0;
        DAT_8009c337 = DAT_8009c337 ^ 1;
        bVar2 = DAT_8009c32a;
      }
    }
    break;
  case 3:
    if (((&DAT_800f4f8d)[(uint)DAT_8009c337 * 0xe20] & 3) == 0) {
      if ((char)DAT_800f4f38 != '\0') {
        DAT_800f4f38._0_1_ = (char)DAT_800f4f38 + -1;
      }
      if (DAT_800f4f38._1_1_ != '\0') {
        DAT_800f4f38._1_1_ = DAT_800f4f38._1_1_ + -1;
      }
      if (DAT_800f4f38._2_1_ != '\0') {
        DAT_800f4f38._2_1_ = DAT_800f4f38._2_1_ + -1;
      }
      if ((char)DAT_800f5d58 != '\0') {
        DAT_800f5d58._0_1_ = (char)DAT_800f5d58 + -1;
      }
      if (DAT_800f5d58._1_1_ != '\0') {
        DAT_800f5d58._1_1_ = DAT_800f5d58._1_1_ + -1;
      }
      if (DAT_800f5d58._2_1_ != '\0') {
        DAT_800f5d58._2_1_ = DAT_800f5d58._2_1_ + -1;
      }
      if (((((char)DAT_800f4f38 == '\0') && (DAT_800f4f38._1_1_ == '\0')) &&
          (DAT_800f4f38._2_1_ == '\0')) &&
         ((((char)DAT_800f5d58 == '\0' && (DAT_800f5d58._1_1_ == '\0')) &&
          (DAT_800f5d58._2_1_ == '\0')))) {
        DAT_800f5db7 = 0;
        DAT_800f4f97 = '\0';
        bVar2 = DAT_8009c32a + 1;
      }
    }
    break;
  case 4:
    FUN_80049888();
    FUN_80047acc();
    DAT_8009c32a = 0xfe;
  default:
    goto switchD_80053978_default;
  }
  DAT_8009c32a = bVar2;
  (&DAT_800f4f8d)[(uint)DAT_8009c337 * 0xe20] = (&DAT_800f4f8d)[(uint)DAT_8009c337 * 0xe20] + '\x01'
  ;
switchD_80053978_default:
  if (DAT_8009c394 == '\0') {
    uVar6 = FUN_800474cc();
    if (((uVar6 & 0x80) != 0) && (DAT_800f4f97 != '\0')) {
      DAT_8009c394 = DAT_8009c394 + '\x01';
    }
  }
  else {
    iVar5 = FUN_8018019c();
    if (((iVar5 != 0) && (DAT_8009c395 == '\0')) && (sVar3 = FUN_800474cc(), sVar3 != 0x80)) {
      DAT_8009c32a = 2;
      DAT_8009c395 = DAT_8009c395 + '\x01';
    }
  }
  return;
}

