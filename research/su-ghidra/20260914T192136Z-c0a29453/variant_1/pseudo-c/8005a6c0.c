/* Analysis pseudo-C, not buildable source. */

void FUN_8005a6c0(int param_1,undefined4 param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  switch(param_2) {
  case 0:
    *(undefined4 *)(param_1 + 0x1c) = 0x9000;
    puVar1 = PTR_DAT_80010008;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined **)(param_1 + 0xc) = PTR_DAT_80010008;
    *(undefined **)(param_1 + 8) = puVar1;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 1:
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
  case 2:
    *(undefined **)(param_1 + 0xc) = &DAT_801dd800;
    *(undefined **)(param_1 + 8) = &DAT_801dd800;
    *(undefined4 *)(param_1 + 0x1c) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 3:
    local_20 = 0x280;
    local_1e = 0xf1;
    local_1c = 0x100;
    local_1a = 1;
    FUN_80082380(&local_20,&DAT_801dd800);
    *(undefined **)(param_1 + 0xc) = &DAT_801dd000;
    *(undefined **)(param_1 + 8) = &DAT_801dd000;
    *(undefined4 *)(param_1 + 0x1c) = 0x800;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 4:
    local_18 = 0x280;
    local_16 = 0xf4;
    local_14 = 0x100;
    local_12 = 2;
    FUN_80082380(&local_18,&DAT_801dd000);
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
  case 5:
    DAT_800f6bcc = 1;
  }
  return;
}

