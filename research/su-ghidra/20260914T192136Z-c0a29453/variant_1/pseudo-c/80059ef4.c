/* Analysis pseudo-C, not buildable source. */

void FUN_80059ef4(int param_1,undefined4 param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  undefined2 local_28;
  short local_26;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  iVar8 = *(int *)(param_1 + 0x38);
  iVar7 = *(int *)(param_1 + 0x3c);
  iVar4 = iVar8 * 0xe20;
  sVar1 = (short)iVar8;
  switch(param_2) {
  case 0:
    puVar6 = PTR_FUN_80010004;
    if (iVar8 == 0) {
      puVar6 = PTR_FUN_80010000;
    }
    *(undefined **)(param_1 + 0xc) = puVar6;
    *(undefined **)(param_1 + 8) = puVar6;
    uVar5 = 0x30000;
    goto LAB_8005a5c8;
  case 1:
    *(short *)(param_1 + 0x30) = (short)(iVar8 << 8);
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined4 *)(param_1 + 0x1c) = 0x18000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    iVar4 = DAT_8009c4b0;
    *(undefined2 *)(param_1 + 6) = 0x10;
LAB_8005a594:
    *(int *)(param_1 + 8) = iVar4;
    *(int *)(param_1 + 0xc) = iVar4 + 0x800;
    return;
  case 2:
    *(undefined **)(param_1 + 0xc) = &DAT_801dd000;
    *(undefined **)(param_1 + 8) = &DAT_801dd000;
    uVar5 = 0x1000;
    goto LAB_8005a5c8;
  case 3:
    local_28 = 0x280;
    local_26 = sVar1 * 0x10 + 0xd8;
    local_24 = 0x100;
    local_22 = 8;
    FUN_80082380(&local_28,&DAT_801dd000);
    uVar5 = 0x800;
    *(undefined **)(param_1 + 0xc) = &DAT_801de000;
    *(undefined **)(param_1 + 8) = &DAT_801de000;
    goto LAB_8005a5c8;
  case 4:
    if (iVar7 == 0) {
      puVar6 = &DAT_801de000;
LAB_8005a134:
      local_1e = sVar1 + 0xf2;
      local_1a = 1;
      local_1c = 0x100;
      local_20 = 0x280;
      FUN_80082380(&local_20,puVar6);
      *(short *)(param_1 + 0x30) = sVar1 * 0x100 + 0xc0;
      *(undefined2 *)(param_1 + 4) = 0x40;
      *(undefined2 *)(param_1 + 6) = 0x10;
      *(undefined2 *)(param_1 + 0x32) = 0x100;
      DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
      *(undefined1 *)(param_1 + 0x46) = 2;
      iVar4 = DAT_8009c4b0;
      *(undefined4 *)(param_1 + 0x1c) = 0x8000;
      *(int *)(param_1 + 8) = iVar4;
      *(int *)(param_1 + 0xc) = iVar4 + 0x800;
      return;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x8000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 5:
  case 0xf:
    *(undefined **)(param_1 + 0xc) = &DAT_801dd000;
    *(undefined **)(param_1 + 8) = &DAT_801dd000;
LAB_8005a5c4:
    uVar5 = 0x800;
LAB_8005a5c8:
    *(undefined4 *)(param_1 + 0x1c) = uVar5;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    break;
  case 6:
    if (iVar7 == 1) {
      puVar6 = &DAT_801dd000;
      goto LAB_8005a134;
    }
    uVar5 = 0x8000;
    goto LAB_8005a470;
  case 7:
    if ((iVar7 == 0) && (iVar8 == 0)) {
      *(undefined4 *)(param_1 + 0x1c) = 0x5000;
      puVar6 = PTR_DAT_80010014;
LAB_8005a3c8:
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      *(undefined **)(param_1 + 0xc) = puVar6;
      *(undefined **)(param_1 + 8) = puVar6;
      *(undefined1 *)(param_1 + 0x46) = 1;
      return;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 8:
    if ((iVar7 == 0) && (iVar8 == 1)) {
      *(undefined4 *)(param_1 + 0x1c) = 0x5000;
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      puVar6 = PTR_DAT_80010018;
LAB_8005a448:
      *(undefined **)(param_1 + 0xc) = puVar6;
      *(undefined **)(param_1 + 8) = puVar6;
      *(char *)(param_1 + 0x46) = (char)iVar8;
      return;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 9:
    if ((iVar7 == 1) && (iVar8 == 0)) {
      *(undefined4 *)(param_1 + 0x1c) = 0x5000;
      puVar6 = PTR_DAT_80010014;
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      *(undefined **)(param_1 + 0xc) = PTR_DAT_80010014;
      *(undefined **)(param_1 + 8) = puVar6;
      *(undefined1 *)(param_1 + 0x46) = 1;
      return;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 10:
    if ((iVar7 == 1) && (iVar8 == 1)) {
      *(undefined4 *)(param_1 + 0x1c) = 0x5000;
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      puVar6 = PTR_DAT_80010018;
      goto LAB_8005a448;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 0xb:
    if (iVar8 == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 0x1000;
      puVar6 = PTR_DAT_8001000c;
      goto LAB_8005a3c8;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x1000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 0xc:
    if (iVar8 == 1) {
      *(undefined4 *)(param_1 + 0x1c) = 0x1000;
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      puVar6 = PTR_DAT_80010010;
      goto LAB_8005a448;
    }
    uVar5 = 0x1000;
LAB_8005a470:
    *(undefined4 *)(param_1 + 0x1c) = uVar5;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    *(undefined1 *)(param_1 + 0x46) = 1;
    return;
  case 0xd:
    if ((&DAT_800f4f95)[iVar4] == '\0') {
      *(undefined4 **)(param_1 + 0xc) = &DAT_801a8000 + iVar8 * 0x200;
      *(undefined4 **)(param_1 + 8) = &DAT_801a8000 + iVar8 * 0x200;
      goto LAB_8005a5c4;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 0xe:
    if ((&DAT_800f4f95)[iVar4] == '\0') {
      *(undefined1 *)(param_1 + 0x46) = 3;
      iVar4 = DAT_8009c4b0;
      *(int *)(param_1 + 0x30) = iVar8 * 0x19000 + 0xd810;
      *(undefined4 *)(param_1 + 0x1c) = 0x19000;
      goto LAB_8005a594;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0x19000;
    DAT_8009c460 = DAT_8009c460 & 0xfffcffff | 0x200000;
    break;
  case 0x10:
    FUN_8004d978(&DAT_800f4d70 + iVar4,&DAT_801dd000,0x40);
    uVar3 = DAT_801dd10c;
    uVar2 = DAT_801dd108;
    uVar5 = DAT_801dd104;
    *(undefined4 *)(&DAT_800f4e70 + iVar8 * 0x710) = DAT_801dd100;
    (&DAT_800f4e74)[iVar8 * 0x388] = uVar5;
    (&DAT_800f4e78)[iVar8 * 0x388] = uVar2;
    (&DAT_800f4e7c)[iVar8 * 0x388] = uVar3;
    uVar2 = DAT_801dd118;
    uVar5 = DAT_801dd114;
    (&DAT_800f4e80)[iVar8 * 0x388] = DAT_801dd110;
    (&DAT_800f4e84)[iVar8 * 0x388] = uVar5;
    (&DAT_800f4e88)[iVar8 * 0x388] = uVar2;
    if (((&DAT_800f4e78)[iVar8 * 0x388] & 0x20200000) != 0) {
      FUN_8005c38c(iVar8,4);
    }
    if (*(short *)(&DAT_800f4f72 + iVar4) != -1) {
      (&DAT_800f4e70)[iVar8 * 0x710] = *(short *)(&DAT_800f4f72 + iVar4);
    }
    if (*(short *)(&DAT_800f4f74 + iVar4) != -1) {
      (&DAT_800f4e72)[iVar8 * 0x710] = *(short *)(&DAT_800f4f74 + iVar4);
    }
    if ((&DAT_800f4f95)[iVar4] != '\0') {
      (&DAT_800f4e80)[iVar8 * 0x388] = 0xffffffff;
      (&DAT_800f4e84)[iVar8 * 0x388] = 0xffffffff;
      (&DAT_800f4e88)[iVar8 * 0x388] = 0xffffffff;
    }
    (&DAT_800f4f8c)[iVar4] = 1;
  default:
    goto switchD_80059f58_default;
  }
  *(undefined1 *)(param_1 + 0x46) = 1;
switchD_80059f58_default:
  return;
}

