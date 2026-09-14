/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8005a92c(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
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
    *(undefined4 *)(param_1 + 0x1c) = 0x30000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_FUN_80010000;
    goto LAB_8005aaa0;
  case 1:
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined2 *)(param_1 + 0x30) = 0;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    uVar4 = 0x30000;
    goto LAB_8005ab4c;
  case 2:
    *(undefined **)(param_1 + 0xc) = &DAT_801dd000;
    *(undefined **)(param_1 + 8) = &DAT_801dd000;
    uVar4 = 0x1000;
    goto LAB_8005abcc;
  case 3:
    local_20 = 0x280;
    local_1e = 0xd8;
    local_1c = 0x100;
    local_1a = 8;
    FUN_80082380(&local_20,&DAT_801dd000);
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_DAT_80010014;
    goto LAB_8005aaa0;
  case 4:
    *(undefined4 *)(param_1 + 0x1c) = 0x5000;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    puVar3 = PTR_DAT_80010018;
LAB_8005aaa0:
    *(undefined **)(param_1 + 0xc) = puVar3;
    *(undefined **)(param_1 + 8) = puVar3;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 5:
  case 9:
    puVar2 = (undefined4 *)&DAT_801dd000;
    goto LAB_8005abb8;
  case 6:
    local_18 = 0x280;
    local_16 = 0xe0;
    local_14 = 0x100;
    local_12 = 2;
    FUN_80082380(&local_18,&DAT_801dd000);
    *(undefined2 *)(param_1 + 0x30) = 0x180;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    uVar4 = 0x4000;
LAB_8005ab4c:
    iVar1 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x1c) = uVar4;
    *(int *)(param_1 + 8) = iVar1;
    *(int *)(param_1 + 0xc) = iVar1 + 0x800;
    break;
  case 7:
    puVar2 = &DAT_801a8000;
LAB_8005abb8:
    *(undefined4 **)(param_1 + 0xc) = puVar2;
    *(undefined4 **)(param_1 + 8) = puVar2;
    uVar4 = 0x800;
LAB_8005abcc:
    *(undefined4 *)(param_1 + 0x1c) = uVar4;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 8:
    *(undefined1 *)(param_1 + 0x46) = 3;
    iVar1 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x30) = 0xd810;
    *(undefined4 *)(param_1 + 0x1c) = 0x19000;
    *(int *)(param_1 + 8) = iVar1;
    *(int *)(param_1 + 0xc) = iVar1 + 0x800;
    break;
  case 10:
    FUN_8004d978(&DAT_800f4d70,&DAT_801dd000,0x40);
    DAT_800f4e74 = DAT_801dd104;
    DAT_800f4e78 = DAT_801dd108;
    DAT_800f4e7c = DAT_801dd10c;
    DAT_800f4e80 = 0xffffffff;
    DAT_800f4e84 = 0xffffffff;
    DAT_800f4e88 = 0xffffffff;
    _DAT_800f4e70 = 0;
    DAT_800f4f8c = 1;
  }
  return;
}

