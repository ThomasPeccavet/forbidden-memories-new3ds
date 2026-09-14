/* Analysis pseudo-C, not buildable source. */

void FUN_80032558(int param_1,undefined4 param_2)

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
    break;
  case 1:
    uVar2 = 0x2800;
    goto LAB_800326d4;
  case 2:
    DAT_8009c838 = 0x380;
    DAT_8009c83a = 0x160;
    DAT_8009c83c = 0x40;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0 + (uint)DAT_8009c44b * 0x800);
    *(undefined2 *)(param_1 + 0x30) = 0x340;
    *(undefined2 *)(param_1 + 0x32) = 0;
    *(undefined2 *)(param_1 + 4) = 0x40;
    *(undefined2 *)(param_1 + 6) = 0x10;
    DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
    *(undefined1 *)(param_1 + 0x46) = 2;
    uVar2 = 0x4000;
    break;
  case 3:
    uVar2 = 0x2000;
LAB_800326d4:
    *(undefined4 *)(param_1 + 0x1c) = uVar2;
    iVar1 = DAT_8009c4b0;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(int *)(param_1 + 0xc) = DAT_8009c4b0;
    *(int *)(param_1 + 8) = iVar1;
    *(undefined1 *)(param_1 + 0x46) = 1;
    return;
  case 4:
    DAT_8009c838 = 0x280;
    DAT_8009c83a = 0xe0;
    DAT_8009c83c = 0x100;
    DAT_8009c83e = 0x10;
    FUN_80082380(&DAT_8009c838,DAT_8009c4b0);
  default:
    goto switchD_80032590_default;
  }
  iVar1 = DAT_8009c4b0;
  *(undefined4 *)(param_1 + 0x1c) = uVar2;
  *(int *)(param_1 + 8) = iVar1;
  *(int *)(param_1 + 0xc) = iVar1 + 0x800;
switchD_80032590_default:
  return;
}

