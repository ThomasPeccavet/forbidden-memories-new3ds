/* Analysis pseudo-C, not buildable source. */

void FUN_8004f92c(int param_1,undefined4 *param_2,undefined4 *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  if ((DAT_8009c313 == '\x01') && (DAT_8009c314 == '\x01')) {
    return;
  }
  if (param_1 != 1) {
    if (1 < param_1) {
      if (param_1 != 2) {
        return;
      }
      puVar4 = &DAT_800f3ec8;
      iVar2 = 0;
      if (DAT_8009c310 != 0) {
        do {
          FUN_8004e818(puVar4);
          iVar2 = iVar2 + 1;
          puVar4 = puVar4 + 10;
        } while (iVar2 < (int)(uint)DAT_8009c310);
      }
      DAT_8009c311 = 0;
      DAT_8009c312 = 0xff;
      return;
    }
    if (param_1 != 0) {
      return;
    }
    FUN_8005cfc4(0xffffffff);
    DAT_8009c30c = &DAT_800f3ec8;
    DAT_8009c310 = 0;
    if ((param_2 == (undefined4 *)0x0) && (param_3 == (undefined4 *)0x0)) {
      if (param_4 == 0) {
        DAT_8009c310 = 0;
        return;
      }
      if (param_4 == 0x4000) {
        DAT_8009c310 = 0;
        return;
      }
    }
    FUN_8004f080(0);
    DAT_8009c311 = 1;
  }
  if (DAT_8009c310 < 10) {
    uVar1 = (uint)DAT_8009c310;
    iVar2 = uVar1 * 0x28;
    if (param_2 == (undefined4 *)0x0) {
      *(undefined2 *)((int)&DAT_800f3ecc + iVar2 + 2) = 0;
    }
    else {
      uVar3 = param_2[1];
      (&DAT_800f3ec8)[uVar1 * 10] = *param_2;
      (&DAT_800f3ecc)[uVar1 * 10] = uVar3;
    }
    if (param_3 == (undefined4 *)0x0) {
      *(undefined2 *)((int)&DAT_800f3ed4 + iVar2 + 2) = 0;
      (&DAT_800f3eee)[iVar2] = 0;
    }
    else {
      uVar3 = param_3[1];
      (&DAT_800f3ed0)[uVar1 * 10] = *param_3;
      (&DAT_800f3ed4)[uVar1 * 10] = uVar3;
      (&DAT_800f3eee)[iVar2] = 0;
    }
    (&DAT_800f3ee8)[uVar1 * 0x14] = (short)param_4;
    (&DAT_800f3eea)[uVar1 * 0x14] = 0;
    (&DAT_800f3eec)[uVar1 * 0x14] = 0;
    DAT_8009c310 = DAT_8009c310 + 1;
  }
  return;
}

