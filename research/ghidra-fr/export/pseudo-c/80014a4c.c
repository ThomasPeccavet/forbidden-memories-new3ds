/* Analysis pseudo-C, not buildable source. */

void FUN_80014a4c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 != 1) {
    if (1 < param_2) {
      if (param_2 != 2) {
        return;
      }
      goto LAB_80014b34;
    }
    if (param_2 != 0) {
      return;
    }
    if (DAT_801d4214 != 0) {
      *(undefined1 *)(param_1 + 0x46) = 3;
      iVar2 = DAT_8009c4b0;
      *(int *)(param_1 + 8) = DAT_8009c4b0;
      *(int *)(param_1 + 0xc) = iVar2 + 0x800;
      *(undefined4 *)(param_1 + 0x30) = DAT_801d420c;
      iVar2 = DAT_801d4214;
      *(int *)(param_1 + 0x1c) = DAT_801d4214;
      goto LAB_80014b20;
    }
    *(undefined4 *)(param_1 + 0x40) = 2;
  }
  uVar1 = DAT_801d4210;
  if (DAT_801d4218 != 0) {
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(undefined4 *)(param_1 + 0xc) = DAT_801d4210;
    *(undefined4 *)(param_1 + 8) = uVar1;
    *(undefined1 *)(param_1 + 0x46) = 1;
    iVar2 = DAT_801d4218;
    *(int *)(param_1 + 0x1c) = DAT_801d4218;
LAB_80014b20:
    if (iVar2 < 0) {
      *(int *)(param_1 + 0x1c) = iVar2 * -0x800;
    }
    return;
  }
LAB_80014b34:
  if (DAT_8009c470 == (code *)0x0) {
    return;
  }
  (*DAT_8009c470)();
  return;
}

