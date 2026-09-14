/* Analysis pseudo-C, not buildable source. */

void FUN_800536d8(uint param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  
  if ((&DAT_800f4f97)[param_1 * 0xe20] == '\0') {
    if ((&DAT_800f4f8c)[param_1 * 0xe20] == -1) {
      uVar3 = DAT_8009c484;
      if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
        do {
          do {
            iVar1 = FUN_8008f708(uVar3);
            uVar3 = iVar1 >> 8;
            uVar6 = (int)uVar3 % 0x2d2;
          } while (0x2d1 < uVar6);
        } while (((uVar6 - 300 < 0x32) || (uVar6 - 0x28a < 0x32)) ||
                (uVar3 = param_1 | 0x80, uVar6 == 0x2d0));
        FUN_8005967c(param_1 | 0x80,uVar6,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0);
      }
    }
    else {
      FUN_800599a0(param_1);
    }
    if ((&DAT_800f4f97)[param_1 * 0xe20] != '\0') {
      sVar5 = 0x400;
      if (((&DAT_800f4f97)[(param_1 ^ 1) * 0xe20] != '\0') &&
         ((&DAT_800f4e90)[(param_1 ^ 1) * 0x388] != 0)) {
        iVar2 = (int)*(short *)((&DAT_800f4e90)[(param_1 ^ 1) * 0x388] + 0x46);
        iVar4 = iVar2 + 0x400;
        iVar1 = iVar4;
        if (iVar4 < 0) {
          iVar1 = iVar2 + 0x13ff;
        }
        sVar5 = (short)iVar4 + (short)(iVar1 >> 0xc) * -0x1000;
      }
      if ((&DAT_800f4e90)[param_1 * 0x388] != 0) {
        *(undefined2 *)((&DAT_800f4e90)[param_1 * 0x388] + 0x44) = 0;
        *(short *)((&DAT_800f4e90)[param_1 * 0x388] + 0x46) = sVar5;
        *(undefined2 *)((&DAT_800f4e90)[param_1 * 0x388] + 0x48) = 0;
        *(undefined4 *)((&DAT_800f4e90)[param_1 * 0x388] + 0x18) = 0;
        *(undefined4 *)((&DAT_800f4e90)[param_1 * 0x388] + 0x1c) = 0;
        *(undefined4 *)((&DAT_800f4e90)[param_1 * 0x388] + 0x20) = 0;
      }
      FUN_8005c334((&DAT_800f4e90)[param_1 * 0x388],0);
      FUN_8005cee0(param_1);
      (&DAT_800f4f8d)[param_1 * 0xe20] = 0;
    }
  }
  return;
}

