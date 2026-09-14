/* Analysis pseudo-C, not buildable source. */

void FUN_8006b350(int param_1,undefined4 param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  switch(param_2) {
  case 0:
    *(undefined2 *)(param_1 + 0x30) = 0x200;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    iVar2 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x1c) = 0x20000;
    *(int *)(param_1 + 8) = iVar2;
    *(int *)(param_1 + 0xc) = iVar2 + 0x800;
    break;
  case 1:
    *(undefined2 *)(param_1 + 0x30) = 0x380;
    *(undefined2 *)(param_1 + 0x32) = 0;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined4 *)(param_1 + 0x1c) = 0x10000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    iVar2 = DAT_8009c4b0;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(int *)(param_1 + 8) = iVar2;
    *(int *)(param_1 + 0xc) = iVar2 + 0x800;
    break;
  case 2:
    *(undefined **)(param_1 + 0xc) = &DAT_801dd000;
    *(undefined **)(param_1 + 8) = &DAT_801dd000;
    uVar3 = 0x1000;
    goto LAB_8006b538;
  case 3:
    local_10 = DAT_8009c3fc;
    local_c = DAT_8009c400;
    FUN_80082380(&local_10,&DAT_801dd000);
    *(undefined4 *)(param_1 + 0x1c) = 0x8000;
    puVar1 = PTR_DAT_8001002c;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined **)(param_1 + 0xc) = PTR_DAT_8001002c;
    *(undefined **)(param_1 + 8) = puVar1;
    goto LAB_8006b54c;
  case 4:
    *(undefined **)(param_1 + 0xc) = &DAT_801af800;
    *(undefined **)(param_1 + 8) = &DAT_801af800;
    uVar3 = 0x800;
LAB_8006b538:
    *(undefined4 *)(param_1 + 0x1c) = uVar3;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
LAB_8006b54c:
    *(undefined1 *)(param_1 + 0x46) = 1;
  }
  return;
}

