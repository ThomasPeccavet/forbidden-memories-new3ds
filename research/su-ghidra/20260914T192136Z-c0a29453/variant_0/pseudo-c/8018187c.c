/* Analysis pseudo-C, not buildable source. */

void FUN_8018187c(void)

{
  int iVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 auStack_a0 [3];
  undefined1 local_9d;
  undefined1 local_9c;
  undefined1 local_9b;
  undefined1 local_9a;
  undefined1 local_99;
  short local_98;
  undefined2 local_96;
  char local_94;
  undefined1 local_93;
  undefined2 local_92;
  undefined1 local_90;
  undefined1 local_8f;
  undefined1 local_8e;
  short local_8c;
  undefined2 local_8a;
  char local_88;
  undefined1 local_87;
  undefined2 local_86;
  undefined1 local_84;
  undefined1 local_83;
  undefined1 local_82;
  short local_80;
  undefined2 local_7e;
  char local_7c;
  undefined1 local_7b;
  undefined1 local_78;
  undefined1 local_77;
  undefined1 local_76;
  short local_74;
  undefined2 local_72;
  char local_70;
  undefined1 local_6f;
  undefined1 auStack_68 [3];
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined2 local_60;
  undefined2 local_5e;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  short local_58;
  undefined2 local_56;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined2 local_50;
  undefined2 local_4e;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  short local_48;
  undefined2 local_46;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_30;
  
  uVar5 = (uint)DAT_801847ee;
  uVar6 = (uint)DAT_801847fa;
  uVar2 = 0xdc;
  if (DAT_801847ea == '\0') {
    uVar2 = 0x74;
  }
  *(undefined2 *)(DAT_801847e4 + 0x30) = uVar2;
  *(undefined2 *)(DAT_801847e4 + 0x32) = 0x4a;
  if ((*(int *)(DAT_801847dc + 0x24) == 0) && (DAT_801847e8 != '\x02')) {
    *(ushort *)(DAT_801847dc + 8) = *(ushort *)(DAT_801847dc + 8) & 0xffbf;
    *(undefined2 *)(DAT_801847dc + 0x30) = *(undefined2 *)(DAT_801847e4 + 0x30);
    uVar2 = *(undefined2 *)(DAT_801847e4 + 0x32);
code_r0x801819a0:
    *(undefined2 *)(DAT_801847dc + 0x32) = uVar2;
  }
  else {
    *(ushort *)(DAT_801847dc + 8) = *(ushort *)(DAT_801847dc + 8) | 0x40;
    if (*(int *)(DAT_801847dc + 0x24) == 0) {
      *(short *)(DAT_801847dc + 0x30) = (short)((uVar5 << 7) / 8000) + 0xb0;
      uVar2 = 0x6f;
      goto code_r0x801819a0;
    }
  }
  if ((*(int *)(DAT_801847e0 + 0x24) == 0) && (DAT_801847e9 != '\x02')) {
    *(ushort *)(DAT_801847e0 + 8) = *(ushort *)(DAT_801847e0 + 8) & 0xffbf;
    *(undefined2 *)(DAT_801847e0 + 0x30) = *(undefined2 *)(DAT_801847e4 + 0x30);
    uVar2 = *(undefined2 *)(DAT_801847e4 + 0x32);
  }
  else {
    *(ushort *)(DAT_801847e0 + 8) = *(ushort *)(DAT_801847e0 + 8) | 0x40;
    if (*(int *)(DAT_801847e0 + 0x24) != 0) goto LAB_80181a6c;
    *(short *)(DAT_801847e0 + 0x30) = (short)((uVar6 << 7) / 8000) + 0xb0;
    uVar2 = 0x8b;
  }
  *(undefined2 *)(DAT_801847e0 + 0x32) = uVar2;
LAB_80181a6c:
  iVar4 = 0;
  local_65 = 8;
  local_61 = 0x38;
  local_5e = 0x6b;
  local_56 = 0x6b;
  local_64 = 0x40;
  local_63 = 0x20;
  local_62 = 0x20;
  local_5c = 0xff;
  local_5b = 0x20;
  local_5a = 0x20;
  local_54 = 0x40;
  local_53 = 0x20;
  local_52 = 0x20;
  local_4c = 0xff;
  local_4b = 0x20;
  local_4a = 0x20;
  local_60 = 0xb0;
  local_50 = 0xb0;
  local_4e = 0x73;
  local_46 = 0x73;
  local_58 = (short)((uVar5 << 7) / 8000) + 0xb0;
  local_48 = local_58;
  FUN_800842a8(auStack_68,DAT_8009c860,0x800);
  local_5e = 0x87;
  local_56 = 0x87;
  local_64 = 0x20;
  local_63 = 0x20;
  local_62 = 0x40;
  local_5c = 0x20;
  local_5b = 0x20;
  local_5a = 0xff;
  local_54 = 0x20;
  local_53 = 0x20;
  local_52 = 0x40;
  local_4c = 0x20;
  local_4b = 0x20;
  local_4a = 0xff;
  local_60 = 0xb0;
  local_50 = 0xb0;
  local_4e = 0x8f;
  local_46 = 0x8f;
  local_58 = (short)((uVar6 << 7) / 8000) + 0xb0;
  local_48 = local_58;
  FUN_800842a8(auStack_68,DAT_8009c860,0x800);
  local_9d = 0xc;
  local_99 = 0x3c;
  local_86 = 10;
  local_92 = 0x3028;
  local_9c = 0x80;
  local_9b = 0x80;
  local_9a = 0x80;
  local_90 = 0x80;
  local_8f = 0x80;
  local_8e = 0x80;
  local_84 = 0x80;
  local_83 = 0x80;
  local_82 = 0x80;
  local_78 = 0x80;
  local_77 = 0x80;
  local_76 = 0x80;
  local_40 = FUN_80182044(8000);
  iVar1 = FUN_80182044(uVar5);
  if (0 < iVar1) {
    sVar3 = -0x7e;
    local_3c = local_40 << 3;
    local_30 = 0x6a;
    do {
      iVar4 = iVar4 + 1;
      local_98 = (short)local_3c - sVar3;
      sVar3 = sVar3 + 8;
      local_8c = local_98 + 8;
      local_96 = (undefined2)local_30;
      local_7e = 0x72;
      local_72 = 0x72;
      local_93 = 0x40;
      local_87 = 0x40;
      local_7b = 0x48;
      local_6f = 0x48;
      local_88 = ((char)uVar5 + (char)((int)uVar5 / 10) * -10) * '\b';
      local_94 = local_88 + -0x80;
      local_88 = local_88 + -0x78;
      local_8a = local_96;
      local_80 = local_98;
      local_7c = local_94;
      local_74 = local_8c;
      local_70 = local_88;
      FUN_800842a8(auStack_a0,DAT_8009c860,0x800);
      uVar5 = (int)uVar5 / 10;
    } while (iVar4 < iVar1);
  }
  iVar1 = FUN_80182044(uVar6);
  iVar4 = 0;
  if (0 < iVar1) {
    local_38 = local_40 << 3;
    sVar3 = -0x7e;
    do {
      iVar4 = iVar4 + 1;
      local_98 = (short)local_38 - sVar3;
      sVar3 = sVar3 + 8;
      local_8c = local_98 + 8;
      local_96 = 0x86;
      local_8a = 0x86;
      local_7e = 0x8e;
      local_72 = 0x8e;
      local_93 = 0x40;
      local_87 = 0x40;
      local_7b = 0x48;
      local_6f = 0x48;
      local_88 = ((char)uVar6 + (char)((int)uVar6 / 10) * -10) * '\b';
      local_94 = local_88 + -0x80;
      local_88 = local_88 + -0x78;
      local_80 = local_98;
      local_7c = local_94;
      local_74 = local_8c;
      local_70 = local_88;
      FUN_800842a8(auStack_a0,DAT_8009c860,0x800);
      uVar6 = (int)uVar6 / 10;
    } while (iVar4 < iVar1);
  }
  return;
}

