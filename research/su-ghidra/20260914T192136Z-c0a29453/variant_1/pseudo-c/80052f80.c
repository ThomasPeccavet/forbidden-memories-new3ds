/* Analysis pseudo-C, not buildable source. */

void FUN_80052f80(void)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  code *pcVar4;
  code *pcVar5;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = DAT_8009c38c;
  local_1c = DAT_8009c390;
  pcVar4 = (code *)(PTR_DAT_80010014 + 4);
  pcVar5 = (code *)(PTR_DAT_80010018 + 4);
  FUN_8005cbf4(1);
  if ((DAT_8009c32a - 8 < 2) && (DAT_800f4f8d == '\0')) {
    DAT_8009c330 = 0;
    iVar2 = (*pcVar4)(PTR_DAT_80010024,0xffffffff);
    if (iVar2 == 2) {
      DAT_800f4f8d = DAT_800f4f8d + '\x01';
    }
  }
  if (('\t' < (char)DAT_8009c32a) && (DAT_800f5dad == '\0')) {
    DAT_8009c330 = 0;
    iVar2 = (*pcVar5)(PTR_DAT_80010028,0xffffffff);
    if (iVar2 == 2) {
      FUN_8005c808(0,0);
      FUN_800155f8();
      DAT_8009c32a = 0xf;
    }
  }
  switch((int)((DAT_8009c32a + 1) * 0x1000000) >> 0x18) {
  case 0:
    if (DAT_800f4f8c == -1) {
      if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
        FUN_8005967c(0,0x309,0,0,0,0,4);
      }
    }
    else {
      FUN_800599a0(0);
    }
    if (DAT_800f4f97 != '\0') {
      FUN_8004f3c8(0,10000,0xe00,0,0);
      FUN_8005c8d0(0,1,0);
      if (DAT_800f4f84._3_1_ != '\0') {
        FUN_8005ac78(0,0,0);
      }
      FUN_8005c808(0,1);
      FUN_8005c698(0,5,0,0,0);
      DAT_800f4d6e = 1;
      DAT_800f4d6c = 2;
      FUN_800477a4(0x7310);
      DAT_800f4e80 = 0xffffffff;
      DAT_800f4e84 = 0xffffffff;
      DAT_800f4e88 = 0xffffffff;
      DAT_8009c330 = 0;
      (*pcVar4)(PTR_DAT_80010024,0);
      (*pcVar5)(PTR_DAT_80010028,0);
      DAT_800f4f8d = '\0';
      DAT_800f5dad = '\0';
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 1:
    uVar3 = FUN_800474cc();
    if ((uVar3 & 0x80) != 0) {
      local_20 = CONCAT22(0xf830,(undefined2)local_20);
      FUN_8005c8d0(0,0,10);
      FUN_8004d9a4(0,2000,0x100,0x100,&local_20,0x6e);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 2:
    if ((char)DAT_800f4f38 < '\0') {
      FUN_8005c698(0,0,0x80,0x80,0x80);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    else {
      DAT_800f4f38._0_1_ = (char)DAT_800f4f38 + '\x02';
      DAT_800f4f38._1_1_ = DAT_800f4f38._1_1_ + '\x02';
      DAT_800f4f38._2_1_ = DAT_800f4f38._2_1_ + '\x02';
    }
    break;
  case 3:
    iVar2 = FUN_8004fb18();
    if ((iVar2 != 0) && (0x77f < DAT_800f4f7e)) {
      FUN_8005c8d0(0,0,0);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 4:
    if (0x77f < DAT_800f4f7e) {
      FUN_8005c8d0(0,0,0);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 5:
    if (0x1df < DAT_800f4f7e) {
      FUN_8005c8d0(0,0,0);
      local_20 = 0xfa24f63c;
      local_1c = CONCAT22(local_1c._2_2_,1000);
      FUN_8004f3c8(0,3000,0xffffff00,0xffffff00,&local_20);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 6:
    if (0x1df < DAT_800f4f7e) {
      FUN_8005c8d0(0,0,0);
      local_20 = 0xfa2409c4;
      local_1c = CONCAT22(local_1c._2_2_,1000);
      FUN_8004f3c8(0,3000,0x100,0xffffff00,&local_20);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 7:
    if (0x1df < DAT_800f4f7e) {
      FUN_8005c8d0(0,0,0);
      local_20 = 0x5dcfe0c;
      local_1c = CONCAT22(local_1c._2_2_,1000);
      FUN_8004f3c8(0,3000,0xfffffe00,0xffffff00,&local_20);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 8:
    if (0x1df < DAT_800f4f7e) {
      FUN_8005c8d0(0,0,0);
      local_20 = 0x5dc01f4;
      local_1c = CONCAT22(local_1c._2_2_,1000);
      FUN_8004f3c8(0,3000,0x200,0xffffff00,&local_20);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 9:
    if (0x1df < DAT_800f4f7e) {
      local_20 = CONCAT22(0xf830,(undefined2)local_20);
      FUN_8004f3c8(0,0xdac,0x40,0x200,&local_20);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 10:
    if (DAT_800f4d6d == 2) {
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 0xb:
    if (0x8bf < DAT_800f4f7e) {
      local_20 = CONCAT22(0xfa24,(undefined2)local_20);
      FUN_8004d9a4(0,0xdac,0,0xffffff80,&local_20,0x28);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 0xc:
    if (0xe5f < DAT_800f4f7e) {
      local_1c = CONCAT22(local_1c._2_2_,0xfc18);
      FUN_8004f3c8(0,5000,0x200,0xffffff00,&local_20);
      FUN_8005c8d0(0,0,0xbe);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 0xd:
    if (0xe5f < DAT_800f4f7e) {
      local_1c = CONCAT22(local_1c._2_2_,0xfc18);
      FUN_8004f3c8(0,5000,0xfffffe00,0xffffff00,&local_20);
      FUN_8005c8d0(0,0,0xbe);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 0xe:
    if (0xe5f < DAT_800f4f7e) {
      local_20 = CONCAT22(0xfc18,(undefined2)local_20);
      FUN_8004f3c8(0,3000,0,0xffffff80,&local_20);
      FUN_8005c8d0(0,0,0xbe);
      DAT_8009c32a = DAT_8009c32a + 1;
    }
    break;
  case 0xf:
    uVar1 = *(ushort *)(&DAT_800f493c + (uint)DAT_800f4d6d * 0x76);
    iVar2 = FUN_8005bf24();
    if ((int)((uint)uVar1 * 0x10 - (uint)DAT_800f4f84._1_1_ * iVar2) <= (int)(uint)DAT_800f4f7e) {
      FUN_8005c808(0,0);
    }
    break;
  case 0x10:
    DAT_8009c32a = 0xfe;
  }
  return;
}

