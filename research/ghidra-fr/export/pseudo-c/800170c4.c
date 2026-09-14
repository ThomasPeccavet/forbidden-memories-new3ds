/* Analysis pseudo-C, not buildable source. */

void FUN_800170c4(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  switch(param_2) {
  case 0:
    *(undefined2 *)(param_1 + 0x30) = 0x300;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined4 *)(param_1 + 0x1c) = 0x20000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    puVar2 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x40) = 0x10;
    goto LAB_80017428;
  case 1:
    DAT_8009c838 = 0x380;
    DAT_8009c83a = 0x160;
    DAT_8009c83c = 0x40;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0 + (uint)DAT_8009c44b * 0x800);
    *(undefined4 *)(param_1 + 0x1c) = 0x2000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar2 = DAT_8009c4b0;
    break;
  case 2:
    DAT_8009c838 = 0x280;
    DAT_8009c83a = 0xe0;
    DAT_8009c83c = 0x100;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0);
    *(undefined2 **)(param_1 + 0xc) = &DAT_8017a1d8;
    *(undefined2 **)(param_1 + 8) = &DAT_8017a1d8;
    uVar3 = 0x2800;
    goto LAB_800173a4;
  case 3:
    *(undefined **)(param_1 + 0xc) = &DAT_8017c2d8;
    *(undefined **)(param_1 + 8) = &DAT_8017c2d8;
    uVar3 = 0x10000;
    goto LAB_800173a4;
  case 4:
    *(undefined4 **)(param_1 + 0xc) = &DAT_801799d8;
    *(undefined4 **)(param_1 + 8) = &DAT_801799d8;
    uVar3 = 0x800;
    goto LAB_800173a4;
  case 5:
    *(undefined4 *)(param_1 + 0x1c) = 0x1000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar2 = DAT_8009c4b0;
    break;
  case 6:
    DAT_8009c838 = 0x280;
    DAT_8009c83a = 0xd0;
    DAT_8009c83c = 0x100;
    DAT_8009c83e = 8;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0);
    *(undefined2 *)(param_1 + 0x30) = 0x200;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    goto LAB_8001749c;
  case 7:
    *(undefined4 *)(param_1 + 0x1c) = 0x16000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar2 = PTR_DAT_800101dc;
    break;
  case 8:
    puVar1 = &DAT_801a8000;
    goto LAB_80017390;
  case 9:
    puVar1 = (undefined4 *)&DAT_801a9800;
LAB_80017390:
    *(undefined4 **)(param_1 + 0xc) = puVar1;
    *(undefined4 **)(param_1 + 8) = puVar1;
    uVar3 = 0x1800;
LAB_800173a4:
    *(undefined4 *)(param_1 + 0x1c) = uVar3;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined1 *)(param_1 + 0x46) = 1;
    return;
  case 10:
    *(undefined2 *)(param_1 + 0x30) = 0x340;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined2 *)(param_1 + 0x32) = 0;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    puVar2 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x1c) = 0x4000;
LAB_80017428:
    *(undefined **)(param_1 + 8) = puVar2;
    *(undefined **)(param_1 + 0xc) = puVar2 + 0x800;
    return;
  case 0xb:
    *(undefined4 *)(param_1 + 0x1c) = 0x2800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar2 = PTR_FUN_80010000;
    break;
  case 0xc:
    *(undefined2 *)(param_1 + 0x30) = 0x280;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
LAB_8001749c:
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined4 *)(param_1 + 0x1c) = 0x10000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    puVar2 = DAT_8009c4b0;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined **)(param_1 + 8) = puVar2;
    *(undefined **)(param_1 + 0xc) = puVar2 + 0x800;
    return;
  default:
    goto switchD_800170f8_caseD_d;
  case 0x10:
    *(undefined4 *)(param_1 + 0x1c) = 0x2800;
    *(undefined4 *)(param_1 + 0x40) = 1;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar2 = DAT_8009c4b0;
  }
  *(undefined **)(param_1 + 0xc) = puVar2;
  *(undefined **)(param_1 + 8) = puVar2;
  *(undefined1 *)(param_1 + 0x46) = 1;
switchD_800170f8_caseD_d:
  return;
}

