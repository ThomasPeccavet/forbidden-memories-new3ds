/* Analysis pseudo-C, not buildable source. */

void FUN_80043658(undefined2 *param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  puVar3 = DAT_8009c4b0;
  switch(param_2) {
  case 0:
    param_1[0x18] = 0x280;
    param_1[2] = 0x40;
    param_1[3] = 0x10;
    param_1[0x19] = 0;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x23) = 2;
    uVar2 = 0x6000;
    goto LAB_8004376c;
  case 1:
    uVar1 = 0x2c0;
    goto LAB_80043714;
  case 2:
    uVar1 = 0x300;
LAB_80043714:
    param_1[0x18] = uVar1;
    param_1[2] = 0x40;
    param_1[3] = 0x10;
    param_1[0x19] = 0;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x23) = 2;
    uVar2 = 0x6800;
LAB_8004376c:
    puVar3 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0xe) = uVar2;
    *(undefined **)(param_1 + 4) = puVar3;
    *(undefined **)(param_1 + 6) = puVar3 + 0x800;
    return;
  case 3:
    *(undefined4 *)(param_1 + 0xe) = 0x1000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = DAT_8009c4b0;
    break;
  case 4:
    *param_1 = 0x280;
    param_1[1] = 0xf8;
    param_1[2] = 0x100;
    param_1[3] = 8;
    FUN_80082380(param_1,puVar3);
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = DAT_8009c4b0 + 0x1000;
    break;
  case 5:
    *param_1 = 0x280;
    param_1[1] = 0xc0;
    param_1[2] = 0x10;
    param_1[3] = 8;
    FUN_80082380(param_1,puVar3 + 0x1000);
    *(undefined4 *)(param_1 + 0xe) = 0xf000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_DAT_800101e0;
    break;
  case 6:
    *(undefined4 *)(param_1 + 0xe) = 0x10000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_DAT_800101e4;
    break;
  case 7:
    *(undefined4 *)(param_1 + 0xe) = 0x3800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_DAT_800101e8;
    break;
  default:
    goto switchD_80043688_default;
  }
  *(undefined **)(param_1 + 6) = puVar3;
  *(undefined **)(param_1 + 4) = puVar3;
  *(undefined1 *)(param_1 + 0x23) = 1;
switchD_80043688_default:
  return;
}

