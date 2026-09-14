/* Analysis pseudo-C, not buildable source. */

void FUN_8003baf4(undefined2 *param_1,undefined4 param_2)

{
  undefined *puVar1;
  
  switch(param_2) {
  case 0:
    param_1[0x19] = 0x100;
    param_1[2] = 0x40;
    param_1[0x18] = 0;
    *(undefined4 *)(param_1 + 0xe) = 0x18000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x23) = 2;
    puVar1 = DAT_8009c4b0;
    param_1[3] = 0x10;
    *(undefined **)(param_1 + 4) = puVar1;
    *(undefined **)(param_1 + 6) = puVar1 + 0x800;
    return;
  case 1:
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar1 = DAT_8009c4b0;
    break;
  case 2:
    *param_1 = 0x280;
    param_1[1] = 0xd0;
    param_1[2] = 0x100;
    puVar1 = DAT_8009c4b0;
    param_1[3] = 4;
    FUN_80082380(param_1,puVar1);
    *(undefined **)(param_1 + 6) = &DAT_801af000;
    *(undefined **)(param_1 + 4) = &DAT_801af000;
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    goto LAB_8003bca0;
  case 3:
    *(undefined4 *)(param_1 + 0xe) = 0x18000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar1 = PTR_FUN_80010000;
    break;
  case 4:
    *(undefined4 *)(param_1 + 0xe) = 0x2800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar1 = PTR_DAT_800101d8;
    break;
  default:
    goto switchD_8003bb24_default;
  }
  *(undefined **)(param_1 + 6) = puVar1;
  *(undefined **)(param_1 + 4) = puVar1;
LAB_8003bca0:
  *(undefined1 *)(param_1 + 0x23) = 1;
switchD_8003bb24_default:
  return;
}

