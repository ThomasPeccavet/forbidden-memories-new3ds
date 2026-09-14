/* Analysis pseudo-C, not buildable source. */

void FUN_8003a3ac(undefined2 *param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    iVar1 = DAT_8009c4b0;
  }
  else {
    if (param_2 < 2) {
      if (param_2 != 0) {
        return;
      }
      *(undefined4 *)(param_1 + 0xe) = 0x18000;
      param_1[0x19] = 0x100;
      param_1[2] = 0x40;
      param_1[3] = 0x10;
      DAT_8009c460 = DAT_8009c460 & 0xffddffff | 0x10000;
      *(undefined1 *)(param_1 + 0x23) = 2;
      iVar1 = DAT_8009c4b0;
      param_1[0x18] = (short)*(undefined4 *)(param_1 + 0x1e) * -0xc0 + 0x340;
      *(int *)(param_1 + 4) = iVar1;
      *(int *)(param_1 + 6) = iVar1 + 0x800;
      return;
    }
    if (param_2 != 2) {
      return;
    }
    *param_1 = 0x280;
    param_1[3] = 2;
    iVar1 = DAT_8009c4b0;
    param_1[2] = 0x100;
    param_1[1] = (short)*(undefined4 *)(param_1 + 0x1e) * 2 + 0xf0;
    FUN_80082380(param_1,iVar1);
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    iVar1 = *(int *)(param_1 + 0x1c);
  }
  DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
  *(int *)(param_1 + 6) = iVar1;
  *(int *)(param_1 + 4) = iVar1;
  *(undefined1 *)(param_1 + 0x23) = 1;
  return;
}

