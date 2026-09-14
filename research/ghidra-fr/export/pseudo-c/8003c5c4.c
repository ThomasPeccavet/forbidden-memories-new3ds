/* Analysis pseudo-C, not buildable source. */

void FUN_8003c5c4(undefined2 *param_1,int param_2)

{
  undefined *puVar1;
  
  if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0xe) = 0x800;
    puVar1 = DAT_8009c4b0;
  }
  else {
    if (param_2 < 2) {
      if (param_2 != 0) {
        return;
      }
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
    }
    if (param_2 == 2) {
      *param_1 = 0x280;
      param_1[1] = 0xe0;
      param_1[2] = 0x100;
      puVar1 = DAT_8009c4b0;
      param_1[3] = 4;
      FUN_80082380(param_1,puVar1);
      *(undefined **)(param_1 + 6) = &DAT_801af000;
      *(undefined **)(param_1 + 4) = &DAT_801af000;
      *(undefined4 *)(param_1 + 0xe) = 0x1000;
      DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
      *(undefined1 *)(param_1 + 0x23) = 1;
      return;
    }
    if (param_2 != 3) {
      return;
    }
    *(undefined4 *)(param_1 + 0xe) = 0x3000;
    puVar1 = PTR_DAT_800101d8;
  }
  DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
  *(undefined **)(param_1 + 6) = puVar1;
  *(undefined **)(param_1 + 4) = puVar1;
  *(undefined1 *)(param_1 + 0x23) = 1;
  return;
}

