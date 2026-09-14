/* Analysis pseudo-C, not buildable source. */

void FUN_8002be90(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  switch(param_2) {
  case 0:
    *(undefined2 *)(param_1 + 0x30) = 0x300;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    uVar2 = 0x20000;
    iVar1 = DAT_8009c4b0;
    goto LAB_8002c0a0;
  case 1:
    uVar2 = 0x2800;
    goto LAB_8002c0c0;
  case 2:
    DAT_8009c838 = 0x380;
    DAT_8009c83a = 0x160;
    DAT_8009c83c = 0x40;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0 + (uint)DAT_8009c44b * 0x800);
    uVar2 = 0x2000;
    goto LAB_8002c0c0;
  case 3:
    DAT_8009c838 = 0x280;
    DAT_8009c83a = 0xe0;
    DAT_8009c83c = 0x100;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0);
    *(undefined2 *)(param_1 + 0x30) = 0x240;
    *(undefined2 *)(param_1 + 0x32) = 0x100;
    *(undefined2 *)(param_1 + 6) = 0x10;
    *(undefined4 *)(param_1 + 0x1c) = 0x18000;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    iVar1 = DAT_8009c4b0;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(int *)(param_1 + 8) = iVar1;
    *(int *)(param_1 + 0xc) = iVar1 + 0x800;
    break;
  case 4:
  case 6:
    uVar2 = 0x800;
LAB_8002c0c0:
    *(undefined4 *)(param_1 + 0x1c) = uVar2;
    iVar1 = DAT_8009c4b0;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(int *)(param_1 + 0xc) = DAT_8009c4b0;
    *(int *)(param_1 + 8) = iVar1;
    *(undefined1 *)(param_1 + 0x46) = 1;
    break;
  case 5:
    DAT_8009c838 = 0x280;
    DAT_8009c83a = 0xe6;
    DAT_8009c83c = 0x100;
    DAT_8009c83e = 2;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0);
    *(undefined1 *)(param_1 + 0x46) = 3;
    iVar1 = DAT_8009c4b0;
    *(undefined4 *)(param_1 + 0x30) = 0x26810;
    uVar2 = 0xa000;
LAB_8002c0a0:
    *(undefined4 *)(param_1 + 0x1c) = uVar2;
    *(int *)(param_1 + 8) = iVar1;
    *(int *)(param_1 + 0xc) = iVar1 + 0x800;
    break;
  case 7:
    FUN_80049198(1,DAT_8009c4b0);
  }
  return;
}

